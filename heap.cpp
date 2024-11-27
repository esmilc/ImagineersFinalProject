#include<iostream>
#include <map>
using namespace std;


struct HeapNode {
    string name;
    int time; //in minutes (0 = midnight)
    int waitTime;

    HeapNode(string name, int time, int waitTime){
        this->name = name;
        this->time = time;
        this->waitTime = waitTime;
    }

    bool operator>(const HeapNode& other)const{
        if (time == other.time){
            return waitTime > other.waitTime;
        }
        return time > other.time;
    }

     bool operator<(const HeapNode& other)const{
        if (time == other.time){
            return waitTime < other.waitTime;
        }
        return time < other.time;
    }

};

class MinHeap {
    vector<HeapNode> heap;

    //When adding new element should be in bottom most left most available part so pushback into heap vector? and heapify up
    //When popping, you replace the head with bottom right most vector[len-1] and you heapify down

    void swap(int i, int j){ //Helper function to swap two elements in a heap
        HeapNode temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyDown() {
        //must be run after all extraction and replacement!!
        int i = 0; //always start at root
        while (true) {
            int left = 2 * i + 1;   // Left child 
            int right = 2 * i + 2;  // Right child 
            int smallest = i;       // Assuming current is smallest

            // Check if the left child exists and is smaller than the current node
            if (left < heap.size() && heap[left] < heap[smallest]) {
                smallest = left;
            }
            // Check if the right child exists and is smaller than the current smallest node
            if (right < heap.size() && heap[right] < heap[smallest]) {
                smallest = right;
            }

            // If the smallest node is not the current node, swap and continue
            if (smallest != i) {
                swap(i, smallest);
                i = smallest; // Move down
            } else {
                break; ///We're good
            }
        }
    }

    void heapifyUp(){
        //this is to be run after every insertion!!!
        int i = heap.size() - 1; //Last element
        int parent = (i - 1) / 2;
        while (i > 0 && heap[i] < heap[parent]) {
            swap(i, parent);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

public:
    void push(string rideName, int time, int waitTime){
        HeapNode node(rideName, time, waitTime);
        heap.push_back(node);
        heapifyUp();
    }

    HeapNode pop(){
        HeapNode toReturn = heap[0];
        heap[0] = heap[heap.size()-1];
        heap.pop_back(); //Delete that last node we just made the head
        heapifyDown();
        return toReturn;
    }

    bool isEmpty(){
        return heap.size() == 0;
    }

    HeapNode top(){
        if (isEmpty()){
            throw runtime_error("OH NAUR...its empty bruv");
        }
        return heap[0];
    }




};





/*
THE GRAVEYARD: :(

//Assuming park opens at 9 am (540min) and close at 11 PM (1380 min)
// class Ride{
//     string name;
//     //array int of size 840
//     int wait_times[840];

//     public:
//         int getWaitTime(int formattedTime){
//             return wait_times[formattedTime];
//         }


// };)



*/