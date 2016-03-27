#pragma once

class Memory {

public:
	void AllocMemoryForNewProcess(std::string file_name, int& base, int& limit);
	int GetValue(int addr);
	void SetValue(int addr, int val);
	friend std::ostream& operator<<(std::ostream& os, const Memory& mem);

private:
	std::vector<int> mem_content_;
};