#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "heap.cpp"
using namespace std;


int rawTimetoFormatted(string sTime){
    //09:03:15 Example of time (Seconds are negligable) -> 543
    string sHour = sTime.substr(0, 2);
    string sMinute = sTime.substr(3, 2);
    int hour = stoi(sHour);
    int minute = stoi(sMinute);
    
    return (hour*60) + (minute);
}

bool parseFile(string filename, string date){ //I have the prefix, FOLDER NAME CANNOT CHANGE
    string prefix = "../rides_wait_time/";
    string path = prefix + filename;
    ifstream file(path);

    if (!file.is_open()){
        cout << filename << " could not open properly bro!!" << endl;
        cout << "Is the folder name still called: " << prefix << "?" << endl;
        return false;
    }

    string line;
    while (getline(file, line)){
        istringstream ss(line);
        string word;
        vector<string> splitLine;

        while (getline(ss, word, ',')){
            splitLine.push_back(word);
        }

        cout << splitLine[0] << " " << splitLine[3] << endl;



    }

    return true;
}


