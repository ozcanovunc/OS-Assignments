#include "helper.h"
#include "memory.h"
#include "instruction.h"
#include "process.h"

#define DEBUG

int main(int argc, char** argv) {

#ifndef DEBUG
	if (argc != 4) {
		cerr << "Usage: ./Simulate [PROGRAM] -D [MODE]" << endl;
		cerr << "Example: ./Simulate pr.txt -D 0" << endl;
		exit(EXIT_FAILURE);
	}

	Simulator* sim = new Simulator(argv[1], atoi(argv[3]));
	sim->RunSimulator();
	delete sim;
	return EXIT_SUCCESS;
#else


	Memory* m = new Memory();
	Process* p = new Process("sort.txt", m, 1);
	bool c = true;

	while (c) {
		c = p->ExecuteCurrentInstruction(m);
	}


#endif
}