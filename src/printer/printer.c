#include "printer.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../events/event.h"
#include "../events/eventsmanager.h"
#include "../analyzer/cpu.h"

void PrintEvents(Event **events, const int size)
{
    system("clear");
    system("clear");
    for(int i = 0; i < size; i++)
    {
        assert(events[i]->_type == ANALYZER);
        for(int y = 0; y < events[i]->_size; y++)
        {
            CPU *cpu = events[i]->_data;
            printf("CPU%d = %f\n", cpu[y]._index, cpu[y]._usage);
        }

        free(events[i]->_data);    
        free(events[i]);
    }
    free(events);
}

void *PrinterLoop()
{
    while(!EventManagerGetClose())
    {
        int eventsSize;
        Event **events = EventManagerRead(ANALYZER, &eventsSize);
        if(eventsSize > 0)
            PrintEvents(events, eventsSize);        

        EventManagerAdd(CreateEvent(WATCHDOG, NULL, PRINTER));    
        sleep(PRINTER_INTERVAL);
    }
}