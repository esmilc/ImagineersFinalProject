//
// Created by kyles on 12/2/2024.
//

#include "BPlusTree.h"

RideNode::RideNode() {
    name = "";
    time = 0;
    waitTime = 0;
}

RideNode::RideNode(string n, int t, int wt) {
    name = n;
    time = t;
    waitTime = wt;
}

bool RideNode::operator<(const RideNode& other) const {
    return time < other.time;
}

void RideNode::print() {
    cout << name << " at " << time << " minutes: " << waitTime << endl;
}

Node::Node() = default;

void Node::insert(RideNode ride) {
    data.push_back(ride);

    int minTimeIndex = 0;

    // sort the nodes based on the time

    sort(data.begin(), data.end());
    max = data[data.size() -1];
}

BPlusTree::BPlusTree(string name) {
    this->name = name;
    numNodes = 0;
    numKeys = 0;
    src = nullptr;
}

BPlusTree::~BPlusTree() {
    if(src != nullptr)
        destructorHelp(src);
}

void BPlusTree::destructorHelp(Node* root) {
    if(root->leaf) {
        numNodes--;
        delete root;
        return;
    }

    for(Node* n : root->children) {
        destructorHelp(n);
    }
    numNodes--;
    delete root;
}

void BPlusTree::insert(Node* root, RideNode& ride, int childIdx, Node* parent) {
    if(src == nullptr) {
        src = new Node();
        src->data.push_back(ride);
        src->leaf = true;
        numNodes++;
        numKeys++;
        return;
    }

    if(root->leaf) {
        root->insert(ride);
        numKeys++;
    }
    else {

        for(int x = 0; x < n; x++) {
            if(root->data.size() < x + 1 || ride < root->data[x]) {
                if(root->children.size() - 1 < x) {
                    root->children.push_back(new Node);
                    root->children[x]->leaf = true;
                    numNodes++;

                    root->children[root->children.size() - 2]->next = root->children[root->children.size() - 1];
                    root->children[root->children.size() - 1]->prev = root->children[root->children.size() - 2];
                }
                insert(root->children[x], ride, x, root);
                break;
            }
        }
    }

    if(root->leaf && root->data.size() > l) {
        splitNode(root, parent, childIdx);
    }
    else if(!root->leaf && (root->data.size() > n - 1 || root->children.size() > n)) {
        splitNode(root, parent, childIdx);
    }
}

void BPlusTree::splitNode(Node* node, Node* parent, int childIdx) {

    int mid = node->data.size() / 2;
    RideNode midVal = node->data[mid];

    Node* left = new Node();
    Node* right = new Node();
    if(node->leaf) {
        left->leaf = true;
        right->leaf = true;

        left->prev = node->prev;
        if(left->prev != nullptr)
            left->prev->next = left;
        left->next = right;

        right->next = node->next;
        if(right->next != nullptr)
            right->next->prev = right;
        right->prev = left;
    }

    int x = 0;
    int y;
    if(node->leaf) {
        y = mid;
    }
    else
        y = mid + 1;

    while(x < mid && y < node->data.size()) {
        left->insert(node->data[x]);
        right->insert(node->data[y]);
        x++;
        y++;
    }
    if(x < mid) {
        left->insert(node->data[x]);
    }

    bool flag = true;
    if(parent == nullptr) {
        src = new Node();
        parent = src;
        numNodes++;
        flag = false;
    }
    parent->insert(midVal);

    if(!node->leaf) {
        for(Node* n : node->children) {
            if(n->max < midVal) {
                left->children.push_back(n);
            }
            else {
                right->children.push_back(n);
            }
        }
    }

    if(flag)
        parent->children.erase(parent->children.begin() + childIdx);
    parent->children.insert(parent->children.begin() + childIdx, right);
    parent->children.insert(parent->children.begin() + childIdx, left);
    delete node;
    numNodes++;
}

RideNode BPlusTree::search(Node *root, int target) {
    if(root->leaf) {

        int diff;
        int closestIdx = -1;

        for(int x = 0; x < root->data.size(); x++) {
            diff = abs(target - root->data[x].time);
            if(diff == 0) {
                return root->data[x];
            }
            if(closestIdx == -1 || diff < abs(target - root->data[closestIdx].time)) {
                closestIdx = x;
            }
        }

        int closestIdxNext = -1;
        vector<RideNode> next;
        if(root->next != nullptr)
            next = root->next->data;

        int closestIdxPrev = -1;
        vector<RideNode> prev;
        if(root->prev != nullptr)
            prev = root->prev->data;

        for(int x = 0; x < next.size(); x++) {

            diff = abs(target - next[x].time);
            if(diff == 0) {
                return next[x];
            }
            if(closestIdxNext == -1 || diff < abs(target - next[closestIdxNext].time)) {
                closestIdxNext = x;
            }
        }

        for(int x = 0; x < prev.size(); x++) {

            diff = abs(target - prev[x].time);
            if(diff == 0) {
                return prev[x];
            }
            if(closestIdxPrev == -1 || diff < abs(target - prev[closestIdxPrev].time)) {
                closestIdxPrev = x;
            }
        }

        int diffBase = abs(target - root->data[closestIdx].time);

        int diffNext = diffBase + 1;
        if(closestIdxNext != -1)
            diffNext = abs(target - next[closestIdxNext].time);

        int diffPrev = diffBase + 1;
        if(closestIdxPrev != -1)
            abs(target - prev[closestIdxPrev].time);

        if(diffBase < diffNext && diffBase < diffPrev) {
            return root->data[closestIdx];
        }
        if(diffNext < diffBase && diffNext < diffPrev) {
            return next[closestIdxNext];
        }
        return prev[closestIdxPrev];
    }

    for(int x = 0; x < root->data.size(); x++) {
        if(target < root->data[x].time) {
            return search(root->children[x], target);
        }
    }
    return search(root->children[root->data.size()], target);
}


void BPlusTree::printInorder(Node* root, int level) {
    if(root->leaf) {
        // cout << "Level " << level << ": " << endl;
        for(RideNode x : root->data) {
            x.print();
        }
        // cout << endl << endl;;
        return;
    }

    // cout << "Level " << level << ": " << endl;
    // for(int x : root->data) {
    //     cout << x << ", ";
    // }
    // cout << endl << endl;

    for(Node* n : root->children) {
        printInorder(n, level + 1);
    }

    if(root == src) {
        cout << endl;
    }
}

void BPlusTree::printList(Node *root) {
    if(root->leaf) {
        Node* traverse = root;
        while(traverse != nullptr) {
            for(RideNode x : traverse->data) {
                x.print();
            }
            traverse = traverse->next;
        }
    }
    else {
        printList(root->children[0]);
    }
    if(root == src) {
        cout << endl;
    }
}

void BPlusTree::printRevList(Node *root) {
    if(root->leaf) {
        Node* traverse = root;
        while(traverse != nullptr) {
            for(int x = traverse->data.size() - 1; x >= 0; x--) {
                traverse->data[x].print();
            }
            traverse = traverse->prev;
        }
    }
    else {
        printRevList(root->children[root->children.size() - 1]);
    }
    if(root == src) {
        cout << endl;
    }
}


void BPlusTree::inorderTest(Node *root, vector<RideNode> &result, int& nodeCount) {
    if(root->leaf) {
        cout << "leaf node with " << root->data.size() << " keys" << endl;
        for(RideNode x : root->data) {
            result.push_back(x);
        }
        return;
    }

    cout << "internal node with " << root->data.size() << " keys and " << root->children.size() << " children" << endl;
    for(Node* n : root->children) {
        nodeCount++;
        inorderTest(n, result, nodeCount);
    }
}


