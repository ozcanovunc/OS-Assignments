#pragma once

#include "page.h"

class Memory {

public:
	Memory(std::string file_name, int debug_mode);
	Page* PageFaultHandler(int addr);
	int GetValue(int addr);
	void SetValue(int addr, int val);
	void PrintPageTable();
	friend std::ostream& operator<<(std::ostream& os, const Memory& mem);

private:
	int debug_mode_;
	int pages_in_memory_;

	// Queue structure has been used in order to simulate "Second Chance FIFO"
	std::deque<Page*> physical_mem_;
	std::vector<Page*> disk_mem_;
};