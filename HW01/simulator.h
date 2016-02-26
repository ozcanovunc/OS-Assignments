#pragma once

#include "instruction.h"
#include "memory.h"

class Simulator {

public:
	Simulator(std::string file_name, int debug_mode);
	~Simulator();
	int GetPc();
	void SetPc(int pc);
	void RunSimulator();
private:
	Memory* memory_;
	std::vector<Instruction> instruction_set_;
	bool debug_mode_;
};