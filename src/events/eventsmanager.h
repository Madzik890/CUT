#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H

#include "event.h"

void EventManagerInit();
void EventManagerClose();

void EventManagerAdd(Event *event);
Event **EventManagerReadAll(int *size);//not delete any events
Event **EventManagerRead(const EventType type, int *size);//delete all events of type
const unsigned int EventManagerSize();

void EventManagerSetClose(const int close);
const int EventManagerGetClose();

#endif