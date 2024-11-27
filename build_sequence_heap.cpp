//
// Created by Esmil Canet on 11/27/24.
//
#include <unordered_set>
#include <iostream>
using namespace std;
#include "file_parsing.cpp"
#include "heap.cpp"



void printSequence(MinHeap heap, int numRides) {
    int currentTime = 540; //Park opens at 9:00 AM
    int counter = 0;
    unordered_set<string> ridesAdded;
    while (ridesAdded.size() != numRides) {
        HeapNode currNode = heap.pop();
        auto it = ridesAdded.find(currNode.name);
        if (it == ridesAdded.end() && currNode.time >= currentTime) {
            cout << counter << ". " << currNode.name << " at " << minutesToStandard(currNode.time) <<" (Wait time: " << currNode.waitTime << " minutes)." << endl;
            counter ++;
            ridesAdded.insert(currNode.name);
            currentTime = currNode.time + 6 + currNode.waitTime;
        }
    }




}




