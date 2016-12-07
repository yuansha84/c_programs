#include <stdlib.h>
#include <stdio.h>

struct tNode{
int ele;
struct tNode *left;
struct tNode *right;
};
typedef struct tNode * Tree;

struct tNode *find(Tree t,int ele){
if(t==NULL)
return NULL;
if(ele<t->ele)
return find(t->left,ele);
else if(ele>t->ele)
return find(t->right,ele);
else return t;
}

Tree insert(Tree t,int ele){
struct tNode *newCell;
if(t==NULL){
newCell=(struct tNode*)malloc(sizeof(struct tNode));
newCell->ele=ele;
newCell->left=NULL;
newCell->right=NULL;
return newCell;
}
if(ele<t->ele)
t->left=insert(t->left,ele);
else if(ele>t->ele)
t->right=insert(t->right,ele);
//already present, do nothing
return t;
}

struct tNode *findMax(Tree t){//t is nonempty
struct tNode *p=t;
while(p->right!=NULL)
p=p->right;
return p;
}


Tree delete(Tree t,int ele){
struct tNode *pt;
if(t==NULL)
return NULL;
if(ele<t->ele)
t->left=delete(t->left,ele);
else if(ele>t->ele)
t->right=delete(t->right,ele);
else{
if(t->left==NULL){
pt=t;
t=t->right;
free(pt);}
else if(t->right==NULL){
pt=t;
t=t->left;
free(pt);}
else{
pt=findMax(t->left);
t->ele=pt->ele;
t->left=delete(t->left,pt->ele);
}
}
return t;
}

void printPreorder(Tree t){
if(t==NULL)
return ;
printPreorder(t->left);
printf("%d ",t->ele);
printPreorder(t->right);
}

void dispose(Tree t){
if(t==NULL)
return ;
dispose(t->left);
dispose(t->right);
free(t);
}

int main(){
Tree t=NULL;
t=insert(t,1);
t=insert(t,3);
t=insert(t,2);
t=insert(t,5);
t=insert(t,8);
t=insert(t,6);
t=insert(t,7);
t=insert(t,9);
printPreorder(t);
printf("\n");
t=delete(t,5);
t=delete(t,7);
printPreorder(t);
return 0;
}


