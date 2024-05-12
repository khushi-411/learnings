#include <iostream>


struct Node {
    int data;
    Node* next;
};


void push(Node** head_ref, int data) {
    Node* new_node = new Node;
    new_node->data = data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}


void printLL(Node* head) {
    while (head != NULL) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}


void reverse(Node** head) {
    Node* current = *head;
    Node* prev = NULL, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}


int main() {
    Node* head = NULL;
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
    push(&head, 4);
    printLL(head);
    reverse(&head);
    printLL(head);
    return 0;
}
