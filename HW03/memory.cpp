#include "helper.h"
#include "memory.h"
#include "page.h"

Memory::Memory(string file_name, int debug_mode) {

    ifstream file(file_name.c_str());
    string line;
    int num_of_contents = 0,
    	max_page_size = Page::GetMaxPageSize(),
    	num_of_pages;

    while (getline(file, line))
    {
    	// Get contents of each memory location
    	if (line.find("Begin Data Section") != string::npos) {
    	    while (getline(file, line) && 
    	    	line.find("End Data Section") == string::npos) {
    	    	++num_of_contents;
    	    }
    	}
    }

    // Calculate number of pages needed
    num_of_pages = num_of_contents / max_page_size;
    if (num_of_contents % max_page_size != 0) {
    	++num_of_pages;
    }

    // Create pages, put them into the disk
    for (int pi = 0; pi < num_of_pages; ++pi) {
    	Page* page = new Page(file_name, pi);
    	disk_mem_.push_back(page);
    }

    // Number of pages in memory
    pages_in_memory_ = 0;

    debug_mode_ = debug_mode;
}

Page* Memory::PageFaultHandler(int addr) {

	int page_frame = addr / Page::GetMaxPageSize();
	bool page_fault_occured = true;
	Page* page;

	// Search the page in physical memory
	for (int pi = 0; pi < physical_mem_.size(); ++pi) {

		Page* temp = physical_mem_.at(pi);
		if (temp->GetFrameNumber() == page_frame) {
			// Page found in physical memory
			page = temp;
			page_fault_occured = false;
		}
	}

	if (page_fault_occured) {

		// Search for the page in the disk
		for (int pi = 0; pi < disk_mem_.size(); ++pi) {

			Page* temp = disk_mem_.at(pi);
			if (temp->GetFrameNumber() == page_frame) {
				page = temp;
			}
		}

		// There is a place for a new page in memory
		if (pages_in_memory_ < Page::GetMaxPageCount()) {

			physical_mem_.push_back(page);
			++pages_in_memory_;

			if (debug_mode_ == 3) {
				cout << "There is a page fault but no replacement" << endl;
			}
		}
		// Page replacement
		else {

			Page* temp = physical_mem_.front();
			int frame = temp->GetFrameNumber();

			// Update the disk
			for (int pi = 0; pi < disk_mem_.size(); ++pi) {
				if (disk_mem_.at(pi)->GetFrameNumber() == frame) {
					disk_mem_[pi] = temp;
				}
			}

			physical_mem_.push_back(page);

			if (debug_mode_ == 3) {
				cout << "There is a page fault and replacement" << endl;
				cout << frame << " and " << page->GetFrameNumber() << 
				" replaced" << endl;
			}
		}
	} // Page fault handling

	return page;
}

int Memory::GetValue(int addr) {

	Page* page = PageFaultHandler(addr);
	return page->GetValue(addr);
}

void Memory::SetValue(int addr, int val) {

	Page* page = PageFaultHandler(addr);
	page->SetValue(addr, val);
}

void Memory::PrintPageTable() {

	cout << "PAGES IN MEMORY" << endl;

	for (int pi = 0; pi < pages_in_memory_; ++pi) {
		Page* page = physical_mem_.at(pi);
		cout << "Page " << page->GetFrameNumber() << endl;
	}

	cout << endl;
}

ostream& operator<<(ostream& os, const Memory& mem) {

	for (int pi = 0; pi < mem.pages_in_memory_; ++pi) {
		Page* page = mem.physical_mem_.at(pi);
		os << *page << endl;
	}

	os << endl;
	return os;
}