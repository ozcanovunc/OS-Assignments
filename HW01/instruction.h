#pragma once

#include "memory.h"

class Instruction {

public:
	enum InstructionType {
		UNDEFINED, NOP, SET, CPY, CPYI, ADD, ADDI, SUBI, JIF, HLT
	};
	Instruction(std::string instruction_str);
	InstructionType GetType();
	int GetFirstOp();
	int GetSecondOp();
	std::string GetComment();
	std::string GetInstructionString();
	bool Execute(Memory* mem);
private:	
	bool ExecuteUndefined(Memory* mem);
	bool ExecuteNop(Memory* mem);
	bool ExecuteSet(Memory* mem);
	bool ExecuteCpy(Memory* mem);
	bool ExecuteCpyi(Memory* mem);
	bool ExecuteAdd(Memory* mem);
	bool ExecuteAddi(Memory* mem);
	bool ExecuteSubi(Memory* mem);
	bool ExecuteJif(Memory* mem);
	bool ExecuteHlt(Memory* mem);
	InstructionType type_;
	int first_op_;
	int second_op_;
	std::string comment_;
	std::string instruction_;
};