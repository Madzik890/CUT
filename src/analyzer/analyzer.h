#ifndef ANALZYER_H
#define ANALYZER_H

#define ANALYZER_INTERVAL 1

struct Event;
typedef struct Event Event;
struct CPU;
typedef struct CPU CPU;

extern void AnalizeEvent(Event **events, const int size);
extern void AnalizeBuffer(const char *buffer, const int size);
extern void AnalizeLine(const char *buffer, const int size, double *usage);
extern void *AnalyzerLoop();

#endif