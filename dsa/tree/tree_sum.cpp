#include <iostream>


struct Node {
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


int sumTree(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return root->data + sumTree(root->left) + sumTree(root->right);
}


int main() {
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    std::cout << sumTree(root) << "\n";
    return 0;
}
