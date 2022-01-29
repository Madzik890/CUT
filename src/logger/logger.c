#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../events/event.h"
#include "../events/eventsmanager.h"

void LoggerWrite(const char *text)
{    
    const int bufferLen = (int)strlen(text);
    char *buffer = (char*)malloc(sizeof(char) * bufferLen);  
    memcpy((void*)buffer, (void*)text, bufferLen * sizeof(char));
    EventManagerAdd(CreateEvent(LOGGER, (void*)buffer, bufferLen));
}

void LoggerWriteToFile(Event **events, const int size)
{
    FILE *file;
    file = fopen(LOGGER_FILE_PATH,"a");
    if(file)
    {        
        for(int i = 0; i < size; i++)       
        {            
            fprintf(file, "%s", (char*)events[i]->_data); 
            free(events[i]->_data);
            free(events[i]);
        }

        free(events);
        fclose(file);
    }
}

void *LoggerLoop()
{    
    while(!EventManagerGetClose())
    {
        int eventsSize;
        Event **events = EventManagerRead(LOGGER, &eventsSize);
        if(eventsSize > 0)
            LoggerWriteToFile(events, eventsSize);

        sleep(LOGGER_INTERVAL);
    }

    return 0;
}