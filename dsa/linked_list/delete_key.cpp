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
    while(head != NULL) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}


void deleteBegin(Node** head) {
    Node* temp = *head;
    *head = (*head)->next;
    delete temp;
}


void deleteEnd(Node** head) {
    if (*head == NULL) {
        return;
    }
    if ((*head)->next == NULL) {
        delete *head;
    }

    Node* prev = NULL;
    Node* last = *head;
    while (last->next != NULL) {
        prev = last;
        last = last->next;
    }
    prev->next = NULL;
    delete last;
}


int main() {
    Node* head = NULL;
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
    push(&head, 4);
    push(&head, 5);
    push(&head, 6);
    printLL(head);
    deleteBegin(&head);
    printLL(head);
    deleteEnd(&head);
    printLL(head);
    return 0;
}
