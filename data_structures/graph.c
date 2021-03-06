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

void disposeList(struct GraphNode* head){
    struct GraphNode *tmp;
    if(head==NULL)
    return ;
    tmp=head;
    disposeList(head->next);
    free(tmp);
}

void disposeGraph(Graph g){
    int n=g->numOfVertex;
    int i;
    for(i=0;i<n;i++)
    disposeList(g->adjLists[i]);
    free(g->adjLists);
    free(g);
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
disposeGraph(g);
return 0;
}
