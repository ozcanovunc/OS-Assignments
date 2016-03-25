#pragma once

#include "memory.h"

class Instruction {

public:
	enum InstructionType {
		UNDEFINED, NOP, SET, CPY, CPYI, CPYI2, ADD, ADDI, SUBI, JIF, HLT,
		FORK, PRN, EXEC
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
	bool ExecuteCpyi2(Memory* mem);
	bool ExecuteAdd(Memory* mem);
	bool ExecuteAddi(Memory* mem);
	bool ExecuteSubi(Memory* mem);
	bool ExecuteJif(Memory* mem);
	bool ExecuteHlt(Memory* mem);
	bool ExecuteCallFork(Memory* mem);
	bool ExecuteCallPrn(Memory* mem);
	bool ExecuteCallExec(Memory* mem);
	InstructionType type_;
	int first_op_;
	int second_op_;
	std::string comment_;
	std::string instruction_;
};