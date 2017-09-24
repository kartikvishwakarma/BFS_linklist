/*
   KARTIK VISHWAKARMA
   2017CSM1001
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int total_weight=0;
struct VList{                             /* A node to represent all Vertices presented in Graph*/
 	 int src;                                 /* src-: Head node number*/
	 bool visited;                            /*boolean variable :  where node explored(visited) or not*/
	 struct VList *v_next;                      /*pointer to point all Vertices presented in Graph*/
	 struct EList *e_next;                     /*pointer to set of edges connected to Vertices*/
};

struct EList{                             /*A node to represent connected edges to a vertex */
	 int dest;                                /*Tail node number*/
	 int weight;                              /*weight of edges between two node*/
	 struct EList* e_next;                     /* all edge connected to a vertex*/
};

struct Queue{                             /*Queue to implement Breath first search*/
	 int data;
	 struct Queue* v_next;
	} *rear, *front;                          /*pointer to head and tail of queue*/


 /*A function to create Vertex List Node*/  
struct VList *create_VList(int src){                    
	 struct VList *newNode=(struct VList*)malloc(sizeof(struct VList));
	 newNode->src=src;                            
 	newNode->visited=false;
	 newNode->e_next=NULL;
return newNode;
}

/*A function to create Edges List Node*/
struct EList *create_EList(int dest, int weight){
	 struct EList *newNode=(struct EList*)malloc(sizeof(struct EList));
	 newNode->dest=dest;
	 newNode->weight=weight;
	 newNode->e_next=NULL;
 return newNode;
}
 
/*A function to check whether queue empty or not*/ 
bool isEmpty(){
	 if(front==NULL)
  	 return true;
  return false;
}

/*Function for  insert queue nodes */
void Enqueue(int data){
	 struct Queue* q=(struct Queue*)malloc(sizeof(struct Queue));
	 q->data=data;
	 q->v_next=NULL;
 
	 if(rear==NULL) /*Initial case  when queue Empty*/
 	 rear=front=q;  
	 else{
  	 rear->v_next=q;
  	 rear=q;
  }
}

/*function to remove elment in Queue*/
	int Dequeue(){
	int data;
        if(isEmpty())               /*Case 1: All elment of queue removed*/
  	 return -1;
  	 else if(front==rear)      /*Case2: Only one elment in queue*/
  	 {
	  	 data=front->data;
 	   	 struct Queue* ptr=front;
 	 free(ptr);
 	 front=rear=NULL;
   
  	 }
	 else{                      /*Case 3: More than one element in queue*/
 	 data=front->data;
 	 struct Queue* ptr=front;
 	 front=front->v_next;
 	 free(ptr);
 	 }
  return data;
 }
 
 /*A function to find Vertex node using vertex number */
 struct VList* find(struct VList* start, int src){
  	struct VList* ptr=start;
 	 while(ptr!=NULL){
 		  if(ptr->src==src)
    			 return ptr;
 		 ptr=ptr->v_next;
 	 }
 return ptr;      /*return NULL*/
 }
 
 /*Print Graph in Adjacency list Representation*/
 void printGraph(struct VList* start){
  	struct VList *ptr=start;
 	 while(ptr!=NULL){
   		printf("%d",ptr->src);
   		struct EList *tmp=ptr->e_next;
  		 while(tmp!=NULL){
  		 	printf("--->%d(%d)", tmp->dest, tmp->weight);
   			tmp=tmp->e_next;
  			}
 		 printf("\n");
  		 ptr=ptr->v_next;
 		 }
 }
 
 
 /*Function to read Vertices and Edges from file. (i.e. Nodes.txt  Edges.txt)*/
 struct VList* ReadFile(){
	 struct VList* start, *V;
	 start=V=NULL;
 	 int tmp;
	 FILE* file=fopen("Nodes.txt","r");  /*Reading Nodes.txt file*/
	 if(file==NULL){                     
		 printf("Error in file open:\n");
		 exit(0);
  		}
 
	  while((fscanf(file, "%d", &tmp))!=EOF){ /*Reading file untill all data read*/
   	 	 struct VList *ptr=create_VList(tmp); 
    		 if(start==NULL){
     			 V=start=ptr;
     		 }
     		 else{
     			 V->v_next=ptr;
     			 V=V->v_next;
    		     }
  	 }
   

	 file=fopen("Edges.txt","r");   /*Reading file for Edges*/
	 if(file==NULL){
 		 printf("Error in file open:\n");
 	 exit(0);
 	 }
 	 int s,d,w,t;
	  while((fscanf(file, "%d  %d  %d ", &s,&d,&w)) != EOF){
 		 struct VList *tmp=find(start,s);
 		 struct EList *ptr=create_EList(d,w);
  		 if(tmp->e_next==NULL)
  			 tmp->e_next=ptr;
  		 else{
  			  struct EList* var=tmp->e_next;
   			  while(var->e_next!=NULL)
     				  var=var->e_next;
   			  var->e_next=ptr;
  		   }  
 		 }
	  fclose(file);
   
  return start;
 }
 
 
 /*A function to implement Breath first search algorithm */
 void BFS(struct VList* start, int n){
 	 struct VList* ptr,*var;
	 struct EList* tmp;
 	 ptr=find(start,n);                    /*Searching Entered node of number n*/
 	 if(ptr==NULL){
   		 printf("No Vertex number:%d  exist in Graph.\n",n);
    		exit(1);
   	 }
  	printf("%d ", ptr->src);              
  	ptr->visited=true;                   /*node is mark as visited*/
   	Enqueue(ptr->src);                  /*Inserting Node in Queue*/
  
  
  	while(!(isEmpty())){                /*check for all vertex untill queue empty*/
  	int k=Dequeue();                   /*Removing node number and*/
   	ptr=find(start,k);                 /*searching in Vertex */
    	tmp=ptr->e_next;
   	while(tmp!=NULL){                 /*Exploring all Adjacent Vertices*/
    
     var=find(start, tmp->dest);
     if(!(var->visited)){               /*if Vertices are not visited insert them in queue*/
        var->visited=true;              /*Adding all Edges weight*/
        total_weight=total_weight+tmp->weight;
        printf("--->%d(%d)", tmp->dest,tmp->weight);
        Enqueue(tmp->dest);
       }
      tmp=tmp->e_next;
     }
    }
    printf("\n");
  }
  
 /*A function for disjoint Graph*/ 
 void DisJoint(struct VList* start){
	 struct VList* ptr=start;
	 while(ptr!=NULL){
 	 if(!ptr->visited){
   		 BFS(start, ptr->src);
   		 }
 	 ptr=ptr->v_next;
 	 }
  }
 
 /*Main function*/
 int main(){
	 struct VList* start;
	 rear=front=NULL;
	 int n;
	 start=ReadFile();
 	 printf("Adjacency List Representation of Graph:\n");
	 printGraph(start);             /*Printng Graph*/
	 printf("Enter Node where to start BFS: ");
  	 scanf("%d",&n);
	 printf("\n******Order of Visiting Nodes*****\n");
 	 BFS(start, n);                 /*Calling  BFS function*/
	 DisJoint(start);               /*Exploring unvisited for DisJoint Graph*/
	 printf("/******************/\n");
	 printf("\nSum of edges in BFT: %d\n\n",total_weight);
 return 0;
 }