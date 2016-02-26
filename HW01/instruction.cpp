#include "helper.h"
#include "instruction.h"

Instruction::Instruction(string instruction_str) {

	string type = GetNthWordFromString(instruction_str, ' ', 2);
	first_op_ = atoi(GetNthWordFromString(instruction_str, ' ', 3).c_str());
	second_op_ = atoi(GetNthWordFromString(instruction_str, ' ', 4).c_str());
	comment_ = GetNthWordFromString(instruction_str, '#', 2);

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

bool Instruction::Execute(Memory* mem) {

	switch (GetType()) {

		case UNDEFINED:
			return ExecuteUndefined(mem);
			break;
		case NOP:
			return ExecuteNop(mem); // Increment PC by 1
			break;
		case SET:
			return ExecuteSet(mem);
			break;
		case CPY:
			return ExecuteCpy(mem);
			break;
		case CPYI:
			return ExecuteCpyi(mem);
			break;
		case ADD:
			return ExecuteAdd(mem);
			break;
		case ADDI:
			return ExecuteAddi(mem);
			break;
		case JIF:
			return ExecuteJif(mem);
			break;
		case HLT:
			return ExecuteHlt(mem);
			break;
		default:
			return ExecuteUndefined(mem);
			break;
	}
}

bool Instruction::ExecuteUndefined(Memory* mem) {

	ExecuteNop(mem); // Increment PC by 1
	return false;
}

bool Instruction::ExecuteNop(Memory* mem) {

	mem->SetValue(0, mem->GetValue(0) + 1);
	return true;
}

// SET B A -> Set the Ath memory location with number B
bool Instruction::ExecuteSet(Memory* mem) {

	mem->SetValue(GetSecondOp(), GetFirstOp());
	return true;
}

// CPY A1 A2 -> Copy the content of memory location A1 to memory A2
bool Instruction::ExecuteCpy(Memory* mem) {

	int val = mem->GetValue(GetFirstOp());
	mem->SetValue(GetSecondOp(), val);
	return true;
}

// CPYI A1 A2 -> Copy contents of pointed by A1 to memory location A2
bool Instruction::ExecuteCpyi(Memory* mem) {

	int val = mem->GetValue(mem->GetValue(GetFirstOp()));
	mem->SetValue(GetSecondOp(), val);
	return true;
}

// ADD B A -> Add number B to memory location A
bool Instruction::ExecuteAdd(Memory* mem) {

	int val = mem->GetValue(GetSecondOp());
	mem->SetValue(GetSecondOp(), val + GetFirstOp());
	return true;
}

// ADDI A1 A2 -> Add the contents of memory address A2 to address A1
bool Instruction::ExecuteAddi(Memory* mem) {
	
	int 	val_first_addr = mem->GetValue(GetFirstOp()),
			val_second_addr = mem->GetValue(GetSecondOp());

	mem->SetValue(GetFirstOp(), val_first_addr + val_second_addr);
	return true;
}

// JIF A C -> Set PC with C if memory location A content is less than or equal to 0
bool Instruction::ExecuteJif(Memory* mem) {

	int val = mem->GetValue(GetFirstOp());
	if (val <= 0)
		mem->SetValue(0, GetSecondOp());
	return true;
}

// HLT -> Shuts down the CPU
bool Instruction::ExecuteHlt(Memory* mem) {
	
	cout << *mem;
	return true;
}