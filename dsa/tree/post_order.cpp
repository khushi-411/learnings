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


void postOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    std::cout << root->data << " ";
}


int main() {
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    postOrder(root);
    return 0;
}
