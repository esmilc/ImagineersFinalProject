#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#ifndef BPLUSTREE_H
#define BPLUSTREE_H

struct RideNode {

    string name;
    int time;
    int waitTime;

    RideNode();
    RideNode(string n, int t, int wt);

    bool operator<(const RideNode& other) const;
    void print();
};

struct Node {

    RideNode max;
    bool leaf = false;
    vector<RideNode> data;
    vector<Node*> children;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node();
    void insert(RideNode ride);
};


// n = 4
// l = 5
// internal nodes can have at most 3 keys
struct BPlusTree {

    // holds ride name
    string name;

    // tree invariants
    const static int n = 4;
    const static int l = 5;

    // counters for nodes and keys
    int numNodes;
    int numKeys;

    // root of the entire tree
    Node* src;

    BPlusTree(string name);
    ~BPlusTree();

    // recursive function to help destructor
    void destructorHelp(Node* root);

    void insert(Node* root, RideNode& ride, int childIdx = 0, Node* parent = nullptr);

    // splitter function for when a node breaks invariants
    void splitNode(Node* node, Node* parent, int childIdx);

    // pass a time of day in minutes after midnight,
    // returns RideNode with time closest to passed time
    RideNode search(Node* root, int targetTime);

    void printInorder(Node* root, int level = 0);
    void printList(Node* root);
    void printRevList(Node* root);


    void inorderTest(Node* root, vector<RideNode>& result, int& nodeCount);
};



#endif //BPLUSTREE_H
