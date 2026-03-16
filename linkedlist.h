#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Node structure definition
typedef struct node {
    int data;
    struct node* next;
} Node;

// Function prototypes

// Adds a new node at the head of the list
void Push(Node** headRef, int newData);

// Removes the head node and returns its data
// Exits with error if list is empty
int Pop(Node** headRef);

// Counts occurrences of a given integer in the list
int Count(Node* head, int searchFor);

// Returns the data at a specific 0-based index
// Exits with error if index is out of bounds
int GetNth(Node** head, int index);

// Deletes all nodes and frees memory, sets head to NULL
void DeleteList(Node** head);

// Inserts a node at a given 0-based index
// Index 0 inserts at head; index == length appends at tail
void InsertNth(Node** head, int index, int data);

// Moves the front node from source list to the front of destination list
void MoveNode(Node** destRef, Node** sourceRef);

// Recursively reverses the linked list in place
void RecursiveReverse(Node** headRef);

#endif // LINKEDLIST_H