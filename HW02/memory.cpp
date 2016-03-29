#include "helper.h"
#include "memory.h"

void Memory::AllocMemoryForNewProcess(string file_name, int& base, int& limit) {

    ifstream file(file_name.c_str());
    string line, content;
    int mem_address = -1;
    int value;

    while (getline(file, line))
    {
    	// Get contents of each memory location
    	if (line.find("Begin Data Section") != string::npos) {
    	    while (getline(file, line) && 
    	    	line.find("End Data Section") == string::npos) {

    	    	++mem_address;
                content = GetNthWordFromString(line, ' ', 2);

                // Decide whether content denotes a character or not
                if (content.c_str()[0] == '\'') {
                    value = (int)content.c_str()[1];
                }
    	    	else {
                    value = atoi(content.c_str());
                }

    	    	mem_content_.push_back(value);

    	    	// Set base and limit registers
    	    	if (mem_address == 2) {
    	    		base = value;
    	    	}
    	    	else if (mem_address == 3) {
    	    		limit = value;	
    	    	}   	    	
    	    }
    	}
    }
}

int Memory::GetValue(int addr) {

	if (mem_content_.size() -1 < addr && addr < 0) {
		cerr << "Cannot access memory at address " << addr << endl;
		exit(EXIT_FAILURE);
	}
	return mem_content_.at(addr);
}

void Memory::SetValue(int addr, int val) {

	if (mem_content_.size() -1 < addr && addr < 0) {
		cerr << "Cannot access memory at address " << addr << endl;
		exit(EXIT_FAILURE);
	}

	mem_content_.at(addr) = val;
}

ostream& operator<<(ostream& os, const Memory& mem) {

	for (int i = 0; i < mem.mem_content_.size(); ++i) {

		if (i % 10 == 0)
			os << endl;
		os << i << " " << mem.mem_content_.at(i) << ", ";	
	}

	os << endl;
	return os;
}