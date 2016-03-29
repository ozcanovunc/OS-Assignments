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
string Instruction::Execute(Memory* mem, int base_reg) {

	// Program counter values	
	int 	former_pc = mem->GetValue(base_reg), 
			current_pc;

	string result = "";
	
	switch (GetType()) {

		case UNDEFINED:
			result = ExecuteUndefined(mem, base_reg);
			break;
		case NOP:
			result = ExecuteNop(mem, base_reg);
			break;
		case SET:
			result = ExecuteSet(mem, base_reg);
			break;
		case CPY:
			result = ExecuteCpy(mem, base_reg);
			break;
		case CPYI:
			result = ExecuteCpyi(mem, base_reg);
			break;		
		case CPYI2:
			result = ExecuteCpyi2(mem, base_reg);
			break;
		case ADD:
			result = ExecuteAdd(mem, base_reg);
			break;
		case ADDI:
			result = ExecuteAddi(mem, base_reg);
			break;
		case SUBI:
			result = ExecuteSubi(mem, base_reg);
			break;
		case JIF:
			result = ExecuteJif(mem, base_reg);
			break;
		case HLT:
			result = ExecuteHlt(mem, base_reg);
			break;
		case FORK:
			result = ExecuteCallFork(mem, base_reg);
			break;
		case PRN:
			result = ExecuteCallPrn(mem, base_reg);
			break;
		case EXEC:
			result = ExecuteCallExec(mem, base_reg);
			break;
		default:
			result = ExecuteUndefined(mem, base_reg);
			break;
	}

	// Get the current program counter
	current_pc = mem->GetValue(base_reg);

	// Update the PC
	if (former_pc == current_pc)
		mem->SetValue(base_reg, current_pc + 1);

	return result;
}

string Instruction::ExecuteUndefined(Memory* mem, int base_reg) {

	return "UNDEFINED";
}

string Instruction::ExecuteNop(Memory* mem, int base_reg) {

	return "NOP";
}

// SET B A -> Set the Ath memory location with number B
string Instruction::ExecuteSet(Memory* mem, int base_reg) {

	mem->SetValue(GetSecondOp() + base_reg, GetFirstOp());
	return "SET";
}

// CPY A1 A2 -> Copy the content of memory location A1 to memory A2
string Instruction::ExecuteCpy(Memory* mem, int base_reg) {

	int first_content = mem->GetValue(GetFirstOp() + base_reg);
	mem->SetValue(GetSecondOp() + base_reg, first_content);
	return "CPY";
}

// CPYI A1 A2 -> Copy contents of pointed by A1 to memory location A2
string Instruction::ExecuteCpyi(Memory* mem, int base_reg) {

	int first_content = mem->GetValue(GetFirstOp() + base_reg);
	mem->SetValue(GetSecondOp() + base_reg, mem->GetValue(first_content));
	return "CPYI";
}

// CPYI2 A1 A2 -> Copy content of A1 to the memory adress indexed by A2
string Instruction::ExecuteCpyi2(Memory* mem, int base_reg) {

	int 	first_content = mem->GetValue(GetFirstOp() + base_reg),
			second_content = mem->GetValue(GetSecondOp() + base_reg);

	mem->SetValue(second_content + base_reg, first_content);
	return "CPYI2";
}

// ADD B A -> Add number B to memory location A
string Instruction::ExecuteAdd(Memory* mem, int base_reg) {

	int second_content = mem->GetValue(GetSecondOp() + base_reg);
	mem->SetValue(GetSecondOp() + base_reg, GetFirstOp() + second_content);
	return "ADD";
}

// ADDI A1 A2 -> Add the contents of memory address A1 to address A2
string Instruction::ExecuteAddi(Memory* mem, int base_reg) {
	
	int 	first_content = mem->GetValue(GetFirstOp() + base_reg),
			second_content = mem->GetValue(GetSecondOp() + base_reg);

	mem->SetValue(GetSecondOp() + base_reg, first_content + second_content);
	return "ADDI";
}

// SUBI A1 A2 -> Subtract the contents of A2 from A1 put it in A2
string Instruction::ExecuteSubi(Memory* mem, int base_reg) {

	int 	first_content = mem->GetValue(GetFirstOp() + base_reg),
			second_content = mem->GetValue(GetSecondOp() + base_reg),
			result = first_content - second_content;

	mem->SetValue(GetSecondOp() + base_reg, result);
	return "SUBI";
}

// JIF A C -> Set PC with C if memory location A content is less than or equal to 0
string Instruction::ExecuteJif(Memory* mem, int base_reg) {

	int first_content = mem->GetValue(GetFirstOp() + base_reg);
	if (first_content <= 0)
		mem->SetValue(base_reg, GetSecondOp()); // Set PC (Memory location 0)
	return "JIF";
}

// HLT -> Shuts down the CPU
string Instruction::ExecuteHlt(Memory* mem, int base_reg) {
	
	return "HLT";
}

// CALL FORK -> Works like the fork system call of UNIX systems
string Instruction::ExecuteCallFork(Memory* mem, int base_reg) {

	return "FORK";
}

// CALL PRN A ->Prints the contents of memory address A to the console
string Instruction::ExecuteCallPrn(Memory* mem, int base_reg) {

	int first_content = mem->GetValue(GetFirstOp() + base_reg);
	cout << first_content << endl;
	return "PRN";
}

// CALL EXEC A -> Loads the program specified in the file name
string Instruction::ExecuteCallExec(Memory* mem, int base_reg) {
	
	int 	address = GetFirstOp() + base_reg,
			first_content;
	char 	c;
	string 	file_name;

	do {
		first_content = mem->GetValue(address++);
		c = (char)first_content;
		file_name.append(1, c);
	} while (c);

	return file_name;
}