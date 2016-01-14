//CS240 LAB 4
//JINGYE LIU



#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

int isAlpha(char ch) {
  /* FILL IN HERE */

  if (((ch>='a') && (ch<= 'z'))||((ch>='A') && (ch<= 'Z')))
    return 1;
  else
    return 0;
  
}

int readMsg(char* buf) {
  int c;
  int count=0;
  while ((c=getchar()) !=EOF){
    *buf=c;
    
    count++;
  
  if (c=='\n')
  return count;
  
  buf++; 
//msg[140]
  
  
  }
  if (count!=0)
    return count;
  
  else
  
  return EOF;
  /*  FILL IN HERE  */
  // Please remove the abort() when you implement this function
}

char* makeWord(char* word, int len) {
    char array[len+1];
    char* output=(char*)malloc (sizeof (char)*(len));
    for (int j=0;j<len;j++){
    array[j]=*(word+j);
    
    }
    array[len]='\0';
    output= array;
    return output;
}

void unCapitalize(char* c) {
if ((*c>='A') && (*c<= 'Z')){

      *c= *c+32;
      }
  /*  FILL IN HERE  */
   // Please remove the abort() when you implement this function
}

int getWord(char* msg, int len, int* start, int* end) {
    int i=*end;
    int j;
  
    if (len<=0)
      return 0;
    
    if(*end>=len)
      return 0;
    
    
    
    while(isAlpha(*(msg+i))==0&&i<len){
      i++;
    }
    
    
    if (i>=len)
      return 0;
    
    
    *start=i;
    
    
    j=i+1;
    
    while(isAlpha(*(msg+j))==1&&j<len){
      j++;
      
      
    }
    

    
    *end=j;

    
    return 1;
    
   
    
  
  /*  FILL IN HERE  */
  // Please remove the abort() when you implement this function
}




int main()
{
  char msg[256];
  int len;
  int start=0;
  int end=0;
  char* index=msg;
  int i=0;
  struct lnode* head, *tail,*node;
  head=NULL;
  tail=NULL;
  int line=1;
  

  
  while ((len=readMsg(msg))!=EOF){
      start=0;
      end=0;
      
      	i=0;
	              while (i<len){
	unCapitalize(index+i);
	i++;
	      
	}

      
      
      

      while (getWord(msg,len,&start,&end)) {

  
	
	
	int length=end-start;
    char array[length+1];
    for (int j=0;j<length;j++){
    array[j]=*(index+start+j);
    
    }
    array[length]='\0';
	//printf("%c",*index);
	
	char* output;

	//output=makeWord(index+start,length);

	    
	    if(getNode(&head, &tail,array, line)==NULL)
	    
	    newNode(&head,&tail,array,line);
	    else
	    nodeIncCount(getNode(&head, &tail,array, line));
	   
	    
	    

    }

    line++;
    
    node=head;
    if(node!=NULL){
    do
    if((line-nodeGetLine(node) > 99) && (nodeGetCount(node) == 1))
    deleteNode(&head, &tail, node);
    while((node = nodeGetNext(node)) != NULL);
    }
  
  
  }
  

  
  
  
    for (node = head; node != NULL; node = nodeGetNext(node)){
      if(nodeGetCount(node)>1)

      printf("%s: %d\n", nodeGetWord(node), nodeGetCount(node));
      
    
  }
  
  
  
    return 0;


}
