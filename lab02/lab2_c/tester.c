#include <stdio.h>

extern int isAlpha(char);

int main(){
  char buf[2048];
  int c,m,i=0;
  while ((c=getchar())!=EOF){
    buf[i++]=c;
  }
  
  while (m<i){
    if(utils.isAlpha(m))
    prinf("%c",buf[m]);
      m++;
    
    
  }
  return 0;
  
}