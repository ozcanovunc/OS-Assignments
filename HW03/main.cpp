#include "helper.h"
#include "memory.h"
#include "instruction.h"
#include "simulator.h"
#include "page.h"

int main(int argc, char** argv) {
	
#if 0
	if (argc != 4) {
		cerr << "Usage: ./Simulate [PROGRAM] -D [MODE]" << endl;
		cerr << "Example: ./Simulate pr.txt -D 0" << endl;
		exit(EXIT_FAILURE);
	}

	Simulator* sim = new Simulator(argv[1], atoi(argv[3]));
	sim->RunSimulator();
	delete sim;
	return EXIT_SUCCESS;
#endif

}