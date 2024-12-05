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

// comparator so RideNodes can be cleanly sorted by time of day
bool RideNode::operator<(const RideNode& other) const {
    return time < other.time;
}

void RideNode::print() {
    cout << name << " at " << time << " minutes: " << waitTime << endl;
}

Node::Node() = default;

void Node::insert(RideNode ride) {

    // insert datapoint into B+ tree node
    data.push_back(ride);

    // sort the nodes based on the time
    sort(data.begin(), data.end());

    // stores the maximum time of day for use in other functions
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

    // edge case for if there are no nodes in the tree
    if(src == nullptr) {
        src = new Node();
        src->data.push_back(ride);
        src->leaf = true;
        numNodes++;
        numKeys++;
        return;
    }

    // if a leaf has been reached,
    // then this is the insertion spot for the RideNode
    if(root->leaf) {
        root->insert(ride);
        numKeys++;
    }

    // otherwise, go deeper
    else {

        // determines which branch to follow
        for(int x = 0; x < n; x++) {

            // if the new datapoint is less than the internal node's datapoint,
            // follow the branch extending from that datapoint
            if(root->data.size() < x + 1 || ride < root->data[x]) {

                // if the selected branch does not currently exist, make a new child node
                if(root->children.size() - 1 < x) {
                    root->children.push_back(new Node);
                    root->children[x]->leaf = true;
                    numNodes++;

                    // link new leaf to node left of it
                    root->children[root->children.size() - 2]->next = root->children[root->children.size() - 1];
                    root->children[root->children.size() - 1]->prev = root->children[root->children.size() - 2];
                }

                // go deeper into child node
                insert(root->children[x], ride, x, root);
                break;
            }
        }
    }

    // split node if it is a leaf and has more than l = 5 keys
    if(root->leaf && root->data.size() > l) {
        splitNode(root, parent, childIdx);
    }

    // split node if it is an internal node and has more than n = 4 children or n - 1 leaves
    else if(!root->leaf && (root->data.size() > n - 1 || root->children.size() > n)) {
        splitNode(root, parent, childIdx);
    }
}

void BPlusTree::splitNode(Node* node, Node* parent, int childIdx) {

    // gets the middle index of the node's data vector
    int mid = node->data.size() / 2;

    // middle value to be sent up to parent
    RideNode midVal = node->data[mid];

    // new nodes that the current node will be split into
    Node* left = new Node();
    Node* right = new Node();

    // if the node being split is a leaf,
    if(node->leaf) {

        // the new nodes will also be leaves
        left->leaf = true;
        right->leaf = true;

        // links new leaf nodes to leaves to the left and right of them
        left->prev = node->prev;
        if(left->prev != nullptr)
            left->prev->next = left;
        left->next = right;

        right->next = node->next;
        if(right->next != nullptr)
            right->next->prev = right;
        right->prev = left;
    }

    // starting indexes for data splitting
    int x = 0;
    int y;

    // leave a copy of the middle value in the new nodes if the node being split is a leaf
    if(node->leaf) {
        y = mid;
    }

    // dont leave a copy if the node being split is an internal node
    else
        y = mid + 1;

    // copy each half of the data into the new nodes
    while(x < mid && y < node->data.size()) {
        left->insert(node->data[x]);
        right->insert(node->data[y]);
        x++;
        y++;
    }

    // special case for internal nodes
    if(x < mid) {
        left->insert(node->data[x]);
    }

    // edge case for if the node being split is the root of the entire tree
    bool flag = true;
    if(parent == nullptr) {
        src = new Node();
        parent = src;
        numNodes++;
        flag = false;
    }

    // send the middle value of the split node up to the parent
    parent->insert(midVal);

    // if the node is an internal node
    if(!node->leaf) {

        // split its children among the two new nodes based on the middle value
        for(Node* n : node->children) {
            if(n->max < midVal) {
                left->children.push_back(n);
            }
            else {
                right->children.push_back(n);
            }
        }
    }

    // if the split node was not the root of the entire tree
    // erase the split node from the parent's children
    if(flag)
        parent->children.erase(parent->children.begin() + childIdx);

    // insert the new nodes into the parent's children using the index of the split node
    parent->children.insert(parent->children.begin() + childIdx, right);
    parent->children.insert(parent->children.begin() + childIdx, left);

    // delete the split node
    delete node;

    // a node was split into two, so increment numNodes
    numNodes++;
}

RideNode BPlusTree::search(Node *root, int target) {

    // if a leaf node has been reached,
    // this is where the target value should be
    if(root->leaf) {

        int diff;

        // index of the closest time to the target
        int closestIdx = -1;

        // iterates through every data point in the target node
        for(int x = 0; x < root->data.size(); x++) {

            // calcs the difference between the target time and the datapoint's time
            diff = abs(target - root->data[x].time);

            // if they match, return that datapoint
            if(diff == 0) {
                return root->data[x];
            }

            // otherwise, mark that datapoint as the closest to the target time
            if(closestIdx == -1 || diff < abs(target - root->data[closestIdx].time)) {
                closestIdx = x;
            }
        }

        // if program has made it to this point,
        // an exact time of day match was not found in the target node

        // data from node to the right of the target node
        // if it exists
        int closestIdxNext = -1;
        vector<RideNode> next;
        if(root->next != nullptr)
            next = root->next->data;

        // data from node to the left of the target node,
        // if it exists
        int closestIdxPrev = -1;
        vector<RideNode> prev;
        if(root->prev != nullptr)
            prev = root->prev->data;

        // finds closest datapoint to target time in right node's data
        for(int x = 0; x < next.size(); x++) {

            diff = abs(target - next[x].time);
            if(diff == 0) {
                return next[x];
            }
            if(closestIdxNext == -1 || diff < abs(target - next[closestIdxNext].time)) {
                closestIdxNext = x;
            }
        }

        // finds closest datapoint to target time in left node's data
        for(int x = 0; x < prev.size(); x++) {

            diff = abs(target - prev[x].time);
            if(diff == 0) {
                return prev[x];
            }
            if(closestIdxPrev == -1 || diff < abs(target - prev[closestIdxPrev].time)) {
                closestIdxPrev = x;
            }
        }

        // difference in target time and closest datapoint from target node
        int diffBase = abs(target - root->data[closestIdx].time);

        // difference in target time and closest datapoint from node to right of target
        int diffNext = diffBase + 1;
        if(closestIdxNext != -1)
            diffNext = abs(target - next[closestIdxNext].time);

        // difference in target time and closest datapoint from node to left of target
        int diffPrev = diffBase + 1;
        if(closestIdxPrev != -1)
            abs(target - prev[closestIdxPrev].time);

        // target node diff is smallest
        if(diffBase < diffNext && diffBase < diffPrev) {
            return root->data[closestIdx];
        }

        // right node diff is smallest
        if(diffNext < diffBase && diffNext < diffPrev) {
            return next[closestIdxNext];
        }

        // left node diff is smallest
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
        for(RideNode x : root->data) {
            x.print();
        }
        return;
    }

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


