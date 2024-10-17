#pragma once

class Memory
{
	using Byte = unsigned char; // 1-byte
	using Word = unsigned short; // 2-bytes
	using u32 = unsigned int; // 8-bytes
public: 
	static constexpr u32 MAX_MEM = 1024 * 64;
	Byte Data[MAX_MEM];
	// Methods
	void init();

	// Operators
	// Read
	Byte operator[](u32 address) const;
	// Write
	Byte& operator[](u32 address);


};