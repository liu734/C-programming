#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define SIZE 15

struct lnode {

    long id;
    char* symbol;
    double price;
    int quantity;
    char side;
    struct lnode* next;
    struct lnode* prev;

};

struct lnode *newNode(struct lnode **head, struct lnode **tail, long id, char side, int quantity,  double price) {
	struct lnode *np;
    np=(struct lnode*)malloc(sizeof (struct lnode));
	//char* np_symbol;
	//np_symbol=(char*)malloc(sizeof (char)*(strlen(symbol)+1));
    
    //strcpy(np->symbol,symbol);
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

void deleteNode(struct lnode **head, struct lnode **tail, struct lnode *node) {
    if(*tail==NULL&&*tail==NULL){
//	free(node->w);
	free(node);
    }
    else if (*head==node&&*tail==node){
	
//     	free(node->w);
	free(node);
	*head=NULL;
	*tail=NULL;
    }
    
    else if(*head==node){
        node->next->prev=NULL;
	*head=node->next;
	
//	free(node->w);
	free(node);
    }
    else if(*tail==node){
	node->prev->next=NULL;
	*tail=node->prev;
//	free(node->w);
	free(node);
    }
    
    
    else{
    node->prev->next=node->next;
    node->next->prev=node->prev;
//    free(node->w);
    free(node);
    }
    /* FILL THIS IN */
}

void setPrice(struct lnode **head,long id, int quantity,double price){
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

void setQuantity(struct lnode **head,long id, int quantity){
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
    FILE *input=stdin;
    FILE *output=stdout;
    int ifinput=0;
    int ifoutput=0;
    int ifhash=0;
    
    char in[]="-i";
    char out[]="-o";
    char hash[]="-h";
   struct lnode *hashmaphead[SIZE];
   struct lnode *hashmaptail[SIZE];
   
    char command;
    long int id;
    char side;
    char symbol[5];										
    int quantity;
    double price;
    
    struct lnode *head, *tail, *node;
    for(int i=0;i<SIZE;i++){
	hashmaphead[i]=NULL;
	hashmaptail[i]=NULL;
      } 
    
    
    for (int i=0;i<argc;i++){
      if (strcmp(argv[i],in)==0){
	input=fopen(argv[i+1],"r");
	
	
      }
	//else input=stdin;
	  
      
      if (strcmp(argv[i],out)==0){
	output=fopen(argv[i+1],"w");
	
      }
      //else output=stdout;
      
      if (strcmp(argv[i],hash)==0){
	ifhash=1;
      }
    }

      if(ifhash==0){
      
      head=tail=NULL;
      
      while (!feof(input)){
	fscanf(input,"%c",&command);

	if (command=='A'){
	 fscanf(input," %ld %c %s %d %lf",&id,&side,symbol,&quantity,&price);
	newNode(&head, &tail, id, side, quantity, price);
	  
	}
	if (command=='X'){
	  fscanf(input," %ld %s",&id,symbol);
	node=head;
	while (node!=NULL ){
		if((node->id)==id){
		  break;
		}
		else
		node=node->next;
	  }
	  deleteNode(&head, &tail,node);
	}
	
	if (command=='T'){
	  fscanf(input," %ld %s %d",&id,symbol,&quantity  );	
	  setQuantity(&head,id,quantity);
	  
	}
	
	if (command=='C'){
	  fscanf(input," %ld %s %d",&id,symbol,&quantity);
	  setQuantity(&head,id,quantity);
	}
	
	if (command=='R'){
	  fscanf(input," %ld %s %d %lf",&id,symbol,&quantity,&price);
	  setPrice(&head,id,quantity,price);
	}	

      }
      
      fclose(input);
      
       
      
    
  
	node=head;
      	while (node!=NULL ){
	    fprintf(output,"%ld %c %d %lf\n",node->id,node->side,node->quantity,node->price);
	    node=node->next;
	
      }
 
      }
      
      else{


	
      while (!feof(input)){
	fscanf(input,"%c",&command);

	if (command=='A'){
	 fscanf(input," %ld %c %s %d %lf",&id,&side,symbol,&quantity,&price);
	int index=id%SIZE;
	newNode(&hashmaphead[index],&hashmaptail[index], id, side, quantity, price);
	  
	}
	if (command=='X'){
	  fscanf(input," %ld %s",&id,symbol);
	node=hashmaphead[id%SIZE];
	while (node!=NULL ){
		if((node->id)==id){
		  break;
		}
		else
		node=node->next;
	  }
	  deleteNode(&hashmaphead[id%SIZE], &hashmaptail[id%SIZE],node);
	}
	
	if (command=='T'){
	  fscanf(input," %ld %s %d",&id,symbol,&quantity  );	
	  setQuantity(&hashmaphead[id%SIZE],id,quantity);
	  
	}
	
	if (command=='C'){
	  fscanf(input," %ld %s %d",&id,symbol,&quantity);
	  setQuantity(&hashmaphead[id%SIZE],id,quantity);
	}
	
	if (command=='R'){
	  fscanf(input," %ld %s %d %lf",&id,symbol,&quantity,&price);
	  setPrice(&hashmaphead[id%SIZE],id,quantity,price);
	}	

      }
      
      fclose(input);
      
     for(int i=0;i<SIZE;i++){
      node=hashmaphead[i];
      	while (node!=NULL ){
	    fprintf(output,"%ld %c %d %lf\n",node->id,node->side,node->quantity,node->price);
	    node=node->next;
	
      }
      }
      
	
      }
      
      
      


    return 0;
  
  
}



