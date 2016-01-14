#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct sea_animal {
char name[20];
int age;
double weight;
void (*eat)(struct sea_animal*);
void (*swim)(struct sea_animal*, int);
};

void whale_eat(struct sea_animal* this){
  double food=this->weight*0.5;
  this->weight=(this->weight)*1.05;

  
  
  if (this->weight>400000){
    this->weight=400000;
    
  }
  
  printf("%s happily ate %0.2f pounds of food. Its weight is now %0.2f pounds.\n",this->name,food,this->weight); 
  
  
};
void whale_swim(struct sea_animal* this, int hours){
   double mile=hours*3 * (this->age) * (200000 / this->weight);
   printf("%s happily swam %.2f miles.\n",this->name,mile);
  
};

void shark_eat(struct sea_animal* this){
  double food=this->weight*0.1;
  this->weight=(this->weight)*1.01;

  
  
  if (this->weight>2000){
    this->weight=2000;
    
  }
  
  printf("%s happily ate %.2f pounds of food. Its weight is now %.2f pounds.\n",this->name,food,this->weight);  
  
  
  
};
void shark_swim(struct sea_animal* this, int hours){
   double mile=hours*10 * (this->age) * (1000 / this->weight);
   printf("%s happily swam %.2f miles.\n",this->name,mile);

};

struct sea_animal* whale_new(char *name, int age, double weight){
    struct sea_animal* whale;
    whale=(struct sea_animal*)malloc(sizeof (struct sea_animal));
    strcpy(whale->name,name);
    whale->age=age;
    whale->weight=weight;
    whale->eat=&whale_eat;
    whale->swim=&whale_swim;
    
    
    return whale;
    
    
};
struct sea_animal* shark_new(char *name, int age, double weight){
    struct sea_animal* shark;
    shark=(struct sea_animal*)malloc(sizeof (struct sea_animal));
    strcpy(shark->name,name);
    shark->age=age;
    shark->weight=weight;
    shark->eat=&shark_eat;
    shark->swim=&shark_swim;
    
    
    return shark;
  
};

void readline(char c[]) // read a line of text from stdin to char array c
{
int i=0;
while((c[i++]=getchar())!='\n');
c[i-1]='\0';
}


int main(int argc, char *argv[]){
  char newpet;
  char name[20];
  int age;
  double weight;
  char temp[20];
  char input;
  int hour;
  struct sea_animal *mypet;
  
  
  printf("Create your new pet, whale or shark? (w/s): ");
  newpet=getchar();
  getchar();
  printf("Pet's name: ");
  readline(name);
  printf("Age: ");
  readline(temp);
  age=atoi(temp);
  printf("Weight: ");
  readline(temp);
  weight=atof(temp);
  printf("Pet created!\n");
  
  
  if (newpet=='w'){
    mypet=whale_new(name,age,weight);
    
  }
  if (newpet=='s'){
    mypet=shark_new(name,age,weight);
    
  }
  
  while(input!='3'){
  printf("Have fun with your new pet %s:\n",name);
  printf("1. Feed\n2. Walk\n3. Play later\n\nInput: ");
  input=getchar();
  getchar();

  if (input=='1'){

    mypet->eat(mypet);
    
  }
  
  else if (input=='2'){
    mypet->swim;
    printf("For how many hours?: ");
    readline(temp);
    hour=atoi(temp);
    mypet->swim(mypet,hour);    
    
  }
    
  
  }
  printf("Quit.\n");
  
  
  
  

 



 
  
  
  
  
}