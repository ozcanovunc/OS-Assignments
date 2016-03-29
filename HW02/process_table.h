#pragma once 

#include "process.h"

class ProcessTable {

public:
	bool IsEmpty();
	int GetSize();
	Process* PopProcess();
	void PushProcess(Process* process);

private:
    std::queue<Process*> process_table_;
};