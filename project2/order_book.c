#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>
#define SIZE 15

int globalcount=0;
char symbol2[5];
void leave(int sig){
  printf("Program killed after processing %ld messages for symbol %s.\n",globalcount,symbol2);
  exit(0);
}
void leave2(int sig){
  printf("Program died from a segmentation fault after processing %d messages for symbol %s.\n",globalcount,symbol2);
  exit(0);
}

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
  

}/*__attribute__ ((__packed__))*/;




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

// void setSortPrice(struct lnode **head, struct lnode **tail,double price, struct lnode *node){
// 	struct lnode *np=*head;
// 	
// 	deleteSortNode(head,tail,node);
// 	
// 	while (np!=NULL){
// 	if(node->price<np->price){
// 	  node->sortprev=np->sortprev;
// 	  node->sortnext=np;
// 	  break;
// 	}
// 		  
// 
// 	  if (np->sortnext==NULL){
// 	  node->sortprev=np;
// 	  node->sortnext=NULL;
// 	  
// 	}
// 	  np=np->sortnext;	  
//       }
// }





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
    FILE *output=stdout;
    FILE *output2=stdout;
    
    output2=fopen("iq.txt","w");
    output=fopen("ob.txt","w");
	  
    int ifinput=0;
    int ifoutput=0;
    int ifhash=0;
    int ifbinary=0;
    int ifselected=0;
    int messagecount=1000;
    int count=0;
    int ifsymbol=0;
    double du=0;
    
    char in[]="-i";
    char symbolname[]="-s";
    char hash[]="-h";
    char binary[]="-b";
    char countflag[]="-n";
//     char selectedsymbol[4];
    
   struct lnode *hashmaphead[SIZE];
   struct lnode *hashmaptail[SIZE];

   
    char command;
    unsigned int id;
    char side;
//    char symbol2[5];
    char symbol[5];
    unsigned int quantity;
    double price;
    
    struct lnode *node, *sellhead,*selltail,*buyhead,*buytail;
    
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
      
      
      if (strcmp(argv[i],binary)==0){
// 	input=fopen(argv[i+1],"r");
	ifbinary=1;
	
      }
      
      if (strcmp(argv[i],symbolname)==0){
	ifsymbol=1;
	strcpy (symbol2,argv[i+1]);
	
      }
      
      if (strcmp(argv[i],countflag)==0){
// 	input=fopen(argv[i+1],"r");
	messagecount= atoi( (argv[i+1]) );
	
      }
      
      
	//else input=stdin;
	  
      
    //  if (strcmp(argv[i],out)==0){

	
  //    }
  
// 	ifhash=1;
//       }
    }

//     printf("%s",symbol2);
    int dm=0;
    if (!ifsymbol){
    printf("Please enter -s symbol\n");
    exit(0);
    }

	
      while (!feof(input)){

	
	 if(ifbinary==1){
   
      if(fread(&command,sizeof(char),1,input));
      else break;
   //   fread(&id, sizeof(unsigned int),1 ,fr);
//        c=s.mtype;
        
      } 
      else
      fscanf(input,"%c",&command);
      			

	if (command=='A'){
	  
	if (ifbinary==0){
	fscanf(input," %ld %c %s %d %lf\n",&id,&side,symbol,&quantity,&price);
      
	}
	else{
	fread(&id,sizeof(unsigned int),1,input);
		fread(&side,sizeof(char),1,input);
			fread(symbol,4*sizeof(char),1,input);
			symbol[4]='\0';
				fread(&quantity,sizeof(unsigned int),1,input);
					fread(&price,sizeof(double),1,input);
	  
	}
	

	

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
	  if (ifbinary==0){
	  fscanf(input," %ld %s\n",&id,symbol);
	  }
	  else{
	    	fread(&id,sizeof(unsigned int),1,input);
			fread(symbol,4*sizeof(char),1,input);

	  }
	  
	  

	
	
	
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
	  if (ifbinary==0){
	  fscanf(input," %ld %s %d\n",&id,symbol,&quantity  );	
	  }
	  else{
	    	    	fread(&id,sizeof(unsigned int),1,input);
			fread(symbol,4*sizeof(char),1,input);
 			symbol[4]='\0';
			fread(&quantity,sizeof(unsigned int),1,input);
			
			
	  }
	  
	  

	  
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
	
else 	if (command=='C'){
	  if (ifbinary==0){
	  fscanf(input," %ld %s %d\n",&id,symbol,&quantity  );	
	  }
	  else{
	    	    	fread(&id,sizeof(unsigned int),1,input);
			fread(symbol,4*sizeof(char),1,input);
 			symbol[4]='\0';
			fread(&quantity,sizeof(unsigned int),1,input);
			
			
	  }
	  

	  
	  
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
	 if (ifbinary==0){
	  fscanf(input," %ld %s %d %lf\n",&id,symbol,&quantity,&price);
	  
	  }
	  else{
	    
	    	    	fread(&id,sizeof(unsigned int),1,input);
			fread(symbol,4*sizeof(char),1,input);
			symbol[4]='\0';
			fread(&quantity,sizeof(unsigned int),1,input);
			fread(&price,sizeof(double),1,input);
			
			//fprintf(stderr,"R %ld %s %d %lf\n",id,symbol,quantity,price);
	  }
	  

	  
	  
	  
	  
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
	  //fprintf(stderr,"R:=========\n");
	side=node->side;

	
	  
	//delete  

		  
		if (node!=NULL) {
		if (node->side=='B'){
		  deleteSortNode(&buyhead, &buytail, node);
		}
	// //  	
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
	
	


 	if(count>=messagecount){
	  count=0;
// 	    node=sellhead;
// 	   
	  double temp=du;
	  double temp1=du;
// 	    while (node!=NULL ){
	    if(sellhead!=NULL){
	      temp=sellhead->price;

	      
	    }
	    
	    if(buytail!=NULL){
	      temp1=buytail->price;
	    }

	    
	      
	      
 	    fprintf(output2,"%lf %lf\n",temp,temp1);
// 	    //node=node->next;
	
 	}
// 	}
      }
      
      fclose(input);
      
      
      	//if((count%messagecount)==0){
// 	    node=sellhead;
// 	   
// 	    while (node!=NULL ){
// 	   //  if(sellhead!=NULL&&buytail!=NULL)
// 	    fprintf(output2,"%lf %lf\n",node->price,buytail->price);
// 	    node=node->next;
// 	
// 	  //}
// 	}

      
      
      
     for(int i=0;i<SIZE;i++){
      node=hashmaphead[i];
      	while (node!=NULL ){
// 	    for (int j=0;j<4;j++){
// 	      symbol[i]=node->symbol[i];
// 	    }
// 	    symbol[4]='\0';
//  	    if (strncmp(symbol2,node->symbol,4)==0)
	    fprintf(output,"%d %c %d %lf\n",node->id,node->side,node->quantity,node->price);
	    node=node->next;
	
      }
      }
      

      
      
      
      


    return 0;
  
  
}



