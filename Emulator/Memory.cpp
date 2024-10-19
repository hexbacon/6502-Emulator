#include "Memory.h"

using Byte = unsigned char; // 1-byte
using Word = unsigned short; // 2-bytes
using u32 = unsigned int; // 8-bytes

/* Init
* This function initializes the memory to 0
*/
void Memory::init()
{
	for (u32 i = 0; i < MAX_MEM; i++)
	{
		Data[i] = 0;
	}
	return;
}
/* Read Word
* This function writes a 2 bytes to the memory. The 6502 is little endian so the least significant byte is stored first. 
* @params:
*	Unsigned Int: cycles
*	Word: address -> Address to write to
*	Memory Object: mem
* @return: void
*/
void Memory::write_word(u32& cycles, Word address, Word value)
{
	// Write the least significant byte first
	Data[address] = value & 0xFF;
	// Write the most significant byte
	Data[address + 1] = (value >> 8);
	cycles -= 2;
	return;
}
// Read a byte from memory
Byte Memory::operator[](u32 address) const
{
	return Data[address];
}

// Write a byte to memory
Byte& Memory::operator[](u32 address)
{
	return Data[address];
}