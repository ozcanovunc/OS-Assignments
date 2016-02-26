#pragma once

class Memory {

public:
	Memory(std::string file_name);
	int GetValue(int addr);
	void SetValue(int addr, int val);
	friend std::ostream& operator<<(std::ostream& os, const Memory& mem);

private:
	std::vector<int> mem_content_;
};