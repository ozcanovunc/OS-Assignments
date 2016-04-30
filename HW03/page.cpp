#include "helper.h"
#include "page.h"

const int Page::max_size_ = pow(2, 6);
const int Page::max_pages_in_mem_ = 8;

Page::Page(string file_name, int frame_number) {

    ifstream file(file_name.c_str());
    string line;
    int index = 0;

    while (getline(file, line))
    {
    	// Get contents of each memory location
    	if (line.find("Begin Data Section") != string::npos) {
    	    while (getline(file, line) && 
    	    	line.find("End Data Section") == string::npos) {
    	    	if (index >= max_size_ * frame_number && 
    	    		index < max_size_ * (frame_number + 1)) {
    	    		mem_content_.push_back(atoi(
    	    			GetNthWordFromString(line, ' ', 2).c_str()));
    	    	}
    	    	++index;
    	    }
    	}
    }

    // TODO: Update this!!!
    frame_number_ = frame_number;
    modified_bit_ = 0;
    referenced_bit_ = 0;
    present_bit_ = 0;
}

int Page::GetValue(int addr) {

	int index = addr % max_size_;
/*
	if (mem_content_.size() -1 < index && index < 0) {
		cerr << "Cannot access memory at address " << addr << endl;
		exit(EXIT_FAILURE);
	}
*/
	return mem_content_.at(index);
}

void Page::SetValue(int addr, int val) {

	int index = addr % max_size_;
/*
	if (mem_content_.size() -1 < index && index < 0) {
		cerr << "Cannot access memory at address " << addr << endl;
		exit(EXIT_FAILURE);
	}
*/
	mem_content_.at(index) = val;
}

int Page::GetFrameNumber() {
    return frame_number_;
}

int Page::GetMaxPageSize() {
    return Page::max_size_;
}

int Page::GetMaxPageCount() {
    return Page::max_pages_in_mem_;
}

ostream& operator<<(ostream& os, const Page& page) {

    os << "Page number " << page.frame_number_ << endl;

    for (int i = 0; i < page.mem_content_.size(); ++i) {

        if (i % 10 == 0)
            os << endl;
        os << i << " " << page.mem_content_.at(i) << ", ";   
    }

    os << endl;
    return os;
}