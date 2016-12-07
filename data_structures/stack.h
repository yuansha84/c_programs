#ifndef STACK_H
#define STACK_H
struct stackRec;
typedef struct stackRec *Stack;
Stack createStack();
int isEmpty(Stack s);
void push(Stack s,char ch);
char pop(Stack s);
char top(Stack s);
void printStack(Stack s);


#endif
