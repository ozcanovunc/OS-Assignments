#include "helper.h"

string GetNthWordFromString(string str, char delim_chr, int word_num) {

	string::size_type	first_pos = 0, 
						last_pos = 0;

	string 	result = "",
			delim_str(1, delim_chr);

	if (str.find(delim_str) != string::npos && 
		count(str.begin(), str.end(), delim_chr) >= word_num - 1) {

		for (int i = 0; i < word_num; ++i) {

			first_pos = str.find_first_not_of(delim_str, last_pos); 
			last_pos = str.find_first_of(delim_str, first_pos);
		}

		result = str.substr(first_pos, last_pos - first_pos);
	}

	return result;
}