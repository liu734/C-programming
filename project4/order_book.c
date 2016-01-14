#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>
#include "market.h"
#define SIZE 1000


struct lnode {

    unsigned int id;
    char symbol[4];
    char side;
    unsigned int quantity;
    double price;
    struct lnode* next;
    struct lnode* prev;
    struct lnode* sortprev;
    struct lnode* sortnext;
  

};


int globalcount=0;
char symbol2[5];
int ifpred=0;

int N=14;
int M=3;
double* t;
double C;
double L;
double H;
double FSO;
double SSO;
double signal_line;
double* lastF;
double lastSSO=0;
    struct lnode *node=NULL;
     struct lnode *sellhead=NULL;
      struct lnode *selltail=NULL;
      struct lnode *buyhead=NULL;
        struct lnode *buytail=NULL;
void leave(int sig){
  printf("Program killed after processing %d messages for symbol %s.\n",globalcount,symbol2);
  exit(0);
}
void leave2(int sig){
  printf("Program died from a segmentation fault after processing %d messages for symbol %s.\n",globalcount,symbol2);
  exit(0);
}
int cmsk;
struct prediction get_prediction(){
  struct prediction pred;
  
  if (ifpred==1){
	     if(sellhead)
	        SSO=sellhead->price;
	     else
	        SSO=0.0;
	     if(sellhead==NULL)
	     signal_line=0.0;
	     else
	     signal_line=buytail->price;
	      
//      printf("mlgbd");
//   struct lnode *mklu=sellhead;
//   while (mklu){
//     printf("`````~~~%lf\n",mklu->price);
//     mklu=mklu->sortnext;
//     
//   }
	  }
 
//   cmsk++;
//   if(cmsk>5)exit(0);
  pred.SSO=SSO;
  pred.signal_line=signal_line;
  
  if ((lastSSO>80)&&(SSO<80)&&(signal_line<SSO)){
    pred.alert=SELL;
  }
  
  else if ((lastSSO<20)&&(SSO>20)&&(signal_line>SSO)){
    pred.alert=BUY;
  }
  
  else
    pred.alert=NO_ACTION;
  
  if (ifpred==1){
     
    pred.alert=NO_ACTION;
	     
    }
	 lastSSO=SSO; 

  

  
  return pred;
}








struct lnode *newNode(struct lnode **head, struct lnode **tail, unsigned int id, char side, unsigned int quantity,  double price) {
    struct lnode *np;
    np=(struct lnode*)malloc(sizeof (struct lnode));

    np->id=id;
    np->side=side;
    np->quantity=quantity;
    np->price=price;

    if(*head==NULL&&*tail==NULL){
      np->prev=NULL;
      *head=np;
      *tail=np;
    np->next=NULL;
    

    }
    else {
    np->next=NULL;
      
      (*tail)->next=np;
      np->prev=*tail;
      *tail=np;
    }
    
    
    
    
    return np;
}

struct lnode *newSortNode(struct lnode **head, struct lnode **tail, struct lnode *node) {
    struct lnode *np=*head;
    
    if(*head==NULL&&*tail==NULL){
      node->sortprev=NULL;
      *head=node;
      *tail=node;
      node->sortnext=NULL;
    

    }
    
    else if(node->price<=(*head)->price){	
	   (*head)->sortprev=node;
	   node->sortnext=*head;
           *head=node; 
    }

   else if(node->price>(*tail)->price){
           (*tail)->sortnext=node;
           node->sortprev=*tail;
           *tail=node;
    }
    
    else {
      

      while (np!=NULL){
       if((node->price)<=(np->price)){
	              node->sortprev=np->sortprev;
             np->sortprev->sortnext=node;

             node->sortnext=np;
	     np->sortprev=node;

             break;      
           }             
	  np=np->sortnext;	  
      }
	  
	
      
      

      
      
      
    }
    
    return node;
    
    
  
  
}



void deleteNode(struct lnode **head, struct lnode **tail, struct lnode *node) {
    if(*tail==NULL&&*tail==NULL){

	free(node);
    }
    else if (*head==node&&*tail==node){
	

	free(node);
	*head=NULL;
	*tail=NULL;
    }
    
    else if(*head==node){
        node->next->prev=NULL;
	
	*head=node->next;
	

	free(node);
    }
    else if(*tail==node){
	node->prev->next=NULL;
	
	*tail=node->prev;

	free(node);
    }
    
    
    else{
    node->prev->next=node->next;
    node->next->prev=node->prev;
    free(node);
    }
    /* FILL THIS IN */
}

void deleteSortNode(struct lnode **head, struct lnode**tail, struct lnode*node) {
      if(*tail==NULL&&*tail==NULL){
	  return;
	//free(node);
      }
      else if (*head==node&&*tail==node){
	

	//free(node);
	*head=NULL;
	*tail=NULL;
      }
    
      else if(*head==node){
	*head=node->sortnext;
        (*head)->sortprev=NULL;

	

	//free(node);
      }
      else if(*tail==node){
		*tail=node->sortprev;
	(*tail)->sortnext=NULL;


	//free(node);
      }
    
    
      else{
      node->sortprev->sortnext=node->sortnext;
      node->sortnext->sortprev=node->sortprev;
      //free(node);
      }
  
  
  
}





void setPrice(struct lnode **head,unsigned int id, unsigned int quantity,double price){
  	struct lnode *node=*head;
	while (node!=NULL ){
		if((node->id)==id){
				node->quantity=quantity;
				node->price=price;	
				break;		
		}
		else
		  
		node=node->next;
	}
}








void setQuantity(struct lnode **head,unsigned int id, unsigned int quantity){
  	struct lnode *node=*head;
	while (node!=NULL ){
		if((node->id)==id){
		node->quantity=((node->quantity)-quantity);
		break;				
		}
		node=node->next;
	}
    

}

int main(int argc, char *argv[]){
    signal(SIGINT,leave);
    signal(SIGSEGV,leave2);
    FILE *input=stdin;
//     FILE *output=stdout;
//     FILE *output2=stdout;
    
//     output2=fopen("iq.txt","w");
//     output=fopen("ob.txt","w");
	  
    int ifinput=0;
    int ifoutput=0;
    int ifhash=0;
    int ifbinary=1;
    int ifselected=0;

    int messagecount=1000;
    int count=0;
    int ifsymbol=0;
    double du=0;
    
    char in[]="-i";
    char symbolname[]="-s";
    char hash[]="-h";
    char binary[]="-b";
    char dasht[]="-t";
    char dashm[]="-m";
    char dashn[]="-n";
    
    int dm=0;

    
   struct lnode *hashmaphead[SIZE];
   struct lnode *hashmaptail[SIZE];

   
    char command;
    unsigned int id;
    char side;

    char symbol[5];
    unsigned int quantity;
    double price;
    

    
    sellhead=NULL;
    selltail=NULL;
    buyhead=NULL;
    buytail=NULL;
    
    for(int i=0;i<SIZE;i++){
	hashmaphead[i]=NULL;
	hashmaptail[i]=NULL;
    }
    
    
    
    
    for (int i=0;i<argc;i++){
      
      if (strcmp(argv[i],in)==0){
	input=fopen(argv[i+1],"r");
	
	
	
      }
      
      if (strcmp(argv[i],symbolname)==0){
	ifsymbol=1;
	strcpy (symbol2,argv[i+1]);
	
      }
      
      if (strcmp(argv[i],dashm)==0){
	M= atoi( (argv[i+1]) );
	
      }
      
      if (strcmp(argv[i],dashn)==0){
	N= atoi( (argv[i+1]) );
	
      }      
      
      if (strcmp(argv[i],dasht)==0){
	ifpred=1;

      }      
      
      
      
      
      
    }
    
    double prevN[N+1];
    double lastFSO[M];
    double lastsignal[M];
    
    t= prevN;
    lastF=lastFSO;


    for(int i=0;i<N+1;i++){
	prevN[i]=0;
    }
    
    for(int i=0;i<M;i++){
	lastF[i]=0;
	lastsignal[i]=0;	
    } 
    


    if (!ifsymbol){
    printf("Please enter -s symbol\n");
    exit(0);
    }
    
    
    
    

    
    init_market(input, symbol2);
    pthread_t thread;
    pthread_create(&thread,NULL,market,NULL);
    
    unsigned int length;
    char* start;
    char* buffer;

    
    while(1){
      

    buffer=get_inputs(&length);
    start=buffer;
    
    if (length<=0) break;
	
      while (1){
      
	
       command=*((char*)buffer);
       buffer++;

	
// 	 if(ifbinary==1){
//    
//       if(fread(&command,sizeof(char),1,input));
//       else break;
// 
//       } 
//       else
//       fscanf(input,"%c",&command);
      			

	if (command=='A'){
	  
	id=*( (unsigned int*)buffer);
	buffer=buffer+sizeof(unsigned int);

	
	side=*((char*)buffer);
        buffer=buffer+sizeof(char);

        strncpy(symbol,buffer,4);

   	symbol[4]='\0';     
	buffer=buffer+4*sizeof(char);
        

        quantity=*((unsigned int*)buffer);
        buffer=buffer+sizeof(unsigned int);
        
	price=*((double*) buffer);
        buffer=buffer+sizeof(double);

// 	if (ifbinary==0){
// 	fscanf(input," %ld %c %s %d %lf\n",&id,&side,symbol,&quantity,&price);
//       
// 	}
// 	else{
// 	fread(&id,sizeof(unsigned int),1,input);
// 		fread(&side,sizeof(char),1,input);
// 			fread(symbol,4*sizeof(char),1,input);
// 			symbol[4]='\0';
// 				fread(&quantity,sizeof(unsigned int),1,input);
// 					fread(&price,sizeof(double),1,input);
// 	  
// 	}
	

	

	if (strncmp(symbol2,symbol,4)==0){
	   	count++;
		globalcount++;
	  	 int index=id%SIZE;
	node=newNode(&hashmaphead[index],&hashmaptail[index], id, side, quantity, price);
	

	
	
	

	  
	if (side=='B'){
	  
	  newSortNode(&buyhead, &buytail, node);

	}
	
	else if (side=='S'){
	  newSortNode(&sellhead, &selltail, node);

	}
	
	}
	}
	
	
	
	else if (command=='X'){
	  
	  
	id=*( (unsigned int*)buffer);
	buffer=buffer+sizeof(unsigned int);
/*	
	side=*((char*)buf);
        buffer=buffer+sizeof(char);*/

        strncpy(symbol,buffer,4);

   	symbol[4]='\0';     
	buffer=buffer+4*sizeof(char);
        
/*
        quantity=*((unsigned int*)buffer);
        buffer=buffer+sizeof(unsigned int);
        
	price=*((double*) buffer);
        buffer=buffer+sizeof(double);
	  */
// 	  if (ifbinary==0){
// 	  fscanf(input," %ld %s\n",&id,symbol);
// 	  }
// 	  else{
// 	    	fread(&id,sizeof(unsigned int),1,input);
// 			fread(symbol,4*sizeof(char),1,input);
// 
// 	  }
// 	  
	  

	
	
	
	if (strncmp(symbol2,symbol,4)==0){
	  	 count++;
		 globalcount++;
	node=hashmaphead[id%SIZE];
	while (node!=NULL ){
		if((node->id)==id){
		  break;
		}
		else
		node=node->next;
	  }

	

	  
 	if (node!=NULL) {
   	if (node->side=='B'){
   	  deleteSortNode(&buyhead, &buytail, node);
    	}
  	
   	else if (node->side=='S'){
   	  deleteSortNode(&sellhead, &selltail, node);
  	}
	}
 	
	
	  
	  deleteNode(&hashmaphead[id%SIZE], &hashmaptail[id%SIZE],node);
	
	}
	  
	}
	
	else if (command=='T'){
	  
	  	id=*( (unsigned int*)buffer);
	buffer=buffer+sizeof(unsigned int);
	
// 	side=*((char*)buf);
//         buffer+=sizeof(char);

        strncpy(symbol,buffer,4);

   	symbol[4]='\0';     
	buffer=buffer+4*sizeof(char);
        

        quantity=*((unsigned int*)buffer);
        buffer=buffer+sizeof(unsigned int);
        
// 	price=*((double*) buffer);
//         buffer=buffer+sizeof(double);
	  
// 	  if (ifbinary==0){
// 	  fscanf(input," %ld %s %d\n",&id,symbol,&quantity  );	
// 	  }
// 	  else{
// 	    	    	fread(&id,sizeof(unsigned int),1,input);
// 			fread(symbol,4*sizeof(char),1,input);
//  			symbol[4]='\0';
// 
// 			fread(&quantity,sizeof(unsigned int),1,input);
//  			
// 			
// 	  }
// 	  
	  

	  
	if (strncmp(symbol2,symbol,4)==0){
	  
	    count++;
	    globalcount++;
	    node=hashmaphead[id%SIZE];
	  while (node!=NULL ){
		if((node->id)==id){
		  break;
		}
		else
		node=node->next;
	  }
	  C=node->price;
	  setQuantity(&node,id,quantity);
	  
	  
	  
	  
	  
	  
	  
	  for (int i=0;i<N;i++){
	    prevN[i]=prevN[i+1];
	
	  }
	  
	  prevN[N]=C;
	  
	  L=10000.0;  
	  for (int i=0;i<N+1;i++){
	    if(L>prevN[i])
	      L=prevN[i];
	  }
	  
	  H=0.0;
	  
	  for (int i=0;i<N+1;i++){
	    if(H<prevN[i])
	      H=prevN[i];
	  }
	  
	  

	  for (int i=0;i<M-1;i++){
	    lastFSO[i]=lastFSO[i+1];
	  }
	  
	  FSO=((C-L)/(H-L))*100;
	  lastFSO[M-1]=FSO;
	  
	  
	  double sum=0;
	  for (int i=0;i<M;i++){
	    sum=sum+lastFSO[i];
	  }
	  
	  SSO=sum/M;
	  
	  for (int i=0;i<M-1;i++){
	    lastsignal[i]=lastsignal[i+1];
	  }
	  lastsignal[M-1]=SSO;
	  
	  
	  sum=0;
	  
	  for (int i=0;i<M;i++){
	    sum=sum+lastsignal[i];
	  }

	  signal_line=sum/M;
	  


	  
	  
	  
	  
	  
	  
	  
	  if(node->quantity==0){
	    
	     	if (node!=NULL) {
		    if (node->side=='B'){
		      deleteSortNode(&buyhead, &buytail, node);
		    }
		    
		    else if (node->side=='S'){
		      deleteSortNode(&sellhead, &selltail, node);
		    }
		    }
		    
		    
		      
		      deleteNode(&hashmaphead[id%SIZE], &hashmaptail[id%SIZE],node);
	    
	  }
	  


	  
	  
	  
	    break;
	  }
	  
	  
	
	}
	
else 	if (command=='C'){
  	id=*( (unsigned int*)buffer);
	buffer=buffer+sizeof(unsigned int);
/*	
	side=*((char*)buf);
        buffer+=sizeof(char);*/

        strncpy(symbol,buffer,4);
   	symbol[4]='\0';     
	buffer=buffer+4*sizeof(char);
        

        quantity=*((unsigned int*)buffer);
        buffer=buffer+sizeof(unsigned int);
        
// 	price=*((double*) buffer);
//         buffer=buffer+sizeof(double);
  
  
  
// 	  if (ifbinary==0){
// 	  fscanf(input," %ld %s %d\n",&id,symbol,&quantity  );	
// 	  }
// 	  else{
// 	    	    	fread(&id,sizeof(unsigned int),1,input);
// 			fread(symbol,4*sizeof(char),1,input);
//  			symbol[4]='\0';
// 			fread(&quantity,sizeof(unsigned int),1,input);
// 			
// 			
// 	  }
	  

	  
	  
	  if (strncmp(symbol2,symbol,4)==0){
	  
	    count++;
	    globalcount++;
	    node=hashmaphead[id%SIZE];
	  while (node!=NULL ){
		if((node->id)==id){
		  break;
		}
		else
		node=node->next;
	  }
	  
	  setQuantity(&node,id,quantity);
	  if(node->quantity==0){
	    
	     	if (node!=NULL) {
		    if (node->side=='B'){
		      deleteSortNode(&buyhead, &buytail, node);
		    }
		    
		    else if (node->side=='S'){
		      deleteSortNode(&sellhead, &selltail, node);
		    }
		    }
		    
		    
		      
		      deleteNode(&hashmaphead[id%SIZE], &hashmaptail[id%SIZE],node);
	    
	  }
	  }
	}
	
	else if (command=='R'){
	  	id=*( (unsigned int*)buffer);
	buffer=buffer+sizeof(unsigned int);
	
// 	side=*((char*)buf);
//         buffer+=sizeof(char);

        strncpy(symbol,buffer,4);

   	symbol[4]='\0';     
	buffer=buffer+4*sizeof(char);
        

        quantity=*((unsigned int*)buffer);
        buffer=buffer+sizeof(unsigned int);
        
	price=*((double*) buffer);
        buffer=buffer+sizeof(double);
// 	 if (ifbinary==0){
// 	  fscanf(input," %ld %s %d %lf\n",&id,symbol,&quantity,&price);
// 	  
// 	  }
// 	  else{
// 	    
// 	    	    	fread(&id,sizeof(unsigned int),1,input);
// 			fread(symbol,4*sizeof(char),1,input);
// 			symbol[4]='\0';
// 			fread(&quantity,sizeof(unsigned int),1,input);
// 			fread(&price,sizeof(double),1,input);
// 			
// 
// 	  }
// 	  

	  
	  
	  
	  
	if (strncmp(symbol2,symbol,4)==0){
		 count++;
		 globalcount++;
	  
	node=hashmaphead[id%SIZE];
	while (node!=NULL ){
		if((node->id)==id){
		  break;
		}
		else
		node=node->next;
	  }

	side=node->side;

	
	  
	//delete  

		  
		if (node!=NULL) {
		if (node->side=='B'){
		  deleteSortNode(&buyhead, &buytail, node);
		}

		else if (node->side=='S'){
		  deleteSortNode(&sellhead, &selltail, node);
		}
		}
		
		
	  
	deleteNode(&hashmaphead[id%SIZE], &hashmaptail[id%SIZE],node);
	
	
	
	//add
	int index=id%SIZE;
	node=newNode(&hashmaphead[index],&hashmaptail[index], id, side, quantity, price);

	

	  
	if (side=='B'){
	  newSortNode(&buyhead, &buytail, node);

	}
	
	else if (side=='S'){
	  newSortNode(&sellhead, &selltail, node);
	  
	}
	
	}
	    
	    
	    
	    
	  
	}
	
	


//  	if(count>=messagecount){
// 	  count=0;
// // 	   
// 	  double temp=du;
// 	  double temp1=du;
// 	    if(sellhead!=NULL){
// 	      temp=sellhead->price;
// 
// 	      
// 	    }
// 	    
// 	    if(buytail!=NULL){
// 	      temp1=buytail->price;
// 	    }
// 
// 	    
// 	      
// 	      
//  	    fprintf(output2,"%lf %lf\n",temp,temp1);
// 
// 	
//  	}

//       }
      
      
    }
    
    }
      
      fclose(input);
      

      
      
//      for(int i=0;i<SIZE;i++){
//       node=hashmaphead[i];
//       	while (node!=NULL ){
// 	    fprintf(output,"%d %c %d %lf\n",node->id,node->side,node->quantity,node->price);
// 	    node=node->next;
// 	
//       }
//       }
      

      
      
      
      


    return 0;
  
  
}



