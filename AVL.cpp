#include <iostream>
#include <stack>
#include <queue>
#include <ctime>

using namespace std;

struct Node {
    int key;
    Node* left_child;
    Node* right_child;
    Node(int key) {
        this->key = key;
        this->left_child = NULL;
        this->right_child = NULL;
    }
};

int degree_node(Node *node) {
    return (node->left_child != NULL) + (node->right_child != NULL);
}

int heightOfNode(Node* root);
void rebalance(Node* &root);

void add_node(Node* &root, int key) {
    if (!root) 
        root = new Node(key);
    else if (root->key > key) {
        add_node(root->left_child, key);
    }
    else if (root->key < key) {
        add_node(root->right_child, key);
    }
    else {
        cout << key << " is already in tree" << endl;
        return;
    }
    rebalance(root);
}

void LNR(Node* root) {
    if (!root) 
        return;
    else {
        LNR(root->left_child);
        cout << root->key << " ";
        LNR(root->right_child);
    }
}

void NLR(Node* root) {
    if (root)
    {
        cout << root->key << " ";
        NLR(root->left_child);
        NLR(root->right_child);
    }
}

void levelOrder(Node* root) {
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {

        Node* node = q.front();
        q.pop();

        cout << node->key << " ";
        if (node->left_child)
            q.push(node->left_child);
        if (node->right_child)
            q.push(node->right_child);

    }
}

void right_rotate(Node* &root) {
    Node* left = root->left_child;
    root->left_child = left->right_child;
    left->right_child = root;
    root = left;
}

void left_rotate(Node* &root) {
    Node* right = root->right_child;
    root->right_child = right->left_child;
    right->left_child = root;
    root = right;
}

int getBalanceFactor(Node* &root) {
    return heightOfNode(root->left_child) - heightOfNode(root->right_child);
}

void rebalance(Node* &root) {

    int delta = getBalanceFactor(root);
    
    if (delta > 1) {
        int child_delta = getBalanceFactor(root->left_child);
        
        if (child_delta < 0) 
            left_rotate(root->left_child);
        
        right_rotate(root);
    }
    else if (delta < -1) {
        int child_delta = getBalanceFactor(root->right_child);
        
        if (child_delta > 0) 
            right_rotate(root->right_child);
        
        left_rotate(root);
    }
}

int heightOfNode(Node* root) {
    if (!root)
        return 0;
    return 1 + max(heightOfNode(root->left_child), heightOfNode(root->right_child));
}

Node* findNode(Node* root, int key) {
    if (!root)
        return NULL;
    else {
        if (root->key == key)
            return root;
        else if (root->key > key) {
            return findNode(root->left_child, key);
        }
        else if (root->key < key) {
            return findNode(root->right_child, key);
        }
    }
    return NULL;
}

Node* createTree(int arr[], int n) {
    Node* root = new Node(arr[0]);

    for (int i = 1; i < n; i++) {
        add_node(root, arr[i]);
    }

    return root;
}

Node* replacement(Node* root) {
    Node* cur = root;

    while (cur && cur->left_child)
        cur = cur->left_child;

    return cur;
}

void removeNode(Node* &root, int key) {
    if (root == NULL)
        return;
    
    if (key < root->key)
        removeNode(root->left_child, key);
    else if (key > root->key)
        removeNode(root->right_child, key);
    else {

        if (root->left_child == NULL) {
            Node* saver = root->right_child;
            delete root;
            root = saver;
        }
        else if (root->right_child == NULL) {
            Node* saver = root->left_child;
            delete root;
            root = saver;
        }
        else {
            Node* replace = replacement(root->right_child);
            root->key = replace->key;
            removeNode(root->right_child, replace->key);
        }
    }
    if (root)
        rebalance(root);
    return;
}

void RemoveNode(Node* &root, int key) {
    Node* find = findNode(root, key);
    if (find) {
        removeNode(root, key);
        rebalance(root);
    }
    else {
        cout << "Cant find node " << key << endl;
    }
}

bool isBST(Node* root) {
    static Node* prev = NULL;

    if (root) {

        if (!isBST(root->left_child)) 
            return false;

        if (prev != NULL && prev->key > root->key)
            return false;
        
        prev = root;

        if (!isBST(root->right_child))
            return false;
    }
    return true;
}

int main() {
    int a[35];
    srand(time(0));
    for (int i = 0; i < 35; i++) {
        a[i] = rand() % 100;
        cout << a[i] << " ";
    }
    cout << endl;
    a[rand()%35] = 23;
    a[rand()%35] = 35;
    Node* root = createTree(a, 35);
    cout << "LNR tree: ";
    LNR(root);
    cout << endl;
    cout << "NLR tree: ";
    NLR(root);
    cout << endl;
    cout << "Level-order tree: ";
    levelOrder(root);
    cout << endl;
    //remove test
    removeNode(root, 23);
    cout << "LNR after removing 23: ";
    LNR(root);
    cout << endl;
    cout << "NLR after removing 23: ";
    NLR(root);
    cout << endl;
    cout << "Level-order tree after removing 23: ";
    levelOrder(root);
    cout << endl;
    //remove test
    removeNode(root, 35);
    cout << "LNR after removing 35: ";
    LNR(root);
    cout << endl;
    cout << "NLR after removing 35: ";
    NLR(root);
    cout << endl;
    cout << "Level-order tree after removing 35: ";
    levelOrder(root);
    cout << endl;
    // cout << "\nGiven tree is" << (isBST(root) ? " BST" : " not BST") << endl;
    return 0;
}