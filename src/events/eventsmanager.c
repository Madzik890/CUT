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
    int _close;
};

static pthread_mutex_t *g_eventManagerMutex = NULL;
static pthread_mutexattr_t *g_eventManagerAttr = NULL;
static EventManager *g_eventManger = NULL;

void EventManagerInit()
{
    g_eventManger = calloc(1, sizeof(EventManager));
    g_eventManagerMutex = malloc(sizeof(pthread_mutex_t));
    g_eventManagerAttr = malloc(sizeof(pthread_mutexattr_t));
    assert(g_eventManger);
    assert(g_eventManagerMutex);
    assert(g_eventManagerAttr);

    pthread_mutexattr_init(g_eventManagerAttr);
    pthread_mutex_init(g_eventManagerMutex, g_eventManagerAttr);
}

void EventManagerClose()
{
    assert(g_eventManger);
    assert(g_eventManagerMutex);

    const int arraySize = g_eventManger->_eventsSize;

    for(int i = 0; i < arraySize; i++)
    {
        free(g_eventManger->_eventsArray[i]->_data); 
        free(g_eventManger->_eventsArray[i]);        
    }
    free(g_eventManger->_eventsArray);
    free(g_eventManger);

    pthread_mutex_destroy(g_eventManagerMutex);	
    pthread_mutexattr_destroy(g_eventManagerAttr);
    free(g_eventManagerMutex);
    free(g_eventManagerAttr);
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

Event **EventManagerRead(const EventType type, int *size)
{
    Event **array = NULL;
    int arraySize = 0;

    pthread_mutex_lock(g_eventManagerMutex);
    if(g_eventManger->_eventsSize > 0)
    {    
        for(int i = 0; i < g_eventManger->_eventsSize; i++)
        {
            if(g_eventManger->_eventsArray[i]->_type == type)
            {
                array = (Event**)realloc(array, sizeof(Event*) * ++arraySize);
                array[arraySize - 1] = (Event*)malloc(sizeof(Event));
                memcpy((void*)array[arraySize - 1], (void*)g_eventManger->_eventsArray[i], sizeof(Event));
            }
        }

        int index = 0;
        Event **copyArray = NULL;
        int copyArraySize = g_eventManger->_eventsSize - arraySize;
        copyArray = (Event**)malloc(sizeof(Event*) * copyArraySize);
        for(int i = 0; i < g_eventManger->_eventsSize; i++)
        {
            if(g_eventManger->_eventsArray[i]->_type != type)
            {
                copyArray[index] = (Event*)malloc(sizeof(Event));
                memcpy((void*)copyArray[index++], (void*)g_eventManger->_eventsArray[i], sizeof(Event));        
            }
            free(g_eventManger->_eventsArray[i]);
        }

        free(g_eventManger->_eventsArray);

        g_eventManger->_eventsSize = copyArraySize;
        g_eventManger->_eventsArray = copyArray;
    }

    pthread_mutex_unlock(g_eventManagerMutex);
    *size = arraySize;
    return array;
}

const unsigned int EventManagerSize()
{
    pthread_mutex_lock(g_eventManagerMutex);
    unsigned int result = g_eventManger->_eventsSize;
    pthread_mutex_unlock(g_eventManagerMutex);
    return result;
}

void EventManagerSetClose(const int close)
{
    pthread_mutex_lock(g_eventManagerMutex);
    g_eventManger->_close = close;
    pthread_mutex_unlock(g_eventManagerMutex);
}

const int EventManagerGetClose()
{
    pthread_mutex_lock(g_eventManagerMutex);
    int result = g_eventManger->_close;
    pthread_mutex_unlock(g_eventManagerMutex);
    return result;
}