#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "list.h"
#include <string.h>
struct lnode {
    /* FILL THIS IN */
    char *w;
    int count;
    int l;
    struct lnode* next;
    struct lnode* prev;
};

/**
 * In the linked list with *head and *tail as head and tail pointers,
 * add a newly-created node to the tail of the list. The new node has
 * the given word and line, and a count of 1. You must duplicate word,
 * as the original word may be modified by the calling function. Return
 * value is the newly-created node.
 */
struct lnode *newNode(struct lnode **head, struct lnode **tail, char *word, int line) {
          struct lnode *np;
    np=(struct lnode*)malloc(sizeof (struct lnode));
     
    np->w=(char*)malloc (sizeof (char)*(strlen(word)+1));
    
    
    if(*head==NULL&&*tail==NULL){
      np->prev=NULL;
      *head=np;
      *tail=np;
      

     

    strcpy(np->w,word);
    np->next=NULL;
    np->count=1;
    np->l=line;
    

    }
    else {


    strcpy(np->w,word);
    np->next=NULL;
    np->count=1;
    np->l=line;
      
      (*tail)->next=np;
      np->prev=*tail;
      *tail=np;
     
     // printf("%s",(*tail)->prev->w);
    }
    
    return np;
    
    

    
    

    
    /* FILL THIS IN */
}

/**
 * Removes the specified node from the list, and frees all memory the node is using.
 * Remember that if *head or *tail are the node, they will need to be updated!
 */
void deleteNode(struct lnode **head, struct lnode **tail, struct lnode *node) {
    if(*tail==NULL&&*tail==NULL){
	free(node->w);
	free(node);
    }
    else if (*head==node&&*tail==node){
	
      	free(node->w);
	free(node);
	*head=NULL;
	*tail=NULL;
    }
    
    else if(*head==node){
        node->next->prev=NULL;
	*head=node->next;
	
	free(node->w);
	free(node);
    }
    else if(*tail==node){
	node->prev->next=NULL;
	*tail=node->prev;
	free(node->w);
	free(node);
    }
    
    
    else{
    node->prev->next=node->next;
    node->next->prev=node->prev;
    free(node->w);
    free(node);
    }
    
    /* FILL THIS IN */
}

/**
 * Simply returns the next node in the list, or NULL if there are no further nodes.
 */
struct lnode *nodeGetNext(struct lnode *node) {
    /* FILL THIS IN */
    return (node->next);
}

/**
 * Simply returns the word in the given node.
 */
char *nodeGetWord(struct lnode *node) {
    return (node->w);
    /* FILL THIS IN */
}

/**
 * Simply returns the line in the given node.
 */
int nodeGetLine(struct lnode *node) {
    return (node->l);
    /* FILL THIS IN */
}

/**
 * Simply returns the count in the given node.
 */
int nodeGetCount(struct lnode *node) {
    return (node->count);  
  /* FILL THIS IN */
}

/**
 * Increments the count in the given node, and returns the new count.
 */
int nodeIncCount(struct lnode *node) {
    
  return ++(node->count);
    /* FILL THIS IN */
}

/**
 * If the linked list with *head and *tail as head and tail pointers contains
 * a node with the specified word, that node is returned, with its line updated
 * to the specified line. Otherwise, returns NULL.
 */
struct lnode *getNode(struct lnode **head, struct lnode **tail, char *word, int line) {


  if(*head==NULL&&*tail==NULL){
      return NULL;
  }
    
  else {
    struct lnode *node=*head;
    while ((node->next)!=NULL){


//	  printf("%s",node->w);
    if(strcmp((node->w),word)==0){
      node->l=line;
      return node;
      

      
    }
          node=(node->next);
    
  }
    if (strcmp((node->w),word)==0){
      node->l=line;
      return node;
    }
  }
  return NULL;
  
    /* FILL THIS IN */
}

/**
 * Deletes every node in the list with *head and *tail as head and tail pointers.
 * After calling this function, all memory used by the list should be freed,
 * and *head and *tail should both be NULL.
 */
void deleteList(struct lnode **head, struct lnode **tail) {
  struct lnode *node=*head;
  if(*head==NULL&&*tail==NULL){
    
  }
  else{
  while ((node->next)!=NULL){
    node=(node->next);
    free(node->prev->w);
    free(node->prev);

    }
    
    free(node->w);
    free(node);
    *head=NULL;
    *tail=NULL;

  }
  
    /* FILL THIS IN */
}
