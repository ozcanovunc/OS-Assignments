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
	bool Execute(Memory* mem, int base_reg);
	
private:	
	bool ExecuteUndefined(Memory* mem, int base_reg);
	bool ExecuteNop(Memory* mem, int base_reg);
	bool ExecuteSet(Memory* mem, int base_reg);
	bool ExecuteCpy(Memory* mem, int base_reg);
	bool ExecuteCpyi(Memory* mem, int base_reg);
	bool ExecuteCpyi2(Memory* mem, int base_reg);
	bool ExecuteAdd(Memory* mem, int base_reg);
	bool ExecuteAddi(Memory* mem, int base_reg);
	bool ExecuteSubi(Memory* mem, int base_reg);
	bool ExecuteJif(Memory* mem, int base_reg);
	bool ExecuteHlt(Memory* mem, int base_reg);
	bool ExecuteCallFork(Memory* mem, int base_reg);
	bool ExecuteCallPrn(Memory* mem, int base_reg);
	bool ExecuteCallExec(Memory* mem, int base_reg);
	InstructionType type_;
	int first_op_;
	int second_op_;
	std::string comment_;
	std::string instruction_;
};