#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include "../src/events/event.h"
#include "testmacros.h"

static Test eventTest();
static Test eventCopyTest();

int main(int argc, char **arv)
{
    TEST_EXEC("Create Event", eventTest());
    TEST_EXEC("Copy event", eventCopyTest());

    return 0;
}

#define TEST_STRING_SIZE 10
static char * EXAMPLE_STRING = "0123456789";

static Test eventTest()
{
    Test result = 0;

    char *testString = (char*)malloc(sizeof(char) * TEST_STRING_SIZE);
    assert(testString);
    strcpy(testString, EXAMPLE_STRING);

    Event *event = CreateEvent(READER, testString, TEST_STRING_SIZE);
    assert(event);

    const char *eventDataPtr = (char*)event[0]._data;
    for(int i = 0; i < TEST_STRING_SIZE; i++)
    {
        if(eventDataPtr[i] != EXAMPLE_STRING[i])
        {
            printf("EventTest = error\n");
            printf("Strings are not equals");
            result = -1;
        }
    }
    
    DeleteEvent(event);
    free(testString);    
    return result;
}

Test eventCopyTest()
{
    return 0;
}