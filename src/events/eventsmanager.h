#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H

struct Event;
typedef struct Event Event;

void EventManagerInit();
void EventManagerClose();

void EventManagerAdd(Event *event);
Event **EventManagerReadAll(int *size);
const int EventManagerSize();

Event **EventManagerReadLogger(int *size);
Event **EventManagerReadAnalyzer(int *size);
Event **EventManagerReadPrinter(int *size);
Event **EventManagerReadWatchDog(int *size);
Event **EventManagerLogger(int *size);

#endif