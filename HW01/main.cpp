#include "helper.h"
#include "memory.h"
#include "instruction.h"
#include "simulator.h"

int main(int argc, char** argv) {

	if (argc != 4) {
		cerr << "Usage: ./simulator [PROGRAM] -D [MODE]" << endl;
		cerr << "Example: ./simulator pr.txt -D 0" << endl;
		exit(EXIT_FAILURE);
	}

	Simulator* sim = new Simulator(argv[1], atoi(argv[3]));
	sim->RunSimulator();
	delete sim;
	return EXIT_SUCCESS;
}