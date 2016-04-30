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

    memory_ = new Memory(file_name, debug_mode);
	debug_mode_ = debug_mode;
}

Simulator::~Simulator() {

	delete memory_;
}

int Simulator::GetPc() {

    return memory_->GetValue(0);
}

void Simulator::RunSimulator() {
    
    int program_counter = GetPc();
    string pause_debug;

    do {
    	if (debug_mode_ == 1 || debug_mode_ == 2) {
    		// Print the current instruction
    		cout << endl << "--------------------------------------------------" 
    		<< endl << endl << instruction_set_.at(program_counter).
    		GetInstructionString() << endl;
    	}

    	// Execute current instruction
        instruction_set_.at(program_counter).Execute(memory_);
        program_counter = GetPc();

        if ((debug_mode_ == 1 || debug_mode_ == 2) 
			&& program_counter < instruction_set_.size()) {
        	// Print the contents of the memory in debug mode
    		cout << endl << *memory_;
            memory_->PrintPageTable();
        }

        if (debug_mode_ == 2 && program_counter < instruction_set_.size()) {
        	// Pause simulator in debug mode 2
			getline(cin, pause_debug);
        }

    } while (program_counter < instruction_set_.size());
}