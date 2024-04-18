#include <iostream>


struct Node {
    int data;
    Node* next;
};


void push(Node** head_ref, int new_data) {
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}


void insertAfter(Node* prev_node, int new_data) {
    if (prev_node == NULL) {
        return;
    }
    Node* new_node = new Node();
    new_node->data = new_data;
    new_data->next = prev_node->next;
    prev_node->next = new_node;
}


void append(Node** head_ref, int new_data) {
    Node* new_node = new Node();
    Node* last = *head_ref;
    new_node->data = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    while(last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
    return;
}


int main() {
    Node* head = NULL;
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
    append(&head, 4);
    insertAfter(head->next, 5);

    Node* current = head;
    while (current != NULL) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";

    return 0;
}
