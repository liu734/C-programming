#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "words.h"

/**
 * Read one line from standard input into {buf}. \n will be put in {buf} too
 * if there is one. Returns the length of the message. Return EOF if there are
 * no more lines to read.
 */
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

/**
 * Find the next word. {msg} is a pointer to an array of characters.
 * {len} is the length of the {msg} array. {end} is a pointer to an integer that
 * holds the current position in the array of characters.
 *
 * The function finds the next word, starting from the position given by the
 * initial value of {end}.
 *
 * If a word was found the function returns 1, and updates {start} to point to
 * the index of the first character in the word, {end} to point to the index of
 * the first character after the word.
 *
 * If no word was found, the function returns 0.
 */
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

/**
 * Check if {word} is contained in {keywords}. If yes, erase {word} with
 * white spaces. {len} indicates the length of {word}, and {num} indicates
 * the length of the keyword list.
 */
void checkWord(char* word, int len, char** keywords, int num) {
  int identity;
  int clean=0;

  for(int i=0; i<num;i++){
    identity=1;

    
    for (int j=0;j<strlen(*(keywords+i));j++)
    {
      
  
      if ((*(*(keywords+i)+j))!=*(word+j)){
	identity=0;

      }
      }
      
      if (identity==1){
	clean=1;
      }
      
  }
  
          //printf("%d",identity);
      
    
	if(clean==0){
	  return;
	}
	else{
      for(int k=0;k<len;k++)
       spaceOut(word,len);
	}
  
  /*  FILL IN HERE  */
// Please remove the abort() when you implement this function
}

/*
 * Change the character pointed by {c} to lower case if it is a capital.
 */
void unCapitalize(char* c) {
if ((*c>='A') && (*c<= 'Z')){

      *c= *c+32;
      }
  /*  FILL IN HERE  */
   // Please remove the abort() when you implement this function
}
