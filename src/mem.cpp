#include "mem.h"


void MEM::Initialise() {

    for( u32 i = 0; i < MAX_MEM; i++) {

        Data[i] = 0x0;
    }
}

Byte MEM::operator[](u32 Address) const
{
    return Data[Address];
}

Byte &MEM::operator[](u32 Address) {

	return Data[Address];
}

void MEM::WriteWord(u32 &Cycles, Word Value, u32 Address)
{

	Data[Address]     = Value & 0xFF;
	Data[Address + 1] = (Value >> 8);
	Cycles -= 2;
}
