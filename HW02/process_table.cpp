#include "helper.h"
#include "process_table.h"

bool ProcessTable::IsEmpty(){
	return process_table_.empty();
}

Process* ProcessTable::PopProcess(){
	Process* p = process_table_.front();
	process_table_.pop();
	return p;
}

void ProcessTable::PushProcess(Process* process){
	process_table_.push(process);
}