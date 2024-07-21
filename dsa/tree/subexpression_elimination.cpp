#include <iostream>
#include <unordered_map>


struct Node {
    int val;
    Node* left;
    Node* right;
    bool isExpr;
};


Node* createNode(int val, bool isExpr = false) {
    Node* new_node = new Node;
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->isExpr = isExpr;
    return new_node;
}


void printTree(Node* root) {
    if (root == NULL) {
        return;
    }

    printTree(root->left);
    std::cout << root->val << " ";
    printTree(root->right);
}


Node* eliminateCommonSubexpressions(Node* root, std::unordered_map<int, Node*>& expr) {
    if (root == NULL) {
        return NULL;
    }

    if (root->isExpr) {
        int exprHash = std::hash<int>{}(root->val);
        if (expr.find(exprHash) != expr.end()) {
            return expr[exprHash];
        }
    } else {
        root->left = eliminateCommonSubexpressions(root->left, expr);
        root->right = eliminateCommonSubexpressions(root->right, expr);
    }

    return root;
}


int main() {
    Node* root = createNode('+', true);
    root->left = createNode('a');
    root->right = createNode('b');
    root->left->left = createNode('a');
    root->left->right = createNode('b');
    root->left->left->left = createNode('*', true);
    root->left->left->right = createNode('c');

    std::unordered_map<int, Node*> expr;
    Node* new_root = eliminateCommonSubexpressions(root, expr);

    printTree(new_root);
    std::cout << "\n";

    return 0;
}
