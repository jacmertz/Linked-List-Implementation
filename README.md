# Linked List Implementation in C

A hands-on implementation of a singly linked list in C, featuring dynamic memory management and a suite of common list operations including a recursive reverse.

---

## Overview

This project implements a linked list from scratch in C using dynamic memory allocation. It covers core pointer manipulation patterns and includes a menu-driven interface for interactively testing each operation.

---

## Features

- Push and pop nodes at the head of the list
- Count occurrences of a value in the list
- Access elements by index
- Insert a node at any position
- Move the front node between two lists
- Recursively reverse the list in-place
- Full list deletion with memory cleanup

---

## File Structure

```
linked-list/
├── linkedlist.h      # Node structure definition and function prototypes
├── linkedlist.c      # Implementation of all list operations
├── main.c            # Menu-driven interface for testing
└── README.md
```

---

## How to Compile & Run

```bash
gcc -o linkedlist main.c linkedlist.c
./linkedlist
```

Optionally

```bash
cl -o linkedlist main.c linkedlist.c
./linkedlist
```

---

## API Reference

```c
typedef struct node {
    int data;
    struct node* next;
} Node;
```

| Function | Description |
|---|---|
| `Push(Node** headRef, int newData)` | Adds a new node at the head of the list |
| `Pop(Node** headRef)` | Removes the head node and returns its data |
| `Count(Node* head, int searchFor)` | Counts occurrences of a given integer in the list |
| `GetNth(Node** head, int index)` | Returns the data at a specific index |
| `DeleteList(Node** head)` | Deletes all nodes and frees all allocated memory |
| `InsertNth(Node** head, int index, int data)` | Inserts a node at a given index |
| `MoveNode(Node** destRef, Node** sourceRef)` | Moves the front node from one list to another |
| `RecursiveReverse(Node** headRef)` | Recursively reverses the list in-place |

---

## Notes

- **Segfaults:** Trace pointer updates step by step with `printf` or a debugger before and after operations to isolate the issue.
- **Recursive Reverse:** Work through the iterative version first to build intuition, then translate the logic recursively.