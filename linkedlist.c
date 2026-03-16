#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/*
 * Push
 * Allocates a new node and inserts it at the HEAD of the list.
 * headRef - pointer to the head pointer (allows us to modify head)
 * newData - integer value to store in the new node
 *
 * Before: head -> [A] -> [B] -> NULL
 * After:  head -> [newData] -> [A] -> [B] -> NULL
 */
void Push(Node** headRef, int newData) {
    // Allocate memory for the new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: malloc failed in Push\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = newData;   // Store the data
    newNode->next = *headRef;  // Point new node to current head
    *headRef = newNode;        // Update head to new node
}

/*
 * Pop
 * Removes the head node, frees its memory, and returns the data it held.
 * Exits with an error message if called on an empty list.
 *
 * Before: head -> [A] -> [B] -> NULL
 * After:  head -> [B] -> NULL   (returns A's data)
 */
int Pop(Node** headRef) {
    if (*headRef == NULL) {
        fprintf(stderr, "Error: Pop called on empty list\n");
        exit(EXIT_FAILURE);
    }

    Node* temp = *headRef;       // Save current head
    int poppedData = temp->data; // Save its data to return
    *headRef = temp->next;       // Advance head to next node
    free(temp);                  // Free the old head

    return poppedData;
}

/*
 * Count
 * Iterates through the list and counts how many nodes hold searchFor.
 * head - the head pointer (passed by value; we only read, never modify)
 * Returns the count (0 if not found or list is empty).
 */
int Count(Node* head, int searchFor) {
    int count = 0;
    Node* current = head;

    while (current != NULL) {
        if (current->data == searchFor) {
            count++;
        }
        current = current->next;
    }

    return count;
}

/*
 * GetNth
 * Returns the data stored at the given 0-based index.
 * Exits with an error if the index is out of bounds.
 *
 * Example: list = [10, 20, 30], GetNth(head, 1) returns 20
 */
int GetNth(Node** head, int index) {
    if (index < 0) {
        fprintf(stderr, "Error: GetNth called with negative index %d\n", index);
        exit(EXIT_FAILURE);
    }

    Node* current = *head;
    int currentIndex = 0;

    while (current != NULL) {
        if (currentIndex == index) {
            return current->data;
        }
        current = current->next;
        currentIndex++;
    }

    // If we reach here, the index was beyond the list length
    fprintf(stderr, "Error: GetNth index %d is out of bounds\n", index);
    exit(EXIT_FAILURE);
}

/*
 * DeleteList
 * Frees every node in the list and sets *head to NULL.
 * After this call the list is empty with no memory leaks.
 */
void DeleteList(Node** head) {
    Node* current = *head;

    while (current != NULL) {
        Node* next = current->next; // Save next before freeing
        free(current);
        current = next;
    }

    *head = NULL; // Prevent dangling pointer
}

/*
 * InsertNth
 * Inserts a new node containing data at the given 0-based index.
 *   index == 0           → insert at head (same as Push)
 *   index == list length → append at tail
 *   otherwise            → insert between existing nodes
 *
 * Exits with an error if index is negative or beyond the list length.
 */
void InsertNth(Node** head, int index, int data) {
    if (index < 0) {
        fprintf(stderr, "Error: InsertNth called with negative index %d\n", index);
        exit(EXIT_FAILURE);
    }

    // Special case: inserting at the head
    if (index == 0) {
        Push(head, data);
        return;
    }

    // Walk to the node just BEFORE the desired index
    Node* current = *head;
    for (int i = 0; i < index - 1; i++) {
        if (current == NULL) {
            fprintf(stderr, "Error: InsertNth index %d is out of bounds\n", index);
            exit(EXIT_FAILURE);
        }
        current = current->next;
    }

    if (current == NULL) {
        fprintf(stderr, "Error: InsertNth index %d is out of bounds\n", index);
        exit(EXIT_FAILURE);
    }

    // Allocate and wire in the new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: malloc failed in InsertNth\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = current->next; // New node points to what came after
    current->next = newNode;       // Previous node points to new node
}

/*
 * MoveNode
 * Moves the front node of *sourceRef to the front of *destRef.
 * Both lists must be non-NULL (source must have at least one node).
 *
 * Example:
 *   dest   = [1, 2, 3]
 *   source = [5, 6, 7]
 *   After MoveNode(&dest, &source):
 *   dest   = [5, 1, 2, 3]
 *   source = [6, 7]
 */
void MoveNode(Node** destRef, Node** sourceRef) {
    if (*sourceRef == NULL) {
        fprintf(stderr, "Error: MoveNode called with empty source list\n");
        exit(EXIT_FAILURE);
    }

    Node* nodeToMove = *sourceRef;   // Grab the front of source
    *sourceRef = nodeToMove->next;   // Advance source head past it
    nodeToMove->next = *destRef;     // Point it to current dest head
    *destRef = nodeToMove;           // Update dest head
}

/*
 * RecursiveReverse  (helper)
 * The recursive workhorse.
 *   current  - node being processed this call
 *   previous - node that should follow current after reversal
 *   headRef  - used to update the caller's head pointer once we hit the end
 *
 * Base case:  current == NULL  →  we've walked off the end; previous is the
 *             new head.
 * Recursive case: save current->next, then recurse deeper, then flip the
 *             pointer so current->next = previous.
 */
static void reverseHelper(Node* current, Node* previous, Node** headRef) {
    if (current == NULL) {
        // previous is now the new head
        *headRef = previous;
        return;
    }

    Node* nextNode = current->next; // Save before overwriting
    reverseHelper(nextNode, current, headRef); // Recurse deeper first
    current->next = previous;       // On the way back up, flip the pointer
}

/*
 * RecursiveReverse
 * Public entry point.  Reverses the list pointed to by *headRef in place.
 *
 * Before: head -> [1] -> [2] -> [3] -> NULL
 * After:  head -> [3] -> [2] -> [1] -> NULL
 */
void RecursiveReverse(Node** headRef) {
    reverseHelper(*headRef, NULL, headRef);
}