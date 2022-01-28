#include "event.h"
#include <stdlib.h>

Event *CreateEvent(EventType type, void *data, const int size)
{
    Event *result = NULL;

    result = malloc(sizeof(Event));
    result->_type = type;
    result->_data = data;
    result->_size = size;

    return result;
}

Event *CopyEvent(Event *event)
{
    Event *result = NULL;

    result = malloc(sizeof(Event));    
    result->_type = event->_type;
    result->_data = event->_data;
    result->_size = event->_size;

    return result;
}

void DeleteEvent(Event *event)
{
    free(event);
    event->_size = 0;
    event = NULL;
}