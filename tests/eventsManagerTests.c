#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include "testmacros.h"
#include "../src/events/event.h"
#include "../src/events/eventsmanager.h"

static Test eventsManagerAddTest();
static Test eventsManagerReadAllTest();
static Test eventsManagerReadAllWithDataTest();
static Test eventsManagerReadTest();
static Test eventsManagerSingleReadTest();

int main()
{    
    EventManagerInit();

    TEST_EXEC("Events Manager Add", eventsManagerAddTest());
    TEST_EXEC("Events Manager ReadAll", eventsManagerReadAllTest());
    TEST_EXEC("Events Manager ReadAll with data", eventsManagerReadAllWithDataTest());
    TEST_EXEC("Events Manager Read", eventsManagerReadTest());
    TEST_EXEC("Events Manager Single Read", eventsManagerSingleReadTest());

    EventManagerClose();
    return 0;
}

Test eventsManagerAddTest()
{
    Test result = 0;
    if(EventManagerSize() != 0)    
        result = -1;

    EventManagerAdd(CreateEvent(PRINTER, NULL, 0));
    if(EventManagerSize() != 1)    
        result = -1;

    EventManagerAdd(CreateEvent(READER, NULL, 0));
    if(EventManagerSize() != 2)    
        result = -1;

    return result;
}

Test eventsManagerReadAllTest()
{
    Test result = 0;

    EventManagerAdd(CreateEvent(PRINTER, NULL, 0));
    EventManagerAdd(CreateEvent(READER, NULL, 0));

    int sizeFirst = 0, sizeSecond = 0;
    Event **eventsFirst = EventManagerReadAll(&sizeFirst);
    assert(eventsFirst);

    Event **eventsSecond = EventManagerReadAll(&sizeSecond);
    assert(eventsSecond);
    
    assert(sizeFirst == sizeSecond);

    for(int i = 0; i < sizeFirst; i++)
    {
        assert(eventsFirst[i]);
        assert(eventsSecond[i]);

        if(eventsFirst[i]->_type != eventsSecond[i]->_type)                   
            result = -2;        
        
        free(eventsFirst[i]);
        free(eventsSecond[i]);
    }

    free(eventsFirst);
    free(eventsSecond);

    return result;
}

static Test eventsManagerReadAllWithDataTest()
{
    Test result = 0;

    const int testStringSize = 6;
    char *testString = NULL;
    testString = (char*)malloc(sizeof(char) * testStringSize);
    strcpy(testString, "12345\n");

    EventManagerAdd(CreateEvent(PRINTER, (void*)testString, testStringSize));

    const int arrayLastIndex = EventManagerSize() - 1;
    int arraySize;
    Event **arrayEvents = EventManagerReadAll(&arraySize);
    assert(arraySize > 1);

    if(arrayEvents[arrayLastIndex]->_type != PRINTER)
        return -1;

    if(arrayEvents[arrayLastIndex]->_size != testStringSize)
        return -2;

    if(strcmp(arrayEvents[arrayLastIndex]->_data, "12345\n") != 0) 
        return -3;

    for(int i = 0; i < arraySize; i++)
        free(arrayEvents[i]);
    free(arrayEvents);
    free(testString);

    return result;    
}

Test eventsManagerReadTest()
{
    Test result = 0;

    const int firstSize = EventManagerSize();

    int arraySize;
    Event **array = EventManagerRead(PRINTER, &arraySize);

    const int secondSize = EventManagerSize();

    if(firstSize != (secondSize + arraySize))
        result = -1;

    for(int i = 0; i < arraySize; i++)
        free(array[i]);
    free(array);

    return result;
}

Test eventsManagerSingleReadTest()
{
    Test result = 0;

    EventManagerAdd(CreateEvent(EXIT_PROGRAM, NULL, 0));

    const int firstSize = EventManagerSize();
    int arraySize;
    Event **array = EventManagerRead(PRINTER, &arraySize);
    const int secondSize = EventManagerSize();

    if(firstSize != (secondSize + arraySize))
        result = -1;

    for(int i = 0; i < arraySize; i++)
        free(array[i]);
    free(array);

    return result;
}