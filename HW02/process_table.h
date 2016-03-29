#pragma once 

#include "process.h"

class ProcessTable {

public:
	bool IsEmpty();
	Process* PopProcess();
	void PushProcess(Process* process);

private:
    std::queue<Process*> process_table_;
};