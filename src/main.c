#include <stdio.h>
#include "events/eventsmanager.h"

int main(int argc, char **argv)
{
    EventManagerInit();

    printf("CUT :-)\n");

    EventManagerClose();

    return 0;
}