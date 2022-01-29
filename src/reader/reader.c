#include "reader.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../events/eventsmanager.h"
#include "../logger/logger.h"

char *ReadProcStat(int *size)
{
    FILE *f = fopen(READER_LOCATION, "r");
    if(f != NULL)
    {
        char tempBuffer[READER_BUFFER];
        fread(tempBuffer, READER_BUFFER, 1, f);
        fclose(f);
        int bufferSize = strlen(tempBuffer);

        char *string = (char*)malloc(sizeof(char) * bufferSize + 1);
        strcpy(string, tempBuffer);
        *size = bufferSize;

        return string;
    }
    else   
        return NULL;
}

void *ReaderLoop()
{
    while(!EventManagerGetClose())
    {                
        sleep(READER_INTERVAL);
        int size;
        char *buffer = ReadProcStat(&size);
        if(buffer)
        {
            EventManagerAdd(CreateEvent(READER, (void*)buffer, size));

            EventManagerAdd(CreateEvent(WATCHDOG, NULL, ANALYZER));    
            #ifdef ENABLE_LOGS
                LoggerWrite("Reader: read buffer\n");
            #endif
        }
    }
    return 0;
}