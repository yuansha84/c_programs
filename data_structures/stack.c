//this is an array implementation of the stack ADT
#include <stdio.h>
#include "stack.h"
struct stackRec{
char elements[1000];
int top;
};
//typedef struct stackRec *Stack;
Stack createStack(){
Stack s=(Stack)malloc(sizeof(struct stackRec));
s->top=0;
return s;
}

int isEmpty(Stack s){
return s->top==0;
}

void push(Stack s,char ch){
if(s->top==1000){
printf("Stack is Full!\n");
exit(-1);
}
s->elements[s->top++]=ch;
}

char pop(Stack s){
if(!isEmpty(s)){
s->top--;
return s->elements[s->top];
}else return '\0';
}

char top(Stack s){
if(!isEmpty(s))
return s->elements[s->top-1];
else return '\0';
}

//use for test
void printStack(Stack s){
int i;
for(i=0;i<s->top;i++)
printf("%c ",s->elements[i]);
putchar('\n');
}








