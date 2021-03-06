#include <stdio.h>
#include <stdlib.h>

//the binary heap data structure
struct heapRec{
  int *elements;
  int capacity;
  int size;
};
typedef struct heapRec * Heap;
Heap createHeap(int capa){
  Heap h=(struct heapRec*)malloc(sizeof(struct heapRec));
  h->capacity=capa;
  h->elements=(int*)malloc(sizeof(int)*(capa+1));
  h->size=0;
  return h;
}

int isFull(Heap h){
  return h->size==h->capacity;
}

int isEmpty(Heap h){
  return h->size==0;
}

void push(Heap h,int ele){
  int curp,par;
  if(isFull(h)){
    printf("Heap is Full,cannot push!\n");
    return ;
  }
  curp=h->size+1;
  for(par=curp/2;par>0&&h->elements[par]>ele;){
    h->elements[curp]=h->elements[par];
    curp=par;
    par=curp/2;
  }
  h->elements[curp]=ele;
  h->size+=1;
}

int pop(Heap h){
  int val,reval;
  int curp,lchild;
  int lval,small;
  if(isEmpty(h)){
    printf("Heap is empty,cannot pop!\n");
    return -1;
  }
  reval=h->elements[1];
  val=h->elements[h->size];
  h->size-=1;
  if(h->size==0)
    return reval;
  curp=1;
  for(lchild=curp*2;lchild<=h->size;){
    lval=h->elements[lchild];
    small=lchild;
    if(lchild+1<=h->size&&h->elements[lchild+1]<h->elements[lchild]){//has a right child
      lval=h->elements[lchild+1];
      small=lchild+1;
    }
    if(lval<val){
      h->elements[curp]=lval;
      curp=small;
      lchild=curp*2;
    }else break;
  }
  h->elements[curp]=val;
  return reval;
}

//test 
int main(){
  int i;
  Heap h=createHeap(1000);
  srand(1);
  for(i=0;i<1000;i++)
  push(h,rand());
  /*for(i=1;i<=h->size;i++)
    printf("%d ",h->elements[i]);
  putchar('\n');*/
  while(!isEmpty(h))
    printf("%d ",pop(h));
  putchar('\n');
  for(i=100;i>=0;i-=2)
    push(h,i);
  while(!isEmpty(h))
    printf("%d ",pop(h));
  return 0;
}
