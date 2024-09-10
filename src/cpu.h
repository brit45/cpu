#ifndef __CPU_H__
#define __CPU_H__

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

using Byte = u_char;
using Word = u_short;
using u32 = uint;
using s32 = signed int;

/**
 * @brief  LOGICAL SYSTEM
 */
struct CPU {

    Word PC; // Program counter

    Word SP; // Stack Pointer

    Byte A, X, Y; // Registers

    Byte PS; // Processor Status

    Byte C : 1; // Status Flags
    Byte Z : 1; // Status Flags
    Byte I : 1; // Status Flags
    Byte D : 1; // Status Flags
    Byte B : 1; // Status Flags
    Byte V : 1; // Status Flags
    Byte N : 1; // Status Flags

    void Reset(MEM &memory); // Reset program

    s32 Execute(u32 Cycles, MEM &memmory); // Execute program

    Byte FetchByte( u32 &Cycles, MEM &memory); // Read Memory

	Byte ReadByte(u32 &Cycles, Byte Address, MEM &memory); // Read Memory

	Word FetchWord(u32 &Cycles, MEM &memory);

	void LDASetStatus();

	// OPCODES
	static constexpr Byte

		IM_LDA_IM  = 0xA9, // 169
		IM_LDA_ZP  = 0xA5, // 165
		IM_LDA_ZPX = 0xB5, // 181
		IM_LDA_JSR = 0x20; // 32
};

#endif //!__CPU_H__