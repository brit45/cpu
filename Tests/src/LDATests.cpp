#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "../../src/cpu.h"
#include "../../src/mem.h"

class LDATests : public testing::Test {

	public:

		MEM memory;
		CPU cpu;

	protected:

		void SetUp() override {
			
			cpu.Reset(memory);
		}

		void TearDown() override {}
};


TEST_F(LDATests, LDAImmediateCanLoadAValueIntoTheRegister) {

	//-----------------------[ Start ] Inline litle endian program

	memory[0xFFFC] = CPU::IM_LDA_IM;
	memory[0xFFFD] = 0x84;

	//-----------------------[ End ] litle endian program
	
	CPU CPUCopy = cpu;
	s32 CyclesUsed = cpu.Execute(2, memory);

	EXPECT_EQ(CyclesUsed, 2);
	EXPECT_EQ(cpu.A, 0x84);
	EXPECT_TRUE(cpu.N);
	EXPECT_FALSE(cpu.Z);
	EXPECT_EQ(cpu.C, CPUCopy.C);
	EXPECT_EQ(cpu.B, CPUCopy.B);
	EXPECT_EQ(cpu.D, CPUCopy.D);
	EXPECT_EQ(cpu.I, CPUCopy.I);
	EXPECT_EQ(cpu.V, CPUCopy.V);
};

TEST_F(LDATests, LDAIZeroPageCanLoadAValueIntoTheRegister)
{

	//-----------------------[ Start ] Inline litle endian program

	memory[0xFFFC] = CPU::IM_LDA_ZP;
	memory[0xFFFD] = 0x42;
	memory[0x0042] = 0x37;

	//-----------------------[ End ] litle endian program
	
	CPU CPUCopy = cpu;
	cpu.Execute(3, memory);

	EXPECT_EQ(cpu.A, 0x37);
	EXPECT_FALSE(cpu.Z);
	EXPECT_FALSE(cpu.N);
	EXPECT_EQ(cpu.C, CPUCopy.C);
	EXPECT_EQ(cpu.B, CPUCopy.B);
	EXPECT_EQ(cpu.D, CPUCopy.D);
	EXPECT_EQ(cpu.I, CPUCopy.I);
	EXPECT_EQ(cpu.V, CPUCopy.V);
};

TEST_F(LDATests, LDAIZeroPageXCanLoadAValueIntoTheRegister)
{

	cpu.X = 5;
	//-----------------------[ Start ] Inline litle endian program

	memory[0xFFFC] = CPU::IM_LDA_ZPX;
	memory[0xFFFD] = 0x42;
	memory[0x0047] = 0x37;

	//-----------------------[ End ] litle endian program
	
	CPU CPUCopy = cpu;
	cpu.Execute(4, memory);

	EXPECT_EQ(cpu.A, 0x37);
	EXPECT_FALSE(cpu.Z);
	EXPECT_FALSE(cpu.N);
	EXPECT_EQ(cpu.C, CPUCopy.C);
	EXPECT_EQ(cpu.B, CPUCopy.B);
	EXPECT_EQ(cpu.D, CPUCopy.D);
	EXPECT_EQ(cpu.I, CPUCopy.I);
	EXPECT_EQ(cpu.V, CPUCopy.V);
};

TEST_F(LDATests, LDAIZeroPageXCanLoadAValueIntoTheRegisterWhenItWraps)
{

	cpu.X = 0xFF;
	//-----------------------[ Start ] Inline litle endian program

	memory[0xFFFC] = CPU::IM_LDA_ZPX;
	memory[0xFFFD] = 0x80;
	memory[0x007F] = 0x37;

	//-----------------------[ End ] litle endian program
	CPU CPUCopy = cpu;
	cpu.Execute(4, memory);

	EXPECT_EQ(cpu.A, 0x37);
	EXPECT_FALSE(cpu.Z);
	EXPECT_FALSE(cpu.N);
	EXPECT_EQ(cpu.C, CPUCopy.C);
	EXPECT_EQ(cpu.B, CPUCopy.B);
	EXPECT_EQ(cpu.D, CPUCopy.D);
	EXPECT_EQ(cpu.I, CPUCopy.I);
	EXPECT_EQ(cpu.V, CPUCopy.V);
};