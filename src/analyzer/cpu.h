#ifndef CPU_H
#define CPU_H

typedef struct CPU CPU;
struct CPU
{
    int _index;
    double _usage;
};

CPU *CreateCPU(const int index, const double usage);
void DeleteCPU(CPU *cpu);

#endif