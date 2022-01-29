#include "analyzer.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../events/event.h"
#include "../events/eventsmanager.h"
#include "cpu.h"
#include "../logger/logger.h"

extern void AnalizeEvent(Event **events, const int size)
{

    for(int i = 0; i < size; i++)
    {
        assert(events[i]->_type == READER);
        AnalizeBuffer(events[i]->_data, events[i]->_size);
        free(events[i]->_data);
        free(events[i]);
    }

    free(events);

    LoggerWrite("Analyzer: calculate cpu usages\n");
}

extern void AnalizeBuffer(const char *buffer, const int size)
{
    char * line = strtok(strdup(buffer), "\n");
    line = strtok(NULL, "\n");

    int cpuArraySize = 0;
    CPU *cpuArray = NULL;

    while(line) 
    {
        if(strstr(line, "cpu") != 0)
        {
            cpuArray = (CPU*)realloc(cpuArray, ++cpuArraySize * sizeof(CPU));

            double cpuUsage;
            AnalizeLine(line, strlen(line), &cpuUsage);

            CPU cpu;
            cpu._index = cpuArraySize;
            cpu._usage = cpuUsage;
            cpuArray[cpuArraySize - 1] = cpu;
        }
        else
            goto exit;   

        line = strtok(NULL, "\n");                
    }

    exit:

    if(cpuArraySize > 0)
        EventManagerAdd(CreateEvent(ANALYZER, (void*)cpuArray, cpuArraySize));    
}

void AnalizeLine(const char *buffer, const int size, double *usage)
{       
    int varSelect = 0;
    long user = 0;
    long nice = 0;
    long system = 0;
    long idle = 0;
    long iowait = 0;
    long irq = 0;
    long softirq = 0;

    int index = 0;
    for(int i = 0; i < size; i++)
    {
        if(buffer[i] == ' ')
        {            
            const int length = i - index;            

            char *string = (char*)calloc(length + 1, sizeof(char));
            strncpy(string, buffer + index, length);
            string[length] = '\0';            

            switch(varSelect)
            {
                case 0:
                    user = atol(string);
                break;

                case 1:
                    nice = atol(string);
                break;

                case 2:
                    system = atol(string);
                break;

                case 3:
                    idle = atol(string);
                break;
                
                case 4:
                    iowait = atol(string);
                break;

                case 5:
                    irq = atol(string);
                break;

                case 6:
                    softirq = atol(string);
                break;
            };

            index = i + 1;
            free(string);
            varSelect++;
        }
    }

    double cpuUsage = (double)(idle * 1000.f) / (double)(user + nice + system + idle + iowait + irq + softirq);
    *usage = cpuUsage;
}

void *AnalyzerLoop()
{
    while(!EventManagerGetClose())
    {
        int eventsSize;
        Event **events = EventManagerRead(READER, &eventsSize);
        if(eventsSize > 0)
            AnalizeEvent(events, eventsSize);

        EventManagerAdd(CreateEvent(WATCHDOG, NULL, ANALYZER));    
        sleep(ANALYZER_INTERVAL);
    }
}