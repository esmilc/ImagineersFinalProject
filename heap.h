#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// Struct for representing a heap node
struct HeapNode {
    string name;
    int time;
    int waitTime;

    HeapNode(string name, int time, int waitTime);

    // Comparison operators for the heap
    bool operator>(const HeapNode& other) const;
    bool operator<(const HeapNode& other) const;
};


class MinHeap {
private:
    vector<HeapNode> heap;


    void swap(int i, int j);
    void heapifyDown();
    void heapifyUp();

public:
    void push(string rideName, int time, int waitTime);
    HeapNode pop();
    HeapNode top();
    bool isEmpty();
    int sizeDEBUG();
};

#endif // HEAP_H