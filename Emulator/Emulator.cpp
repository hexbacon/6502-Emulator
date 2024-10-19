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

    mem[0xFFFC] = CPU::INS_JSR;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
	mem[0x4242] = CPU::INS_LDA_IM;
	mem[0x4243] = 0x84;
    cpu.execute(9, mem);

	std::cout << "Completed" << std::endl;
    return 0;
}
