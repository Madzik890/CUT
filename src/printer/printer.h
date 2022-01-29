#ifndef PRINTER_H
#define PRINTER_H

#define PRINTER_INTERVAL 1

extern void PrintEvents(Event **events, const int size);
extern void *PrinterLoop();

#endif