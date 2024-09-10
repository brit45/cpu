#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "mem.h"

// using Byte = u_char;
// using Word = u_short;

int main(void)
{

    MEM mem;
    CPU cpu;

    cpu.Reset(mem);

	//-----------------------[ Start ] Inline litle endian program

	mem[0xFFFC] = CPU::IM_LDA_JSR;
	mem[0xFFFD] = 0x42;
	mem[0xFFFE] = 0x42;
	mem[0x4242] = CPU::IM_LDA_IM;
	mem[0x4243] = 0x84;

	//-----------------------[ End ] litle endian program

	cpu.Execute(9, mem);

	return 0;
}