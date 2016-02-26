#include "helper.h"
#include "simulator.h"

Simulator::Simulator(string file_name, int debug_mode) {

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
    	    }
    	}
    }	

    memory_ = new Memory(file_name);
	debug_mode_ = debug_mode;
}

Simulator::~Simulator() {

	delete memory_;
}

int Simulator::GetPc() {

    return memory_->GetValue(0);
}

void Simulator::SetPc(int pc) {

    memory_->SetValue(0, pc);
}

void Simulator::RunSimulator() {
    
    int program_counter;

    do {
        program_counter = GetPc();
        instruction_set_.at(program_counter).Execute(memory_);

        // If the last instruction hasn't changed the PC, then increment it
        if (program_counter == GetPc())
            SetPc(++program_counter);

        if (debug_mode_ == 1)
            cout << *memory_;

    } while (program_counter < instruction_set_.size());
}