#include <stdio.h>
#include "words.h"

int main(int argc, char** argv) {

	char msg[SIZE];
	int len;
	int start=0;
	int end=0;
	char* index=msg;
	int i=0;

  // read in every line of the tweets
  while ((len=readMsg(msg))!=EOF) {
      start=0;
      end=0;


    // get every word in the current line
    while (getWord(msg,len,&start,&end)) {
	    i=0;
	    while (i<len){
		unCapitalize(index+i);
	    i++;
	      
	    }
      // turn the word to small case
		checkWord(index+start,end-start,argv+1,argc-1);

      // check and process the word
    }
    i=0;
    while(i<len){
      printf("%c", msg[i]);
      i++;
    }
    // output the processed message
  }
  return 0;
}
