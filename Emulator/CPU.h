#pragma once
#include "Memory.h"
#include <iostream>

/*Emualor for the 6502 CPU*/

class CPU
{
	using Byte = unsigned char; // 1-byte
	using Word = unsigned short; // 2-bytes
	using u32 = unsigned int; // 8-bytes
public:
	Word PC; // Program counter
	Word SP; // Stack Pointer

	Byte A, X, Y; // Registers

	// Status Flags
	Byte C : 1;
	Byte Z: 1;
	Byte I : 1;
	Byte D : 1;
	Byte B : 1;
	Byte V : 1;
	Byte N : 1;

	// Opcode
	static constexpr Byte INS_LDA_IM = 0xA9, INS_LDA_ZP = 0xA5;

	// Methods
	void reset(Memory& mem); // Resets the CPU
	void execute(u32 cycles, Memory& mem); // Executes an instruction
	void lda_set_status(); // Sets the  Z,N flags 
	Byte fetch_byte_ins(u32& cycles, Memory& mem); // Fetches  instructions
	Byte read_byte(u32& cycles, Byte address, Memory& mem); // Reads from memory

};