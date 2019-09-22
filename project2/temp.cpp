#include <iostream>
#include "phyframes.hh"

using namespace std;

/* Given a node as next_node, insert a new node before the given node */
void insertBefore(struct Node **head_ref, struct Node *next_node, int new_data)
{
    /*1. check if the given next_node is NULL */
    if (next_node == NULL)
    {
        cout << "The given next node cannot be NULL!" << endl;
        return;
    }

    /* 2. allocate new node */
    Node *new_node = (Node *)malloc(sizeof(Node));

    /* 3. put in the data */
    new_node->data = new_data;

    /* 4. Make prev of new node as prev of next_node */
    new_node->prev = next_node->prev;

    /* 5. Make the prev of next_node as new_node */
    next_node->prev = new_node;

    /* 6. Make next_node as next of new_node */
    new_node->next = next_node;

    /* 7. Change next of new_node's previous node */
    if (new_node->prev != NULL)
    {
        new_node->prev->next = new_node;
    }
    /* 8. If the prev of new_node is NULL, it will be 
       the new head node */
    else
    {
        *head_ref = new_node;
    }
}

// This function prints contents of linked list starting from the given node  
void printList(struct Node* node)  
{  
    Node* last;  
    cout << "\nTraversal in forward direction" << endl;  
    while (node != NULL) {  
        cout << node->data << endl;
        last = node;
        node = node->next;
    }
  
    cout << "\nTraversal in reverse direction" << endl;  
    while (last != NULL) {  
        cout << last->data << endl;  
        last = last->prev;  
    }  
}

/* Given a reference (pointer to pointer) to the head of a list 
   and an int, inserts a new node on the front of the list. */
void push(Node **head_ref, int new_data)
{
    /* 1. allocate node */
    Node *new_node = (Node *)malloc(sizeof(Node));

    /* 2. put in the data  */
    new_node->data = new_data;

    /* 3. Make next of new node as head and previous as NULL */
    new_node->next = (*head_ref);
    new_node->prev = NULL;

    /* 4. change prev of head node to new node */
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;

    /* 5. move the head to point to the new node */
    (*head_ref) = new_node;
}


void deleteNodeByValue(struct Node **head_ref, int data_search)
{
    Node* node = *head_ref;
    while(true){
        if(node -> data == data_search){
            if(node -> prev == NULL){
                *head_ref = node -> next;
                node -> next -> prev = NULL;
            }
            else if(node -> next == NULL){
                node -> prev -> next = NULL;
            }
            else
            {
                node -> prev -> next = node -> next;
                node -> next -> prev = node -> prev;
            }
        }
    }
}

void searchAndPush(struct Node **head_ref, int data_search){
    deleteNodeByValue(head_ref, data_search);
    push(head_ref, data_search);
}

