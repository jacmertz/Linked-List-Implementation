#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void printList(Node* head) {
    if (head == NULL) {
        printf("Empty list\n");
        return;
    }
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

int listLength(Node* head) {
    int len = 0;
    while (head) { len++; head = head->next; }
    return len;
}

void printMenu(void) {
    printf("\nLinked List Operations\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Count\n");
    printf("4. GetNth\n");
    printf("5. InsertNth\n");
    printf("6. MoveNode\n");
    printf("7. RecursiveReverse\n");
    printf("8. DeleteList\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

int main(void) {
    Node* list = NULL;
    int choice, value, index;

    while (1) {
        printf("\nCurrent list: ");
        printList(list);
        printMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {

        case 1:
            printf("Enter value to push: ");
            scanf("%d", &value);
            Push(&list, value);
            printf("Pushed %d\n", value);
            break;

        case 2:
            if (list == NULL) {
                printf("List is empty.\n");
            } else {
                value = Pop(&list);
                printf("Popped: %d\n", value);
            }
            break;

        case 3:
            printf("Enter value to count: ");
            scanf("%d", &value);
            printf("%d appears %d time(s)\n", value, Count(list, value));
            break;

        case 4:
            printf("Enter index: ");
            scanf("%d", &index);
            if (index < 0 || index >= listLength(list)) {
                printf("Index out of bounds\n");
            } else {
                value = GetNth(&list, index);
                printf("Value at index %d: %d\n", index, value);
            }
            break;

        case 5:
            printf("Enter index: ");
            scanf("%d", &index);
            printf("Enter value: ");
            scanf("%d", &value);
            if (index < 0 || index > listLength(list)) {
                printf("Index out of bounds\n");
            } else {
                InsertNth(&list, index, value);
                printf("Inserted %d at index %d\n", value, index);
            }
            break;

        case 6: {
            Node* source = NULL;
            int n;
            printf("How many nodes for source list? ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++) {
                printf("Enter value: ");
                scanf("%d", &value);
                Push(&source, value);
            }
            printf("Source: ");
            printList(source);
            printf("Destination before: ");
            printList(list);

            MoveNode(&list, &source);

            printf("Destination after: ");
            printList(list);
            printf("Source after: ");
            printList(source);

            DeleteList(&source);
            break;
        }

        case 7:
            if (list == NULL) {
                printf("List is empty.\n");
            } else {
                RecursiveReverse(&list);
                printf("List reversed.\n");
            }
            break;

        case 8:
            DeleteList(&list);
            printf("List deleted.\n");
            break;

        case 0:
            DeleteList(&list);
            printf("Goodbye.\n");
            return EXIT_SUCCESS;

        default:
            printf("Invalid option.\n");
            break;
        }
    }
}