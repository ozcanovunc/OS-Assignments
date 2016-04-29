#pragma once

#include "helper.h"

class Page {

public:
	Page(string file_name, int frame_number);
	int GetValue(int addr);
	void SetValue(int addr, int val);

private:	
	// Could be 0 or 1
	int modified_bit_;
	int referenced_bit_;
	int present_bit_;
	int frame_number_;

	std::vector<int> mem_content_;

	const static int max_size_;
};