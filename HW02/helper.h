#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <vector>
#include <exception>

using namespace std;

std::string GetNthWordFromString(std::string str, char delim_chr, int word_num);
int WaitRandomBetween(int min_ticks, int max_ticks);