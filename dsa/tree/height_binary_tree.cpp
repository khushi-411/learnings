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


int heightTree(Node* root) {
    if (root == NULL) {
        return -1;
    }

    int leftHeight = heightTree(root->left);
    int rightHeight = heightTree(root->right);
    return std::max(leftHeight, rightHeight) + 1;
}


int main() {
    Node* root = newNode(5);
    root->left = newNode(4);
    root->right = newNode(3);
    root->left->left = newNode(2);
    root->left->right = newNode(1);
    root->right->left = newNode(2);
    root->right->right = newNode(1);

    std::cout << heightTree(root) << "\n";
    return 0;
}
