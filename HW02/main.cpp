#include "helper.h"
#include "memory.h"
#include "instruction.h"
#include "process.h"
#include "process_table.h"

string instruction_types[] = {"UNDEFINED", "NOP", "SET", "CPY", "CPYI", 
"CPYI2", "ADD", "ADDI", "SUBI", "JIF", "HLT", "FORK", "PRN"};

int main(int argc, char** argv) {

	if (argc != 4) {
		cerr << "Usage: ./Simulate [PROGRAM] -D [MODE]" << endl;
		cerr << "Example: ./Simulate pr.txt -D 0" << endl;
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));

	Memory* mem = new Memory();
	ProcessTable* process_table = new ProcessTable();
	Process* curr_process;
	string last_process = "INIT";
	int debug_mode = atoi(argv[3]);

	// Create the first process and push it to the table
	Process* first_process = new Process(argv[1], mem, 0);
	process_table->PushProcess(first_process);

	if (debug_mode == 3) {
		cout << "New process created\n" << *first_process << endl;
	}

	// Infinite loop for CPU ticks
	for (int ticks = 0; ; ++ticks) {

		if (!process_table->IsEmpty()) {
			curr_process = process_table->PopProcess();

			// Process switch occured - Debug mode: 2
			if (debug_mode == 2 && last_process.compare(curr_process->GetName())) {
				cout << "CPU Tick: " << ticks << " /// Switched from \"" 
				<< last_process << "\" to \"" << curr_process->GetName() 
				<< "\"" << endl;
			}
		}
		// No process to execute left
		else{
			break;
		}

		string curr_instruction;
		bool found;
		int ticks_spent = 0;

		// Round robin with a quantum of 5 ticks
		while (curr_instruction.compare("HLT") && ticks_spent < 5) {

			curr_instruction = curr_process->ExecuteCurrentInstruction(mem);

			found = false;
			++ticks_spent;

			if (debug_mode == 1) {
				cout << *mem << endl;
			}

			for (type : instruction_types) {
				// If it's not one of our types, it must be EXEC instruction
				// Because it returns the program name to be executed
				if (curr_instruction.compare(type) == 0)
					found = true;
			}

			// Current instruction is a system call, spend some ticks between 5 - 10
			// FORK
			/*
			if (found && curr_instruction.compare("FORK") == 0) {
				ticks_spent += WaitRandomBetween(5, 10);
			}
			*/
			// PRN
			if (found && curr_instruction.compare("PRN") == 0) {
				ticks_spent += WaitRandomBetween(5, 10);
			}
			// EXEC
			if (!found) {
				ticks_spent += WaitRandomBetween(5, 10);

				// Create new process
				Process* p = new Process(curr_instruction, mem, 
					ticks + ticks_spent, curr_process->GetPid());
				process_table->PushProcess(p);

				if (debug_mode == 3) {
					cout << "New process created\n" << *p << endl;
				}
			}
		}

		ticks += ticks_spent;

		// Update execution time
		int exe_time = curr_process->GetExecutionTime() + ticks_spent;
		curr_process->SetExecutionTime(exe_time);

		// Current process has instructions to execute left
		if (curr_instruction.compare("HLT")) {
			// Current process is now blocked
			curr_process->SetState(READY);
			// Push the current process to the end of the queue
			process_table->PushProcess(curr_process);
			last_process = curr_process->GetName();
		}
		else {
			last_process = curr_process->GetName();

			if (debug_mode == 0)
				cout << *mem << endl;

			delete curr_process;
		}
	} // for

	return EXIT_SUCCESS;
}