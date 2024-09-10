#include "cpu.h"

void CPU::Reset(MEM &memory) {

    PC = 0xFFFC; // 65532
    SP = 0x0100; // 226
    C = Z = I = D = B = V = N = 0x0;

    A = X = Y = 0;

    memory.Initialise();
}

void CPU::Execute(u32 Cycles, MEM &memmory) {
	
	while( Cycles > 0) {
		
		Byte Ins = FetchByte(Cycles, memmory);

		switch(Ins) {

			case IM_LDA_IM: {

				Byte Value = this->FetchByte(Cycles, memmory);
				A = Value;
				
				this->LDASetStatus();
			}
			break;

			case IM_LDA_ZP: {

				Byte ZeroPageAddress = this->FetchByte(Cycles, memmory);

				A = ReadByte(Cycles, ZeroPageAddress, memmory);

				this->LDASetStatus();
			}
			break;

			case IM_LDA_ZPX:
			{

				Byte ZeroPageAddress = this->FetchByte(Cycles, memmory);

				ZeroPageAddress += X;
				Cycles--;

				A = ReadByte(Cycles, ZeroPageAddress, memmory);

				this->LDASetStatus();
			}
			break;

			case IM_LDA_JSR:
			{

				Word SubAddr = FetchWord(Cycles, memmory);
				memmory.WriteWord(Cycles, PC + 1, SP);
				Cycles--;
				
				PC = SubAddr;
				Cycles--;
			}
			break;

			default: {

				printf("Instruction ' %d ' is not implemented\n", Ins);
			}
		}
   }
}

Byte CPU::FetchByte(u32 &Cycles, MEM &memory) {

	Byte Data = memory[this->PC];

	this->PC++;
	Cycles--;

	return Data;
}

Byte CPU::ReadByte(u32 &Cycles, Byte Address, MEM &memory) {
	
	Byte Data = memory[Address];
	Cycles--;
	return Data;
}

Word CPU::FetchWord(u32 &Cycles, MEM &memory)
{
	Word Data = memory[this->PC];
	PC++;

	Data |= (memory[this->PC] << 8);
	PC++;
	 
	Cycles -= 2;

	#if(__PLATFORM_BIG_ENDIAN__)

		SwapBytesInWord(Data);

	#endif

	return Data;
}

void CPU::LDASetStatus() {

	Z = (A == 0);
	N = (A & 0b10000000) > 0;
}
