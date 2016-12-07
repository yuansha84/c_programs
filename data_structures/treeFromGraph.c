#include <stdio.h>
#include <stdlib.h>

struct GraphNode{
    int vertex;
    struct GraphNode *next;
};
struct GraphRec{
    struct GraphNode **adjLists;
    int numOfVertex;
};
typedef struct GraphRec *Graph;
void graphAdjAdd(struct GraphNode **lst,int ele){
    struct GraphNode *newCell=(struct GraphNode*)malloc(sizeof(struct GraphNode));
    newCell->vertex=ele;
    newCell->next=NULL;
    if(*lst==NULL)
    *lst=newCell;
    else{
        newCell->next=(*lst);
        *lst=newCell;
    }
}

Graph createGraph(int n,int** edges,int edgeNum){
    int i;
    int *edge;
    //struct GraphNode *newCell;
    Graph g=(struct GraphRec*)malloc(sizeof(struct GraphRec));
    g->numOfVertex=n;
    g->adjLists=(struct GraphNode**)malloc(sizeof(struct GraphNode*)*n);
    for(i=0;i<n;i++)
    g->adjLists[i]=NULL;
    for(i=0;i<edgeNum;i++){
        edge=edges[i];
        graphAdjAdd(&(g->adjLists[edge[0]]),edge[1]);
        graphAdjAdd(&(g->adjLists[edge[1]]),edge[0]);
        
    }
    return g;
}

void printLst(struct GraphNode *lst){
while(lst!=NULL){
printf("%d ",lst->vertex);
lst=lst->next;
}
putchar('\n');
}

void printGraph(Graph g){
int n=g->numOfVertex;
int i;
struct GraphNode *lst;
for(i=0;i<n;i++){
printf("%d:",i);
printLst(g->adjLists[i]);
}
}

struct TreeNode{
    int nnum;
    int height;
    struct TreeNode* ch_height[3];
    //int rooted_height;
    int chh[3];
    struct TreeNode *firstChild;
    struct TreeNode *nextSib;
    //struct TreeNode *parent;
};
typedef struct TreeNode *Tree;

struct queueNode{
struct TreeNode* ele;
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

void enqueue(Queue q,struct TreeNode* ele){
struct queueNode *newCell=(struct queueNode*)malloc(sizeof(struct queueNode));
newCell->ele=ele;
newCell->next=NULL;
q->rear->next=newCell;
q->rear=newCell;
}

struct TreeNode* dequeue(Queue q){
struct queueNode *pt;
struct TreeNode* val;
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

Tree createTree(Graph g){
    int n,i,adjn;
    struct TreeNode* node,*curChild,*newNode;
    struct GraphNode *adjl;
    n=g->numOfVertex;
    int *visited=(int*)malloc(sizeof(int)*n);
    //Tree root=NULL;
    for(i=0;i<n;i++)
    visited[i]=0;
    Tree root=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->nnum=0;
    root->firstChild=root->nextSib=NULL;
    for(i=0;i<3;i++){
    root->ch_height[i]=NULL;
    root->chh[i]=-1;
    }
    visited[0]=1;
    Queue q=createQueue();
    enqueue(q,root);
    while(!isEmpty(q)){
        node=dequeue(q);
        curChild=NULL;
        adjl=g->adjLists[node->nnum];
        for(;adjl!=NULL;adjl=adjl->next){
            adjn=adjl->vertex;
            if(!visited[adjn]){
                newNode=(struct TreeNode *)malloc(sizeof(struct TreeNode));
                newNode->nnum=adjn;
                newNode->firstChild=newNode->nextSib=NULL;
                for(i=0;i<3;i++){
                    newNode->ch_height[i]=NULL;
		    newNode->chh[i]=-1;
                }
                if(curChild==NULL){
                    node->firstChild=newNode;
                    curChild=newNode;
                }else{
                    curChild->nextSib=newNode;
                    curChild=newNode;
                }
		visited[adjn]=1;
                enqueue(q,newNode);
            }
        }
    }
    return root;
}

void disposeTree(Tree T){
    struct TreeNode *child,*tmp;
    if(T==NULL)
    return;
    for(child=T->firstChild;child!=NULL;child=tmp){
    tmp=child->nextSib;
    disposeTree(child);
    }
    free(T);
}

void printNodeInfo(struct TreeNode *node){
printf("%d: height(%d) maxChildren(",node->nnum,node->height);
int i;
for(i=0;node->ch_height[i]!=NULL;i++)
printf("%d %d ",node->ch_height[i]->nnum,node->chh[i]);
printf(")\n");
}

void printPreorder(Tree t){
struct TreeNode *node,*child;
if(t==NULL)
return ;
printNodeInfo(t);
for(child=t->firstChild;child!=NULL;child=child->nextSib)
printPreorder(child);
}

void printPostorder(Tree t){
struct TreeNode *node,*child;
if(t==NULL)
return ;
for(child=t->firstChild;child!=NULL;child=child->nextSib)
printPostorder(child);
printf("%d ",t->nnum);
}

void postSet(Tree T){
    struct TreeNode *node;
    int i,chSize,curH;
    if(T->firstChild==NULL)// a leaf
    T->height=0;
    else{
        chSize=0;
        for(node=T->firstChild;node!=NULL;node=node->nextSib){
        postSet(node);
        if(chSize==0){
        T->ch_height[chSize]=node;
        T->chh[chSize]=node->height;
	chSize++;
	}
        else if(chSize==1){
            curH=node->height;
            if(curH>T->ch_height[0]->height){
                T->ch_height[1]=T->ch_height[0];
		T->chh[1]=T->chh[0];
                T->ch_height[0]=node;
		T->chh[0]=curH;
            }else {
		T->ch_height[1]=node;
		T->chh[1]=curH;}
            chSize++;
        }
        else{
            curH=node->height;
            for(i=1;i>=0&&curH>T->ch_height[i]->height;i--){
            T->ch_height[i+1]=T->ch_height[i];
	    T->chh[i+1]=T->chh[i];}
            T->ch_height[i+1]=node;
	    T->chh[i+1]=curH;
            T->ch_height[2]=NULL;
     	    T->chh[2]=-1;
        }
        }
        T->height=T->ch_height[0]->height+1;
    }
	//printNodeInfo(T);
}

int main(int argc,char **argv){
if(argc<2){
printf("usage: ./main filename\n");
exit(-1);
}
char *file=argv[1];
int i,j,n;
int **edges;
FILE *fp=fopen(file,"r");
if(fp==NULL){
printf("file cannot open\n");
exit(-1);
}
fscanf(fp,"%d",&n);
edges=(int**)malloc(sizeof(int*)*(n-1));

for(i=0;i<n-1;i++){
edges[i]=(int*)malloc(sizeof(int)*2);
fscanf(fp,"%d,%d",&edges[i][0],&edges[i][1]);
}
fclose(fp);
Graph g=createGraph(n,edges,n-1);
printGraph(g);
//printLst(g->adjLists[0]);
Tree t=createTree(g);
postSet(t);
printPreorder(t);
putchar('\n');
printPostorder(t);
putchar('\n');
return 0;
}

