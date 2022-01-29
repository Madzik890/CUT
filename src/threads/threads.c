#include "threads.h"
#include <stdlib.h>
#include <pthread.h>

static int g_threadsSize = 0;
static pthread_t *g_threads = NULL;

int CreateThread(void *func)
{
    g_threads = (pthread_t*)realloc(g_threads, ++g_threadsSize * sizeof(pthread_t));
    return pthread_create(&g_threads[g_threadsSize - 1], NULL, func, NULL);
}

void CloseThreads()
{
    for(int i = 0; i < g_threadsSize; i++)
        pthread_join(g_threads[i], NULL);
}