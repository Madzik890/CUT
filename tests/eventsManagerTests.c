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

int main()
{    
    EventManagerInit();

    TEST_EXEC("Events Manager Add", eventsManagerAddTest());
    TEST_EXEC("Events Manager ReadAll", eventsManagerReadAllTest());

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