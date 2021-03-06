#include <stdlib.h>

/**
 * Test if {ch} is a letter (a - z or A - Z).
 * Return 1 if yes, otherwise 0.
 */
int isAlpha(char ch) {
  /* FILL IN HERE */

  if (((ch>='a') && (ch<= 'z'))||((ch>='A') && (ch<= 'Z')))
    return 1;
  else
    return 0;
  
}

/**
 * Return the length of the zero terminated string {s}.
 * The \0 character is not counted, e.g. the length of "abc" is 3.
 */
int strLen(char* s) {
  /* FILL IN HERE */

  char* index=s;
  while (*s!='\0'){
      s++;
  }
  
  return s-index;
  
  
}

/**
 * Compare the first {n} characters of string {s1} and {s2}.
 * If identical, return 1. Otherwise return 0.
 */
int strNCmp(char* s1, char* s2, int n) {
  /* FILL IN HERE */

  for(int i;i<n;i++){
    if(*s1!=*s2)
    return 0;
    
    s2++;
    s1++;

    
  }
    return 1;

  
}

/**
 * Replace every character of {s} with a white space.
 * {len} indicates the length of {s}.
 */
void spaceOut(char* s, int len) {
  /* FILL IN HERE */
 
  for (int i;i<len;i++){
    *s=' ';
    s++;
  }
  

  
  
}
