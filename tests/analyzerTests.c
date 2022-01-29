#include <stdlib.h>
#include <stdio.h>
#include "testmacros.h"
#include "../src/events/eventsmanager.h"
#include "../src/reader/reader.h"
#include "../src/analyzer/cpu.h"
#include "../src/analyzer/analyzer.h"

static Test AnalizeBufferTest();

int main()
{
    EventManagerInit();

    TEST_EXEC("Analize Buffer", AnalizeBufferTest());

    EventManagerClose();
    return 0;
}

Test AnalizeBufferTest()
{
    Test result = 0;

    int bufferSize;
    char *buffer = ReadProcStat(&bufferSize);
    AnalizeBuffer(buffer, bufferSize);
    free(buffer);    

    int size;
    Event **event = EventManagerRead(ANALYZER, &size);
    for(int i = 0; i < size; i++)
    {
        for(int y = 0; y < event[i]->_size; y++)
        {
            CPU *cpu = event[i]->_data;
            //printf("CPU%d = %f\n", cpu[y]._index, cpu[y]._usage);
        }

        free(event[i]->_data);    
        free(event[i]);
    }
    free(event);

    return result;
}