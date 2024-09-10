#ifndef __MEM_H__
#define __MEM_H__

#include <stdio.h>
#include <stdlib.h>

using Byte = u_char;
using Word = u_short;
using u32 = uint;

/**
 * @brief  MEMORY SYSTEM
 */
struct MEM
{

    static constexpr  u32 MAX_MEM = 1024 * 64;

    Byte Data[MAX_MEM];

    void Initialise();

    Byte operator[](u32 Address) const; // Read on byte in memory

	Byte &operator[](u32 Address); // write one byte in memory

	void WriteWord(u32 &Cycles, Word Data, u32 Address); // Write two byte in memory
};

#endif //!__MEM_H__