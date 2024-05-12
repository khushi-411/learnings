#include <iostream>


struct Node {
    int data;
    Node* next;
};


void push(Node** head, int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}


void printLL(Node* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}


Node* split(Node* head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    Node* slow = head;
    Node* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* mid = slow->next;
    slow->next = nullptr;
    return mid;
}


Node* merge(Node* left, Node* right) {
    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;

    Node* result = nullptr;
    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(right->next, left);
    }
    return result;
}


Node* mergeSort(Node* head) {
    if (head == nullptr || head->next == nullptr)
        return head;
    Node* mid = split(head);
    Node* left = mergeSort(head);
    Node* right = mergeSort(mid);

    return merge(left, right);
}


int main() {
    Node* head = nullptr;
    push(&head, 5);
    push(&head, 2);
    push(&head, 4);
    push(&head, 3);
    push(&head, 1);

    std::cout << "Original List: ";
    printLL(head);

    head = mergeSort(head);

    std::cout << "Sorted List: ";
    printLL(head);

    return 0;
}
