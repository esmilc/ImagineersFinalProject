

#include <iostream>
#include <map>
#include <set>
#include <utility>
#include "user_io.h"
using namespace std;

int rawTimetoFormattedValidation(string sTime){
    //The purpose of this function is to convert time from a string input on the format HH:MM
    //into an integer of minutes past midnight, as they are easier to work with with validation

    //09:03 Example of time (Seconds are negligable) -> 543
    string sHour = sTime.substr(0, 2);
    string sMinute = sTime.substr(3, 2);
    try {
        int hour = stoi(sHour);
        int minute = stoi(sMinute);
        if (hour >= 0 && hour < 24 && minute >= 0 && minute < 60) {
            return (hour*60) + (minute);
        }
        return -1;
    }
    catch (const std::invalid_argument & e) {
        return -1;
    }
}

string getInputInitial() {
    //The purpose of this function is to facilitate grabbing input from the users
    string x;
    getline(cin, x);
    return x;
}

int getInputNumber() {
    //Purpose of this function is to grab input from the user, this function also validates that the input is a number
    //between 0 and 34.
    string x;
    int toReturn;
    getline(cin, x);
    try {
        toReturn = stoi(x);
        if (toReturn > 34 || toReturn < 0) {
            toReturn = -1;
        }
    }
    catch (const std::invalid_argument & e) {
        toReturn = -1;
    }
    return toReturn;

}

int getArrivalTime() {
    //The Purppose of this function is to get the arrival time of the user. If the time entered is not correct, -1 will be returned.
    //Park opens at 09:00 (540 mins) and limit last time of arrival to 21:00 (1260 mins)
    string x;
    int toReturn;
    getline(cin, x);
    toReturn = rawTimetoFormattedValidation(x);
    cout << toReturn << endl;
    if (toReturn > 1260 || toReturn < 540) {
        toReturn = -1;
    }
    return toReturn;
}

 pair<int, vector<string>> printWelcomeMessage(map<string, string> rideMap, string keys[]) {
    //The purpose of this function is to print a welcome message and grab input from the user
    //in a loop until the user inputs DONE, at that point the function will return a vector of
    //strings with NO DUPLICATES with the files to sort.

    cout << "Plan your ideal Magic Kingdom Visit!" << endl;

    cout << "What time do you plan on arriving? Enter as HH:MM (24hr).\nEnter hours between 09:00 and 21:00." << endl;;
    int arrivalTime = getArrivalTime();
    while (arrivalTime == -1) {
        cout << "INVALID INPUT...Enter hours between 09:00 and 21:00." << endl;
        arrivalTime = getArrivalTime();
    }


    bool continueInput = true;
    vector<string> toReturnUser;
    cout << "Here is a list of all of the available rides: " <<"\n===+===+===+===+===+===+===+===+===+===+===+===" <<endl;
    int num = 1;
    for (auto const& x : rideMap)
    {
        cout << num << ". " << x.first << " " << endl;
        num++;
    }
    cout << "===+===+===+===+===+===+===+===+===+===+===+===" << endl;
    cout << "Enter number of ride you wish to go on. Once finished please enter 0" << endl;

    while (continueInput){
        int input = getInputNumber();
        if (input == 0) {
            continueInput = false;
        }
        else if (input == -1) {
            cout << "INVALID INPUT...Remember to input numbers between 1 & 34" << endl;
        }
        else {
            int x = 0;
            while(x < toReturnUser.size()) {
                if(toReturnUser[x] == rideMap[keys[input-1]]) {
                    break;
                }
                x++;
            }
            if(x == toReturnUser.size()) {
                toReturnUser.push_back(rideMap[keys[input-1]]);
            }
        }
    }
    pair<int, vector<string>> toReturn(arrivalTime, toReturnUser);
    return toReturn;
}

string getDate() {
    //The purpose of this function is to get the day of the month from the user, if the date is invalid, it will repeat
    //asking until the the date is valid
    cout << "Please enter date that you are going to be visiting Disney! (Must be a 2 digit number between 1-31): " << endl;
    string input = getInputInitial();
    while (input.length() != 2) { // this makes sure input is 2 in length..more like forces it l0l
        cout << "WARNING: Bruv, input has to be 2 numbers init" << endl;
        input = getInputInitial();
    }
    return input;
}
