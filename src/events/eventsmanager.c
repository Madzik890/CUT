#include "eventsmanager.h"
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

typedef struct EventManager EventManager;
struct EventManager
{
    Event **_eventsArray;
    unsigned int _eventsSize;
};

static pthread_mutex_t *g_eventManagerMutex = NULL;
static EventManager *g_eventManger = NULL;

void EventManagerInit()
{
    g_eventManger = calloc(1, sizeof(EventManager));
    g_eventManagerMutex = malloc(sizeof(pthread_mutex_t));
    assert(g_eventManger);
    assert(g_eventManagerMutex);
}

void EventManagerClose()
{
    assert(g_eventManger);
    assert(g_eventManagerMutex);

    const int arraySize = g_eventManger->_eventsSize;
    for(int i = 0; i < arraySize; i++)
    {     
        free(g_eventManger->_eventsArray[i]);    
    }
    free(g_eventManger->_eventsArray);


    free(g_eventManger);
    free(g_eventManagerMutex);
}

void EventManagerAdd(Event *event)
{
    pthread_mutex_lock(g_eventManagerMutex);

    g_eventManger->_eventsArray = (Event**)realloc(g_eventManger->_eventsArray, ++g_eventManger->_eventsSize * sizeof(Event*));
    g_eventManger->_eventsArray[g_eventManger->_eventsSize - 1] = event;
    
    pthread_mutex_unlock(g_eventManagerMutex);
}

Event **EventManagerReadAll(int *size)
{
    Event **array = NULL;    
    assert(size);

    pthread_mutex_lock(g_eventManagerMutex);

    const int arraySize = g_eventManger->_eventsSize;
    array = (Event**)malloc(sizeof(Event*) * arraySize);
    *size = arraySize;

    for(int i = 0; i < arraySize; i++)
    {
        array[i] = (Event*)malloc(sizeof(Event));     
        memcpy((void*)array[i], (void*)g_eventManger->_eventsArray[i], sizeof(Event));        
    }

    assert(array);

    pthread_mutex_unlock(g_eventManagerMutex);
    return array;
}

const int EventManagerSize()
{
    pthread_mutex_lock(g_eventManagerMutex);
    int result = g_eventManger->_eventsSize;
    pthread_mutex_unlock(g_eventManagerMutex);
    return result;
}