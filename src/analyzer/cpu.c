#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

CPU *CreateCPU(const int index, const double usage)
{
    CPU *result = NULL;
    
    result = (CPU*)malloc(sizeof(CPU));
    assert(result);

    result->_index = index;
    result->_usage = usage;        

    return result;
}

void DeleteCPU(CPU *cpu)
{
    free(cpu);
    cpu = NULL;    
}