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
/* Execute
* This function executes an instruction based on the opcode
* @params:
*	Unsigned Int: cycles
*	Memory Object: mem
*/
void CPU::execute(u32 cycles, Memory& mem)
{
	while (cycles > 0)
	{
		// Fetch Instruction
		Byte instruction = fetch_byte_ins(cycles, mem);
		// Execute Instruction
		switch (instruction)
		{
		// LDA Instructions - Immidiate, Zero Page, Zero Page X, Absolute, Absolute X, Absolute Y, Indirect X, Indirect Y
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
		case INS_LDA_ZPX:
		{
			Byte zero_page_address = fetch_byte_ins(cycles, mem);
			zero_page_address += X;
			cycles--;
			A = read_byte(cycles, zero_page_address, mem);
			lda_set_status();
			break;
		}
		// Jump to Subroutine
		case INS_JSR:
		{
			// Fetch the address to jump to
			Word subaddress = fetch_word_ins(cycles, mem);
			// Push the address of the next instruction to the stack
			mem.write_word(cycles, SP, PC - 1 );
			cycles--;
			PC = subaddress;
			cycles--;
			break;
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
/*Set ZN Status Flag
* This function sets the Zero and Negative status flags based on the value of the Accumulator
*/

/*Fetch Word Instruction
* This function fetches a word from memory and updates the program counter. The 6502 is little endian so the least significant byte is stored first.
* @params:
*	Unsigned Int: cycles
*	Memory Object: mem
* @return:
* Word at PC

*/
Word CPU::fetch_word_ins(u32& cycles, Memory& mem)
{
	// 6502 is little endian
	Word data = mem[PC];
	PC++;
	// Shift the data by 8 bits to make space for the next byte
	data |= (mem[PC] << 8);
	PC++;
	cycles -= 2;
	// if you want to hamdle the endianness, you would have to swap the bytes
	// if( PLATFORM_BIG_ENDIAN) data = (data >> 8) | (data << 8);
	return data;
}
/*Set ZN Status Flag
* This function sets the Zero and Negative status flags based on the value of the Accumulator

*/
void CPU::lda_set_status()
{
	Z = (A == 0);
	N = (A & 0b10000000) > 0;
	return;
}
