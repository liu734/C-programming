#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "words.h"

/**
 * Read one line from standard input into {buf}. \n will be put in {buf} too
 * if there is one. Returns the length of the message. Return EOF if there are
 * no more lines to read.
 */
int readMsg(char* buf) {
  char c;
  int count=0;
  while ((c=getchar()) !=EOF){
    *buf=c;  
  
  if (c=='\n')
  return count;
    

  
  buf++; 
  count++;
  
  
  }
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
  int count=0;
  
    if (len<=0)
      return 0;
    if (*end>=len)
      return 0;
    
    while (*(msg+*end)!=' '&&*(msg+*end)!='\n'){
	 *end++;
	 count++;
    }
    
    *start=*end-count;
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
  for(int i=0; i<num;i++)
    for (int j=0;j<len;j++)
    {if ((*(*(keywords+i)+j))!=*(word+j))
	return;}
     for(int k=0;k<len;k++)
       spaceOut(word,len);
     
  
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
