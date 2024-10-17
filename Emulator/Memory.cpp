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

// Operators
Byte Memory::operator[](u32 address) const
{
	return Data[address];
}

Byte& Memory::operator[](u32 address)
{
	return Data[address];
}