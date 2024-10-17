#include "CPU.h"

using Byte = unsigned char; // 1-byte
using Word = unsigned short; // 2-bytes
using u32 = unsigned int; // 8-bytes

/* Reset
* This functions resets the CPU and its register to a all clear state
* @param: Memory
*/
void CPU::reset(Memory& mem)
{
	PC = 0xFFFC;
	SP = 0x0100;
	C = Z = I = D = B = V = N = 0;
	A = X = Y = 0;
	mem.init();
	return;
}

void CPU::execute(u32 cycles, Memory& mem)
{
	while (cycles > 0)
	{
		Byte instruction = fetch_byte_ins(cycles, mem);
		switch (instruction)
		{
		case INS_LDA_IM:
		{
			Byte value = fetch_byte_ins(cycles, mem);
			A = value;
			lda_set_status();
			break;
		}
		case INS_LDA_ZP:
		{
			Byte zero_page_address = fetch_byte_ins(cycles, mem);
			A = read_byte(cycles, zero_page_address, mem);
			lda_set_status();
		}
		default:
		{
			std::cout << "Instruction not handle" << std::endl;
			break;
		}
		}
	}
	return;
}

/*Fetch Intruction
* This function fetches an instruction from memory and updates the program counter
* @params:
*	Unsigned Int: cycles
*	Memory Object: mem
* @return:
*	Instruction at PC 
*/
Byte CPU::fetch_byte_ins(u32& cycles, Memory& mem)
{
	Byte data = mem[PC];
	PC++;
	cycles--;
	return data;
}
/*Reads data from Memory
* This function reads/returns the data from memory pointed by a given address 
* @params:
*	Unsigned Int: cycles
*	Unsigned char: address
*	Memory Object: mem
* @return:
*	Data at address
*/
Byte CPU::read_byte(u32& cycles, Byte address, Memory& mem)
{
	Byte data = mem[address];
	cycles--;
	return data;
}

void CPU::lda_set_status()
{
	Z = (A == 0);
	N = (A & 0b10000000) > 0;
	return;
}
