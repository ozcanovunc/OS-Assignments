#pragma once

#include "instruction.h"
#include "memory.h"

typedef enum {
	READY, BLOCKED, RUNNING, FINISHED
} ProcessState;

class Process {

public:
	Process(std::string file_name, Memory* mem, int starting_time, int ppid = -1);

	int GetPid();
	string GetName();

	ProcessState GetState();
	int GetPc(Memory* mem);
	int GetBaseReg();
	int GetLimitReg();
	int GetExecutionTime();

	void SetState(ProcessState state);
	void SetPc(Memory* mem, int pc);
	void SetBaseReg(int base_reg);
	void SetLimitReg(int limit_reg);
	void SetExecutionTime(int exe_time);

	std::string ExecuteCurrentInstruction(Memory* mem);
	Process* Fork(Memory* mem, int starting_time);
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