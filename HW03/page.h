#pragma once

#include "helper.h"

class Page {

public:
	Page(string file_name, int frame_number);
	int GetValue(int addr);
	void SetValue(int addr, int val);
	int GetFrameNumber();
	static int GetMaxPageSize();
	static int GetMaxPageCount();
	friend std::ostream& operator<<(std::ostream& os, const Page& page);

private:	
	int frame_number_;

	std::vector<int> mem_content_;

	// Maximum size of a page
	const static int max_size_;

	// Max number of pages in physical memory
	const static int max_pages_in_mem_;
};