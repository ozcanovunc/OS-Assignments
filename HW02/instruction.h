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
	std::string Execute(Memory* mem, int base_reg, int limit_reg);
	
private:	
	std::string ExecuteUndefined(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteNop(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteSet(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteCpy(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteCpyi(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteCpyi2(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteAdd(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteAddi(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteSubi(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteJif(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteHlt(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteCallFork(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteCallPrn(Memory* mem, int base_reg, int limit_reg);
	std::string ExecuteCallExec(Memory* mem, int base_reg, int limit_reg);
	InstructionType type_;
	int first_op_;
	int second_op_;
	std::string comment_;
	std::string instruction_;
};