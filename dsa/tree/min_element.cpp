#include <iostream>
#include <climits>


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


int minEle(Node* root) {
    if (root == NULL) {
        return INT_MAX;
    }
    int min = root->data;
    int leftMin = minEle(root->left);
    int rightMin = minEle(root->right);
    return std::min(root->data, std::min(leftMin, rightMin));
}


int main() {
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    std::cout << minEle(root) << "\n";
    return 0;
}
