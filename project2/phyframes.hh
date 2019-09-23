// Author: Miracleyoo
// E-mail: mirakuruyoo@gmail.com
// Date: 2019.09.22

typedef struct Node
{
    int data;
    struct Node *next; // Pointer to next node in DLL
    struct Node *prev; // Pointer to previous node in DLL
} Node;

extern Node *head_ref;  // The head of the double linked list
extern Node *tail_ref;  // The tail of the double linked list
extern int virtual_to_physical_list[32]; // A list which map virtual address to physical address
extern int physical_to_virtual_list[7];  // A list which map physical address to virtual address
void searchAndPush(int data_search);
void push(int new_data);
void cutTailAddHead(int data_replace);