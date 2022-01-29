#ifndef LOGGER_H
#define LOGGER_H

#define LOGGER_INTERVAL 3
#define LOGGER_FILE_PATH "./logger"

typedef struct Event Event;
struct Event;

void LoggerWrite(const char *text);
extern void LoggerWriteToFile(Event **events, const int size);
extern void *LoggerLoop();

#endif