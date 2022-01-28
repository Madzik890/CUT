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
    int size = 0;

    EventManagerAdd(CreateEvent(PRINTER, NULL, 0));
    if(EventManagerSize() != 1)    
        result = -1;

    EventManagerAdd(CreateEvent(READER, NULL, 0));
    if(EventManagerSize() != 2)    
        result = -1;

    Event **events = EventManagerReadAll(&size);
    assert(events);
    printf("Size: %d \n", size);
    for(int i = 0; i < size; i++)
    {
        assert(events[i]);
        printf("%d \n", events[i]->_type);
        free(events[i]);
    }

    free(events);

    return result;
}