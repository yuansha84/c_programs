#include <stdio.h>
#include <stdlib.h>

struct queueNode{
int ele;
struct queueNode *next;
};

struct queueRec{
struct queueNode* head;
struct queueNode* rear;
};

typedef struct queueRec *Queue;

Queue createQueue(){
Queue q=(struct queueRec*)malloc(sizeof(struct queueRec));
struct queueNode *header=(struct queueNode*)malloc(sizeof(struct queueNode));
header->next=NULL;
q->head=header;
q->rear=header;
return q;
}

int isEmpty(Queue q){
return q->head==q->rear;
}

void enqueue(Queue q,int ele){
struct queueNode *newCell=(struct queueNode*)malloc(sizeof(struct queueNode));
newCell->ele=ele;
newCell->next=NULL;
q->rear->next=newCell;
q->rear=newCell;
}

int dequeue(Queue q){
struct queueNode *pt;
int val;
if(isEmpty(q)){
printf("Queue is empty!\n");
exit(-1);
}
pt=q->head->next;
q->head->next=pt->next;
if(q->rear==pt)
q->rear=q->head;
val=pt->ele;
free(pt);
return val;
}

void disposeQueue(Queue q){
while(!isEmpty(q))
dequeue(q);
free(q->head);
free(q);
}

void printQueue(Queue q){
struct queueNode *pt;
for(pt=q->head->next;pt!=NULL;pt=pt->next)
printf("%d ",pt->ele);
putchar('\n');
}

int main(){
Queue q=createQueue();
int i;
for(i=1;i<80;i++)
enqueue(q,i);
enqueue(q,1);
enqueue(q,2);
enqueue(q,3);
enqueue(q,4);
enqueue(q,5);
dequeue(q);
printQueue(q);
disposeQueue(q);
return 0;
}

