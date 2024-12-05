
#include <string>
#include "heap.h"
#include "BPlusTree.h"
using namespace std;


int rawTimetoFormatted(string sTime); // O(1)
string minutesToStandard(int input); // O(1)
bool parseFileInHeap(string filename, string date, MinHeap& heap); // O(n log k) n is num lines in file, k is num of rides inserted into the min heap
bool parseFileInTree(string filename, string date, BPlusTree& tree);//

/*

rawTimetoFormatted:
    The purpose of this function is to convert time from a string input on the format HH:MM:SS
    into an integer of minutes past midnight, as they are easier to work with. [Validation should
    be added] #FIXME

minutesToStandard:
    Converts minutes past midnight to regular standard time...24-hour format

parseFilesInHeap:
    The purpose of this function is to take in the file name, date the user inputted, and the heap and enter all of the
    ride information into the heap. return is irrelevant, it's just there to exit out of the function if the files is
    unable to open.

 */
