// Author: Miracleyoo
// E-mail: mirakuruyoo@gmail.com
// Date: 2019.09.22
// Mainly manage the physical frames

#include <iostream>
#include <cstdlib>
#include "phyframes.hh"

using namespace std;

Node *head_ref = NULL; // The head of the double linked list
Node *tail_ref = NULL; // The tail of the double linked list
int virtual_to_physical_list[32] = {0}; // A list which map virtual address to physical address
int physical_to_virtual_list[7] = {0};  // A list which map physical address to virtual address
void searchAndPush(int data_search);
void push(int new_data);
void cutTailAddHead(int data_replace);

/* Given a reference (pointer to pointer) to the head of a list 
   and an int, inserts a new node on the front of the list. */
void push(int new_data)
{
    /* 1. allocate node */
    Node *new_node = (Node *)malloc(sizeof(Node));

    /* 2. put in the data  */
    new_node->data = new_data;

    /* 3. Make next of new node as head and previous as NULL */
    new_node->next = head_ref;
    new_node->prev = NULL;

    /* 4. change prev of head node to new node */
    if (head_ref != NULL)
        head_ref->prev = new_node;
    else
        tail_ref = new_node;
    /* 5. move the head to point to the new node */
    head_ref = new_node;
}

/* Search the double linked list for a certain node by value
   and delete this node. */
void deleteNodeByValue(int data_search)
{
    Node *node = head_ref;
    if (node == NULL)
    {
        cout << "The list is empty!" << endl;
        return;
    }
    while (true)
    {
        if (node->data == data_search)
        {
            if (node->prev == NULL)
            {
                head_ref = node->next;
                node->next->prev = NULL;
            }
            else if (node->next == NULL)
            {
                node->prev->next = NULL;
                tail_ref = node->prev;
            }
            else
            {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
        }
        node = node->next;
        if (node == NULL)
        {
            break;
        }
    }
}

/* Search the double linked list for a certain node by value
   and move it to the head of the list. */
void searchAndPush(int data_search)
{
    if (!(data_search == head_ref->data))
    {
        deleteNodeByValue(data_search);
        push(data_search);
    }
}

/* Delete the last node in the double linked list, and then
   Add a new node whose data equals data_replace. */
void cutTailAddHead(int data_replace)
{
    tail_ref->prev->next = NULL;
    tail_ref = tail_ref->prev;
    push(data_replace);
}