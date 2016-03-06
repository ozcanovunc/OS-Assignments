#include "helper.h"
#include "instruction.h"

Instruction::Instruction(string instruction_str) {

	string type = GetNthWordFromString(instruction_str, ' ', 2);
	first_op_ = atoi(GetNthWordFromString(instruction_str, ' ', 3).c_str());
	second_op_ = atoi(GetNthWordFromString(instruction_str, ' ', 4).c_str());
	comment_ = GetNthWordFromString(instruction_str, '#', 2);
	instruction_ = instruction_str;

	if (type == "NOP")
		type_ = NOP;
	else if (type == "SET")
		type_ = SET;
	else if (type == "CPY")
		type_ = CPY;
	else if (type == "CPYI")
		type_ = CPYI;
	else if (type == "ADD")
		type_ = ADD;
	else if (type == "ADDI")
		type_ = ADDI;
	else if (type_ == "SUBI")
		type = SUBI;
	else if (type == "JIF")
		type_ = JIF;
	else if (type == "HLT")
		type_ = HLT;
	else 
		type_ = UNDEFINED;
}

Instruction::InstructionType Instruction::GetType() {

	return type_;
}

int Instruction::GetFirstOp() {

	return first_op_;
}

int Instruction::GetSecondOp() {

	return second_op_;
}

string Instruction::GetComment() {

	return comment_;
}
string Instruction::GetInstructionString() {

	return instruction_;
}

bool Instruction::Execute(Memory* mem) {

	// Program counter values	
	int 	former_pc = mem->GetValue(0), 
			current_pc;

	bool is_successful = false;
	
	switch (GetType()) {

		case UNDEFINED:
			is_successful = ExecuteUndefined(mem);
			break;
		case NOP:
			is_successful = ExecuteNop(mem);
			break;
		case SET:
			is_successful = ExecuteSet(mem);
			break;
		case CPY:
			is_successful = ExecuteCpy(mem);
			break;
		case CPYI:
			is_successful = ExecuteCpyi(mem);
			break;
		case ADD:
			is_successful = ExecuteAdd(mem);
			break;
		case ADDI:
			is_successful = ExecuteAddi(mem);
			break;
		case SUBI:
			is_successful = ExecuteSubi(mem);
			break;
		case JIF:
			is_successful = ExecuteJif(mem);
			break;
		case HLT:
			is_successful = ExecuteHlt(mem);
			break;
		default:
			is_successful = ExecuteUndefined(mem);
			break;
	}

	// Get the current program counter
	current_pc = mem->GetValue(0);

	// Update the PC
	if (former_pc == current_pc)
		mem->SetValue(0, current_pc + 1);

	return is_successful;
}

bool Instruction::ExecuteUndefined(Memory* mem) {

	return false;
}

bool Instruction::ExecuteNop(Memory* mem) {

	return true;
}

// SET B A -> Set the Ath memory location with number B
bool Instruction::ExecuteSet(Memory* mem) {

	mem->SetValue(GetSecondOp(), GetFirstOp());
	return true;
}

// CPY A1 A2 -> Copy the content of memory location A1 to memory A2
bool Instruction::ExecuteCpy(Memory* mem) {

	int first_content = mem->GetValue(GetFirstOp());
	mem->SetValue(GetSecondOp(), first_content);
	return true;
}

// CPYI A1 A2 -> Copy contents of pointed by A1 to memory location A2
bool Instruction::ExecuteCpyi(Memory* mem) {

	int first_content = mem->GetValue(GetFirstOp());
	mem->SetValue(GetSecondOp(), mem->GetValue(first_content));
	return true;
}

// ADD B A -> Add number B to memory location A
bool Instruction::ExecuteAdd(Memory* mem) {

	int second_content = mem->GetValue(GetSecondOp());
	mem->SetValue(GetSecondOp(), second_content + GetFirstOp());
	return true;
}

// ADDI A1 A2 -> Add the contents of memory address A1 to address A2
bool Instruction::ExecuteAddi(Memory* mem) {
	
	int 	first_content = mem->GetValue(GetFirstOp()),
			second_content = mem->GetValue(GetSecondOp());

	mem->SetValue(GetSecondOp(), first_content + second_content);
	return true;
}

// SUBI A1 A2 -> Subtract the contents of A2 from A1 put it in A2
bool Instruction::ExecuteSubi(Memory* mem) {

	int 	first_content = mem->GetValue(GetFirstOp()),
			second_content = mem->GetValue(GetSecondOp()),
			result = first_content - second_content;

	mem->SetValue(GetSecondOp(), result);
	return true;
}

// JIF A C -> Set PC with C if memory location A content is less than or equal to 0
bool Instruction::ExecuteJif(Memory* mem) {

	int first_content = mem->GetValue(GetFirstOp());
	if (first_content <= 0)
		mem->SetValue(0, GetSecondOp()); // Set PC (Memory location 0)
	return true;
}

// HLT -> Shuts down the CPU
bool Instruction::ExecuteHlt(Memory* mem) {
	
	cout << *mem << endl;
	return true;
}
