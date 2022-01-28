#ifndef EVENT_H
#define EVENT_H

typedef enum
{
    READER = 0x1,
    ANALYZER = 0x2,
    PRINTER = 0x3,
    WATCHDOG = 0x4,
    LOGGER = 0x5
} EventType;

typedef struct Event Event;
struct Event
{
    EventType _type;
    void *_data;
    int _size;
};

Event *CreateEvent(EventType type, void *data, const int size);
Event *CopyEvent(Event *event);
void DeleteEvent(Event *event);

#endif