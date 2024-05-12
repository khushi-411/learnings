#include <iostream>
#include <vector>


struct Node {
    char data;
    std::vector<Node*> child;
};


Node* newNode(int data) {
    Node* temp = new Node;
    temp->data = data;
    return temp;
}


int depthTree(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int maxDepth = 0;
    for (std::vector<Node*>::iterator it = root->child.begin(); it != root->child.end(); it++) {
        maxDepth = std::max(maxDepth, depthTree(*it));
    }

    return maxDepth + 1;
}


int main() {
    Node* root = newNode('a');
    (root->child).push_back(newNode('b'));
    (root->child).push_back(newNode('f'));
    (root->child).push_back(newNode('d'));
    (root->child).push_back(newNode('e'));

    std::cout << depthTree(root) << "\n";
    return 0;
}
