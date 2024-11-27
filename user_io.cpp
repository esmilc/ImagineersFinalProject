//
// Created by Esmil Canet on 11/26/24.
//

#include <iostream>
#include <map>
#include <set>
#include "user_io.h"
using namespace std;

string getInputInitial() {
    //The purpose of this function is to facilitate grabbing input from the users
    string x;
    getline(cin, x);
    return x;
}

vector<string> printWelcomeMessage(map<string, string> rideMap) {
    //The purpose of this function is to print a welcome message and grab input from the user
    //in a loop until the user inputs DONE, at that point the function will return a vector of
    //strings with NO DUPLICATES with the files to sort.

    cout << "Plan you ideal Magic Kingdom Visit!" << endl;
    bool continueInput = true;
    vector<string> toReturnUser;
    cout << "Here is a list of all of the available rides: " <<"\n===+===+===+===+===+===+===+===+===+===+===+===" <<endl;
    for (auto const& x : rideMap)
    {
        cout << x.first << " " << endl;
    }
    cout << "===+===+===+===+===+===+===+===+===+===+===+===" << endl;
    cout << "Enter name of ride you wish to go on, please type name in exactly (Case-Sensitive).Once finished please enter DONE" << endl;

    while (continueInput){
        string input = getInputInitial();
        if (input == "DONE") {
            continueInput = false;
        }
        else if (rideMap.count(input) == 0) {
            cout << "INVALID INPUT...Remember, I am case-sensitive ;)" << endl;
        }
        else {
            auto it = find(toReturnUser.begin(), toReturnUser.end(), rideMap[input]);
            if (it == toReturnUser.end()) {
                toReturnUser.push_back(rideMap[input]);
            }
        }
    }
    return toReturnUser;

}

string getDate() {
    cout << "Please enter date that you are going to be visiting Disney! (Must be a 2 digit number between 1-31): " << endl;
    string input = getInputInitial();
    while (input.length() != 2) { // this makes sure input is 2 in length..more like forces it lil
        cout << "WARNING: Bruv, input has to be 2 numbers init" << endl;
        input = getInputInitial();
    }

    return input;

}
