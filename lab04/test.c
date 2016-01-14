#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "list.h"
struct node {
int data;
struct node* next;
};
/*
Build the list {1, 2, 3} in the heap and store
its head pointer in a local stack variable.
Returns the head pointer to the caller.
*/
struct node* BuildOneTwoThree() {
struct node* head = NULL;
struct node* second = NULL;
struct node* third = NULL;
head = malloc(sizeof(struct node)); // allocate 3 nodes in the heap
second = malloc(sizeof(struct node));
third = malloc(sizeof(struct node));
head->data = 1; // setup first node
head->next = second; // note: pointer assignment rule
second->data = 2; // setup second node
second->next = third;
third->data = 3; // setup third link
third->next = NULL;
// At this point, the linked list referenced by "head"
// matches the list in the drawing.
return head;
}

void Push(struct node** headRef, int data) {
struct node* newNode = malloc(sizeof(struct node));
newNode->data = data;
newNode->next = *headRef; // The '*' to dereferences back to the real head
*headRef = newNode; // ditto
}
void PushTest() {
struct node* head = BuildTwoThree();// suppose this returns the list {2, 3}
Push(&head, 1); // note the &
Push(&head, 13);
// head is now the list {13, 1, 2, 3}
}