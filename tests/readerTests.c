#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include "testmacros.h"
#include "../src/events/eventsmanager.h"
#include "../src/reader/reader.h"

static Test exitLoopTest();
static Test readProcStatTest();
static Test checkEventsTests();
static Test checkEventsTestsMultiThread();

int main()
{
    EventManagerInit();

    TEST_EXEC("ExitLoop", exitLoopTest());
    TEST_EXEC("ReadProcStat", readProcStatTest());
    TEST_EXEC("CheckEventsTests", checkEventsTests());
    TEST_EXEC("CheckEventsTestsMultiThread", checkEventsTestsMultiThread());
    
    EventManagerClose();
    return 0;
}

void *exitThread();
Test exitLoopTest()
{    
    pthread_t thread;
    int result = pthread_create(&thread, NULL, exitThread, NULL);
    if (result != 0) {
        return -1;
    }

    ReaderLoop();    
    pthread_join(thread, NULL);
    return 0;    
}

Test readProcStatTest()
{
    int bufferSize;
    char *buffer = ReadProcStat(&bufferSize);
    assert(buffer);
    assert(bufferSize > 0);    
    free(buffer);

    return 0;
}

Test checkEventsTests()
{
    int retry = 0;
    while(retry++ < 5)
    {
        ReaderLoop();
        int size;
        Event **events = EventManagerRead(READER, &size);
        if(size > 0)
        {
            for(int i = 0; i < size; i++)
            {
                free(events[i]->_data);
                free(events[i]);
            }
            free(events);
            return 0;
        }

        sleep(0.1);        
    }

    return -1;
}

Test checkEventsTestsMultiThread()
{
    EventManagerSetClose(0);
    Test testResult = -1;
    pthread_t thread;
    int result = pthread_create(&thread, NULL, ReaderLoop, NULL);

    int retry = 0;
    while(retry++ < 10)
    {
        int size;
        Event **events = EventManagerRead(READER, &size);
        if(size > 0)
        {
            for(int i = 0; i < size; i++)
            {
                free(events[i]->_data);
                free(events[i]);
            }
            free(events);
            testResult = 0;
            break;
        }

        sleep(1);        
    }

    EventManagerSetClose(255);
    pthread_join(thread, NULL);
    return testResult;
}

void *exitThread()
{
    sleep(1);
    EventManagerSetClose(255);
}