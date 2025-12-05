#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int serial;
    char name[50];
    struct Node* next;
};

struct Node* head = NULL;

// Create a new node
struct Node* createNode(int serial, char name[]) {
    struct Node* temp = (struct Node*) malloc(sizeof(struct Node));
    temp->serial = serial;
    strcpy(temp->name, name);
    temp->next = NULL;
    return temp;
}

// Insert at beginning
void insertBeginning(int serial, char name[]) {
    struct Node* temp = createNode(serial, name);
    temp->next = head;
    head = temp;
    printf("Application inserted at beginning.\n");
}

// Insert at end
void insertEnd(int serial, char name[]) {
    struct Node* temp = createNode(serial, name);

    if (head == NULL) {
        head = temp;
        printf("Application inserted at end.\n");
        return;
    }

    struct Node* p = head;
    while (p->next != NULL)
        p = p->next;

    p->next = temp;
    printf("Application inserted at end.\n");
}

// Insert in middle BEFORE given serial number
void insertBefore(int targetSerial, int serial, char name[]) {
    struct Node* temp = createNode(serial, name);

    if (head == NULL) {
        head = temp;
        return;
    }

    if (head->serial == targetSerial) {
        temp->next = head;
        head = temp;
        return;
    }

    struct Node* p = head;
    while (p->next != NULL && p->next->serial != targetSerial)
        p = p->next;

    if (p->next == NULL) {
        printf("Target serial number not found.\n");
        free(temp);
        return;
    }

    temp->next = p->next;
    p->next = temp;
    printf("Inserted before %d.\n", targetSerial);
}

// Delete at beginning
void deleteBeginning() {
    if (head == NULL) {
        printf("No applications to delete.\n");
        return;
    }

    struct Node* temp = head;
    head = head->next;
    printf("Deleted application: %s (%d)\n", temp->name, temp->serial);
    free(temp);
}

// Delete at end
void deleteEnd() {
    if (head == NULL) {
        printf("No applications to delete.\n");
        return;
    }

    if (head->next == NULL) {
        printf("Deleted application: %s (%d)\n", head->name, head->serial);
        free(head);
        head = NULL;
        return;
    }

    struct Node* p = head;
    while (p->next->next != NULL)
        p = p->next;

    struct Node* temp = p->next;
    p->next = NULL;
    printf("Deleted application: %s (%d)\n", temp->name, temp->serial);
    free(temp);
}

// Delete AFTER a given serial number
void deleteAfter(int serial) {
    if (head == NULL) {
        printf("No applications to delete.\n");
        return;
    }

    struct Node* p = head;
    while (p != NULL && p->serial != serial)
        p = p->next;

    if (p == NULL || p->next == NULL) {
        printf("No node found after the given serial.\n");
        return;
    }

    struct Node* temp = p->next;
    p->next = temp->next;

    printf("Deleted application: %s (%d)\n", temp->name, temp->serial);
    free(temp);
}

// Display applications
void display() {
    if (head == NULL) {
        printf("No pending applications.\n");
        return;
    }

    struct Node* p = head;
    printf("\nPending Applications:\n");
    printf("-----------------------\n");

    while (p != NULL) {
        printf("Serial: %d, Name: %s\n", p->serial, p->name);
        p = p->next;
    }
    printf("-----------------------\n");
}

int main() {
    int choice, serial, targetSerial;
    char name[50];

    while (1) {
        printf("\n--- Government Application Management System ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert Before Serial\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at End\n");
        printf("6. Delete After Serial\n");
        printf("7. Display Applications\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Serial Number (1–200): ");
                scanf("%d", &serial);
                printf("Enter Application Name: ");
                scanf("%s", name);
                insertBeginning(serial, name);
                break;

            case 2:
                printf("Enter Serial Number (1–200): ");
                scanf("%d", &serial);
                printf("Enter Application Name: ");
                scanf("%s", name);
                insertEnd(serial, name);
                break;

            case 3:
                printf("Insert BEFORE which Serial? ");
                scanf("%d", &targetSerial);
                printf("Enter New Serial Number: ");
                scanf("%d", &serial);
                printf("Enter Application Name: ");
                scanf("%s", name);
                insertBefore(targetSerial, serial, name);
                break;

            case 4:
                deleteBeginning();
                break;

            case 5:
                deleteEnd();
                break;

            case 6:
                printf("Delete AFTER which Serial? ");
                scanf("%d", &serial);
                deleteAfter(serial);
                break;

            case 7:
                display();
                break;

            case 8:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}