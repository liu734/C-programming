#include <stdio.h>
#include<stdlib.h>
struct lnode {
    long value;
    struct lnode* next;
  
};

struct lnode* List (struct lnode *next){
  struct lnode *node;
  node=(struct lnode*)malloc(sizeof (struct lnode));
  if(node==NULL){exit(0);}
  node->next=next;
  if(next==NULL){
    (node->value)=0;
  }else{
    (node->value)=(next->value)+1;
  }
  return node;
  

}

int main(){
  
 struct lnode *cur=NULL;
 cur=List(cur);


   while(1){
    cur= List(cur);
    if(((cur->value)%100000)==0){
	printf("%ld\n",(cur->value));
    }
  }
  
  return 0;

}

