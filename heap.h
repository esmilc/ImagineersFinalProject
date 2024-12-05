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


    void swap(int i, int j); // O(1)
    void heapifyDown(); // O (log n)
    void heapifyUp(); // O(log n)

public:
    void push(string rideName, int time, int waitTime); // O (log n)
    HeapNode pop(); // O(log n)
    HeapNode top(); // O (log n)
    bool isEmpty(); // O (1)
    int sizeDEBUG(); // O (1)
};

#endif // HEAP_H