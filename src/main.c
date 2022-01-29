#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "events/eventsmanager.h"
#include "reader/reader.h"
#include "analyzer/analyzer.h"
#include "printer/printer.h"
#include "threads/threads.h"

volatile sig_atomic_t done = 0;
void term(int signum);

int main(int argc, char **argv)
{
    EventManagerInit();
    EventManagerSetClose(0);

    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
    int loop = 0;

    START_THREAD(ReaderLoop);
    START_THREAD(AnalyzerLoop);
    START_THREAD(PrinterLoop);

    while (!done)
    {
        int t = sleep(3);
        while (t > 0)         
            t = sleep(t);        
    }

    EventManagerSetClose(255);
    CloseThreads();
    EventManagerClose();

    return 0;
}

void term(int signum)
{
    done = 1;
}