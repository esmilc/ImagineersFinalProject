#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "heap.cpp"
using namespace std;


int rawTimetoFormatted(string sTime){
    //The purpose of this function is to convert time from a string input on the format HH:MM:SS
    //into an integer of minutes past midnight, as they are easier to work with

    //09:03:15 Example of time (Seconds are negligable) -> 543
    string sHour = sTime.substr(0, 2);
    string sMinute = sTime.substr(3, 2);
    int hour = stoi(sHour);
    int minute = stoi(sMinute);
    
    return (hour*60) + (minute);
}

string minutesToStandard(int input) {
    string toReturn = "";
    int hours = input/60;
    int minutes = input % 60;
    if (minutes < 10) {
        toReturn = to_string(hours) + ":0" + to_string(minutes);
    }
    else {
        toReturn =  (to_string(hours) + ":" + to_string(minutes));
    }
    return toReturn;

}

bool parseFileInHeap(string filename, string date, MinHeap& heap){ //I have the prefix, FOLDER NAME CANNOT CHANGE
    //The purpose of this funtion is to take in the file name, date the user inputted, and the heap and enter all of the
    //ride information into the heap. return is irrelevant, it's just there to exit out of the function if the files is
    //unable to open
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
        string splitLine[3];
        int index = 0;
        bool isValid = true;

        while (getline(ss, word, ',')) {
            if (index == 1 && word.substr(8,2) != date) {
                isValid = false;
                break;
            }
            splitLine[index] = word;
            index ++;
        }

        if (isValid) {
            //Push into heap here
            int time = rawTimetoFormatted(splitLine[1].substr(11,8));
            heap.push(splitLine[0],time, stoi(splitLine[2]));

        }
    }

    return true;
}



