#include "watchdog.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../events/event.h"
#include "../events/eventsmanager.h"

void *WatchdogLoop()
{
    sleep(10);
    while(!EventManagerGetClose())
    {
        int eventsSize;
        Event **events = EventManagerRead(WATCHDOG, &eventsSize);
        if(eventsSize < 3)
        {
            EventManagerSetClose(255);
            printf("WATCHDOG FOUND A NOT WORKING THREAD!!!!!");
        }

        for(int i = 0; i < eventsSize; i++)
            free(events[i]);
        free(events); 

        sleep(WATCHDOG_INTERVAL);
    }
}