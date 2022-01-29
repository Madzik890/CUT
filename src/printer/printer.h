#ifndef PRINTER_H
#define PRINTER_H

#define PRINTER_INTERVAL 1

typedef struct Event Event;
struct Event;

extern void PrintEvents(Event **events, const int size);
extern void *PrinterLoop();

#endif