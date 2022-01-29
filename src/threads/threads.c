#include "threads.h"
#include <stdlib.h>
#include <pthread.h>

static int threadsSize = 0;
static pthread_t *threads = NULL;

int CreateThread(void *func)
{
    threads = (pthread_t*)realloc(threads, threadsSize++ * sizeof(pthread_t));
    return pthread_create(&threads[threadsSize - 1], NULL, func, NULL);
}

void CloseThreads()
{
    for(int i = 0; i < threadsSize; i++)
        pthread_join(threads[i], NULL);
}