// Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CPU.h"
#include "Memory.h"
    
int main()
{
    CPU cpu;
    Memory mem;

    cpu.reset(mem);
    mem[0xFFFC] = CPU::INS_LDA_ZP;
    mem[0xFFFD] = 0x42;
    mem[0x042] = 0x84;
    cpu.execute(3, mem);

    return 0;
}
