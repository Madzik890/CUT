#ifndef READER_H
#define READER_H

#define READER_INTERVAL 1
#define READER_LOCATION "/proc/stat"
#define READER_BUFFER 65535 

extern char *ReadProcStat(int *size);
extern void *ReaderLoop();

#endif