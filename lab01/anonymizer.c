#include <stdio.h>
int main(){
char buf[2048];
int c,d,i,m=0;
while ((c=getchar()) !=EOF){
	
buf[i++]=c;
}


while(m<i){
	if (buf[m]=='@'){
	int tem=m;	
	d=buf[m-1];	
	m--;
		while (d >='A'&& d<='Z'||d>='a'&& d<='z'||d>='0'&& d<='9'){
			buf[m--]='X';
 			
                       d=buf[m];	
		}
m=tem;

}
	m++;
}

m=0;

while(m<i){
printf("%c",buf[m]);
m++;
}
	
return 0;
}
