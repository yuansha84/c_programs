#include <stdio.h>
#include <stdlib.h>
#include "graph.c"

//topological sort
int topoSort(Graph g,int *order){
int i,n,count;
int *visited,*indegrees;
struct GraphNode *node,*lst;
n=g->numOfVertex;
visited=(int*)malloc(sizeof(int)*n);
indegrees=(int*)malloc(sizeof(int)*n);
for(i=0;i<n;i++){
visited[i]=0;
indegrees[i]=0;
}
for(i=0;i<n;i++){
lst=g->adjLists[i];
while(lst!=NULL){
indegrees[lst->vertex]++;
lst=lst->next;
}
}
count=n;
while(1){
for(i=0;i<n;i++)
if(visited[i]==0&&indegrees[i]==0){
visited[i]=1;
lst=g->adjLists[i];
while(lst!=NULL){
indegrees[lst->vertex]--;
lst=lst->next;
}
count--;
if(count==0)
return 1;
break;
}
if(i==n)
return 0;
}
}

int main(int argc,char **argv){
if(argc<2){
printf("usage: ./main filename\n");
exit(-1);
}
char *file=argv[1];
int i,m,n;
int **edges;
FILE *fp=fopen(file,"r");
if(fp==NULL){
printf("file cannot open\n");
exit(-1);
}
fscanf(fp,"%d",&n);
fscanf(fp,"%d",&m);
edges=(int**)malloc(sizeof(int*)*m);

for(i=0;i<m;i++){
edges[i]=(int*)malloc(sizeof(int)*2);
fscanf(fp,"%d,%d",&edges[i][1],&edges[i][0]);
}
fclose(fp);
Graph g=createGraph(n,edges,m);
printGraph(g);
if(topoSort(g,NULL))
printf("Possible\n");
else printf("Impossible\n");
return 0;
}
