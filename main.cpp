#include <iostream>
using namespace std;
#include "file_parsing.cpp"

int main() {

    cout << "Hello Imagineers!" << endl;
    cout << "Testing Functionality" << endl;

    cout << rawTimetoFormatted("09:03:15") << endl;

    parseFile("meet_mickey.csv", "1");

    return 0;
}