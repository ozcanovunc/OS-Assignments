#pragma once

#include "instruction.h"
#include "memory.h"

class Process {

public:
	enum ProcessState {
		READY, BLOCKED, RUNNING, FINISHED
	};
	Process(std::string file_name, Memory* mem, int starting_time, int ppid = -1);
	~Process();
	ProcessState GetState();
	void SetState(ProcessState state);
	int GetBaseReg();
	int GetLimitReg();
	int GetPc(Memory* mem);
	std::string ExecuteCurrentInstruction(Memory* mem);
	friend std::ostream& operator<<(std::ostream& os, const Process& process);

private:
	std::string name_;
	int pid_;
	int parent_pid_;
	int starting_time_;
	int execution_time_;
	int base_reg_;
	int limit_reg_;
	ProcessState state_;
	std::vector<Instruction> instruction_set_;
};