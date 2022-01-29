#ifndef THREADS_H
#define THREADS_H

#define START_THREAD(func)                                  \
        if(CreateThread(func) != 0)                         \
        {  printf("Cannot create thread!"); return -1; }    \

int CreateThread(void *func);
void CloseThreads();

#endif