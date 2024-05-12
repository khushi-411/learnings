#include <iostream>
#include <unordered_set>


struct Node {
    int value;
    Node* left;
    Node* right;
    bool isused;
};


Node* createNode(int value) {
    Node* new_node = new Node;
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->isused = false;
    return new_node;
}


void printTree(Node* root) {
    if (root == NULL) {
        return;
    }

    if (root->isused != NULL) {
        std::cout << root->value << " ";
    }

    printTree(root->left);
    printTree(root->right);
}


void eliminateDeadCode(Node* root, std::unordered_set<int>& val) {
    if (root == NULL) {
        return;
    }

    if (val.find(root->value) != val.end()) {
        root->isused = true;
        eliminateDeadCode(root->left, val);
        eliminateDeadCode(root->right, val);
    } else {
        delete root->left;
        delete root->right;
        root->left = NULL;
        root->right = NULL;
    }
}


int main() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    std::unordered_set<int> val = {1, 2, 5};
    eliminateDeadCode(root, val);

    printTree(root);
    std::cout << "\n";
    return 0;
}
