#ifndef FILE_PARSING_H
#define FILE_PARSING_H

#include <string>
#include "heap.h"
using namespace std;


int rawTimetoFormatted(string sTime);
string minutesToStandard(int input);
bool parseFileInHeap(string filename, string date, MinHeap& heap);

#endif // FILE_PARSING_H