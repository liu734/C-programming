#include <stdio.h>
#include<stdlib.h>
static const int count =10000000;
int main(){
  
  int i,rep,res;
  int* ints=(int*)malloc(count*sizeof (int));
  for (i=0;i<count;i++){
    ints[i]=i;
  }
  res=0;
  for (rep=0;rep<10;rep++){
    for(i=0;i<count;i++){
      res +=ints[i];
    }
  }
  printf("%d\n",res);

  
}
