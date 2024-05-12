#include <iostream>


struct Node{
    int data;
    Node* left;
    Node* right;
};


Node* newNode(int data) {
    Node* temp = new Node;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}


int levelTree(Node* root, int key) {
    if (root == NULL) {
        return 0;
    }

    if (root->data == key) {
        return 1;
    }
}


int main() {
    Node* root = newNode(6);
    root->left = newNode(5);
    root->right = newNode(4);
    root->left->left = newNode(3);
    root->left->right = newNode(2);
    root->right->right = newNode(8);
    root->right->left = newNode(9);

    int key = 4;
    std::cout << levelTree(root, key) << "\n";
    return 0;
}
