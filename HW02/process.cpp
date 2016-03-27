#include "helper.h"
#include "process.h"

Process::Process(string file_name, Memory* mem, int starting_time, int ppid) {

	ifstream file(file_name.c_str());
    string line;
    Instruction* instr;

    while (getline(file, line))
    {
    	// Get each instruction 
    	if (line.find("Begin Instruction Section") != string::npos) {
    	    while(getline(file, line) && 
    	    	line.find("End Instruction Section") == string::npos) {

    	    	instr = new Instruction(line);
    	    	instruction_set_.push_back(*instr);
    	    	delete instr;
    	    }
    	}
    }

    mem->AllocMemoryForNewProcess(file_name, base_reg_, limit_reg_);

    name_ = file_name;
    pid_ = 0;									// TODO: generate a number
    parent_pid_ = ppid;
    starting_time_ = starting_time;
    execution_time_ = 0;

    // Process is initially in ready state
    state_ = READY;
}

Process::~Process() {

}

Process::ProcessState Process::GetState() {
	return state_;
}

void Process::SetState(Process::ProcessState state) {
	state_ = state;
}

int Process::GetBaseReg() {
	return base_reg_;
}

int Process::GetLimitReg() {
	return limit_reg_;
}

int Process::GetPc(Memory* mem) {
	return mem->GetValue(base_reg_);
}

bool Process::ExecuteCurrentInstruction(Memory* mem) {
	return instruction_set_.at(GetPc(mem)).Execute(mem, base_reg_);
}

ostream& operator<<(ostream& os, const Process& mem) {

}