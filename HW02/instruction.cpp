#include "helper.h"
#include "instruction.h"

Instruction::Instruction(string instruction_str) {

	string type = GetNthWordFromString(instruction_str, ' ', 2);

	// If the instruction is not a system call
	if (type != "CALL") {

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
		else if (type == "CPYI2")
			type_ = CPYI2;
		else if (type == "ADD")
			type_ = ADD;
		else if (type == "ADDI")
			type_ = ADDI;
		else if (type == "SUBI")
			type_ = SUBI;
		else if (type == "JIF")
			type_ = JIF;
		else if (type == "HLT")
			type_ = HLT;
		else 
			type_ = UNDEFINED;
	}

	// Instruction is a system call
	else {

		// Get the type of the system call
		type = GetNthWordFromString(instruction_str, ' ', 3);

		if (type == "FORK") {
			first_op_ = 0;
			second_op_ = 0;
			comment_ = GetNthWordFromString(instruction_str, '#', 2);
			instruction_ = instruction_str;
			type_ = FORK;
		}
		else if (type == "PRN") {
			first_op_ = atoi(GetNthWordFromString(instruction_str, ' ', 4).c_str());
			second_op_ = 0;
			comment_ = GetNthWordFromString(instruction_str, '#', 2);
			instruction_ = instruction_str;
			type_ = PRN;
		}
		else if (type == "EXEC") {
			first_op_ = atoi(GetNthWordFromString(instruction_str, ' ', 4).c_str());
			second_op_ = 0;
			comment_ = GetNthWordFromString(instruction_str, '#', 2);
			instruction_ = instruction_str;
			type_ = EXEC;
		}
		else {
			type_ = UNDEFINED;
		}
	}
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

// TODO: Throw an exception "segmentation fault"
bool Instruction::Execute(Memory* mem, int base_reg) {

	// Program counter values	
	int 	former_pc = mem->GetValue(base_reg), 
			current_pc;

	bool is_successful = false;
	
	switch (GetType()) {

		case UNDEFINED:
			is_successful = ExecuteUndefined(mem, base_reg);
			break;
		case NOP:
			is_successful = ExecuteNop(mem, base_reg);
			break;
		case SET:
			is_successful = ExecuteSet(mem, base_reg);
			break;
		case CPY:
			is_successful = ExecuteCpy(mem, base_reg);
			break;
		case CPYI:
			is_successful = ExecuteCpyi(mem, base_reg);
			break;		
		case CPYI2:
			is_successful = ExecuteCpyi2(mem, base_reg);
			break;
		case ADD:
			is_successful = ExecuteAdd(mem, base_reg);
			break;
		case ADDI:
			is_successful = ExecuteAddi(mem, base_reg);
			break;
		case SUBI:
			is_successful = ExecuteSubi(mem, base_reg);
			break;
		case JIF:
			is_successful = ExecuteJif(mem, base_reg);
			break;
		case HLT:
			is_successful = ExecuteHlt(mem, base_reg);
			break;
		case FORK:
			is_successful = ExecuteCallFork(mem, base_reg);
			break;
		case PRN:
			is_successful = ExecuteCallPrn(mem, base_reg);
			break;
		case EXEC:
			is_successful = ExecuteCallExec(mem, base_reg);
			break;
		default:
			is_successful = ExecuteUndefined(mem, base_reg);
			break;
	}

	// Get the current program counter
	current_pc = mem->GetValue(base_reg);

	// Update the PC
	if (former_pc == current_pc)
		mem->SetValue(base_reg, current_pc + 1);

	return is_successful;
}

bool Instruction::ExecuteUndefined(Memory* mem, int base_reg) {

	return false;
}

bool Instruction::ExecuteNop(Memory* mem, int base_reg) {

	return true;
}

// SET B A -> Set the Ath memory location with number B
bool Instruction::ExecuteSet(Memory* mem, int base_reg) {

	mem->SetValue(GetSecondOp() + base_reg, GetFirstOp());
	return true;
}

// CPY A1 A2 -> Copy the content of memory location A1 to memory A2
bool Instruction::ExecuteCpy(Memory* mem, int base_reg) {

	int first_content = mem->GetValue(GetFirstOp() + base_reg);
	mem->SetValue(GetSecondOp() + base_reg, first_content);
	return true;
}

// CPYI A1 A2 -> Copy contents of pointed by A1 to memory location A2
bool Instruction::ExecuteCpyi(Memory* mem, int base_reg) {

	int first_content = mem->GetValue(GetFirstOp() + base_reg);
	mem->SetValue(GetSecondOp() + base_reg, mem->GetValue(first_content));
	return true;
}

// CPYI2 A1 A2 -> Copy content of A1 to the memory adress indexed by A2
bool Instruction::ExecuteCpyi2(Memory* mem, int base_reg) {

	int 	first_content = mem->GetValue(GetFirstOp() + base_reg),
			second_content = mem->GetValue(GetSecondOp() + base_reg);

	mem->SetValue(second_content + base_reg, first_content);
	return true;
}

// ADD B A -> Add number B to memory location A
bool Instruction::ExecuteAdd(Memory* mem, int base_reg) {

	int second_content = mem->GetValue(GetSecondOp() + base_reg);
	mem->SetValue(GetSecondOp() + base_reg, GetFirstOp() + second_content);
	return true;
}

// ADDI A1 A2 -> Add the contents of memory address A1 to address A2
bool Instruction::ExecuteAddi(Memory* mem, int base_reg) {
	
	int 	first_content = mem->GetValue(GetFirstOp() + base_reg),
			second_content = mem->GetValue(GetSecondOp() + base_reg);

	mem->SetValue(GetSecondOp() + base_reg, first_content + second_content);
	return true;
}

// SUBI A1 A2 -> Subtract the contents of A2 from A1 put it in A2
bool Instruction::ExecuteSubi(Memory* mem, int base_reg) {

	int 	first_content = mem->GetValue(GetFirstOp() + base_reg),
			second_content = mem->GetValue(GetSecondOp() + base_reg),
			result = first_content - second_content;

	mem->SetValue(GetSecondOp() + base_reg, result);
	return true;
}

// JIF A C -> Set PC with C if memory location A content is less than or equal to 0
bool Instruction::ExecuteJif(Memory* mem, int base_reg) {

	int first_content = mem->GetValue(GetFirstOp() + base_reg);
	if (first_content <= 0)
		mem->SetValue(base_reg, GetSecondOp()); // Set PC (Memory location 0)
	return true;
}

// HLT -> Shuts down the CPU
bool Instruction::ExecuteHlt(Memory* mem, int base_reg) {
	
	cout << *mem << endl;
	return false;
}

bool Instruction::ExecuteCallFork(Memory* mem, int base_reg) {

}

bool Instruction::ExecuteCallPrn(Memory* mem, int base_reg) {

}

bool Instruction::ExecuteCallExec(Memory* mem, int base_reg) {

}