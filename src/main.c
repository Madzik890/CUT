#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "events/eventsmanager.h"
#include "reader/reader.h"
#include "analyzer/analyzer.h"
#include "printer/printer.h"
#include "watchdog/watchdog.h"
#include "logger/logger.h"
#include "threads/threads.h"

volatile sig_atomic_t done = 0;
void term(int signum);

int main()
{
    EventManagerInit();
    EventManagerSetClose(0);

    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);

    START_THREAD(ReaderLoop);
    START_THREAD(AnalyzerLoop);
    START_THREAD(PrinterLoop);
    START_THREAD(WatchdogLoop);
    START_THREAD(LoggerLoop);

    while (!done && !EventManagerGetClose())
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
    (void)signum;
    done = 1;
}