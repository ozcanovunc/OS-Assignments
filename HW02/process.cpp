#include "helper.h"
#include "process.h"

Process::Process(string file_name, Memory* mem, int starting_time, int ppid) {

	ifstream file(file_name.c_str());
    string line;
    Instruction* instr;
    int former_mem_size = mem->GetSize();

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

    mem->AllocMemoryForNewProcess(file_name);

    name_ = file_name;
    pid_ = WaitRandomBetween(1000, 5000);
    parent_pid_ = ppid;
    starting_time_ = starting_time;
    execution_time_ = 0;

    // Setting up base and limit registers
    base_reg_ = former_mem_size;
    limit_reg_ = mem->GetSize() - 1;  
    mem->SetValue(2 + base_reg_, base_reg_);
    mem->SetValue(3 + base_reg_, limit_reg_);

    // Process is initially in ready state
    state_ = READY;
}

int Process::GetPid() {
    return pid_;
}

string Process::GetName() {
    return name_;
}

ProcessState Process::GetState() {
	return state_;
}

int Process::GetPc(Memory* mem) {
    return mem->GetValue(base_reg_);
}

int Process::GetBaseReg() {
    return base_reg_;
}

int Process::GetLimitReg() {
    return limit_reg_;
}

int Process::GetExecutionTime() {
    return execution_time_;
}

void Process::SetState(ProcessState state) {
	state_ = state;
}

void Process::SetPc(Memory* mem, int pc) {
    mem->SetValue(base_reg_, pc);
}

void Process::SetBaseReg(int base_reg) {
    base_reg_ = base_reg;
}

void Process::SetLimitReg(int limit_reg) {
    limit_reg_ = limit_reg;
}

void Process::SetExecutionTime(int exe_time) {
    execution_time_ = exe_time;
}

string Process::ExecuteCurrentInstruction(Memory* mem) {
	return instruction_set_.at(GetPc(mem)).Execute(mem, base_reg_, limit_reg_);
}

Process* Process::Fork(Memory* mem, int starting_time) {

    Process* new_process = new Process(name_, mem, starting_time, pid_);
    new_process->SetPc(mem, GetPc(mem));
    return new_process;
}

ostream& operator<<(ostream& os, const Process& process) {

    os << "name_\t\t\t:" << process.name_ << endl <<
    "pid_\t\t\t:" << process.pid_ << endl <<
    "parent_pid_\t\t:" << process.parent_pid_ << endl <<
    "starting_time_\t\t:" << process.starting_time_ << endl <<
    "execution_time_\t\t:" << process.execution_time_ << endl <<
    "base_reg_\t\t:" << process.base_reg_ << endl <<
    "limit_reg_\t\t:" << process.limit_reg_ << endl;

    return os;
}