#include <stdio.h>
#include "words.h"
#define SIZE 140

int main(int argc, char** argv) {
  char msg[SIZE]; 
  char* point;
  int msgLength = 0;
  int currentNum = 0; 
  int startNum = 0;
  int endNum = 0;
  int* startNumPointer = 0;
  int* endNumPointer = 0;
 
  while ((msgLength = readMsg(msg)) != EOF) {
    // get every word in the current line
    point = msg;
    startNum = 0;
    endNum = 0;
    startNumPointer = &startNum;
    endNumPointer = &endNum;


    for(int j = 0; j < msgLength; j++) {
      printf("%c", *(point + j));
    }
  }
  return 0;
}
