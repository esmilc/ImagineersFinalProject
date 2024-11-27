//
// Created by Esmil Canet on 11/26/24.
//

#include <map>
#include <string>
using namespace std;

// Function declarations

 pair<int, vector<string>> printWelcomeMessage(map<string, string> rideMap, string keys[]);
string getDate();
int rawTimetoFormattedValidation(string sTime);
string getInputInitial();
int getInputNumber();
int getArrivalTime();

/*
printWelcomeMessage:
    The purpose of this function is to print a welcome message and grab input from the user
    in a loop until the user inputs DONE, at that point the function will return a vector of
    strings with NO DUPLICATES with the files to sort. This function returns a pair, first being
    the arrival time while second being the vector of files to parse.

getDate:
    The purpose of this function is to get the day of the month from the user, if the date is invalid, it will repeat
    asking until the date is valid

rawTimeToFormattedValidation:
    The purpose of this function is to convert time from a string input on the format HH:MM
    into an integer of minutes past midnight, as they are easier to work with with validation

getInputInitial:
    The purpose of this function is to facilitate grabbing input from the users

getInputNumber:
    Purpose of this function is to grab input from the user, this function also validates that the input is a number
    between 0 and 34.

getArrivalTime:
    The purpose of this function is to get the arrival time of the user.
    If the time entered is not correct, -1 will be returned.

 */