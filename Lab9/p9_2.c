#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue
{
	int* key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};

struct _Graph
{
	int size;
	int* node;
	int** matrix;
};

Graph CreateGraph(int* nodes);
void InsertEdge(Graph G, int a, int b);
void DeleteGraph(Graph G);

void Topsort(Graph G);
Queue MakeNewQueue(int X);
int IsEmpty(Queue Q);
int IsFull(Queue Q);
int Dequeue(Queue Q);
void Enqueue(Queue Q, int X);
void DeleteQueue(Queue Q);
void MakeEmpty(Queue Q);

int n = 0;

int main(int argc, char *argv[]) {
	int i = 0;
	int* int_node;
	char input_node[100];
	char* token;
	Graph G = NULL;
	
	FILE *fi = fopen(argv[1], "r");
	
	if(fi == NULL) {
		printf("There is no file : %s\n", argv[1]);
		return 0;
	}
	
	fgets(input_node, 100, fi);
	int_node = (int*)malloc(sizeof(int)*strlen(input_node));
	token = strtok(input_node, " ");
	
	while(token != NULL) {
		int_node[i++] = atoi(token);
		token = strtok(NULL, " ");
	}
	
	n = i;
	G = CreateGraph(int_node);
	
	while(!feof(fi)) {
		fscanf(fi, "%s", input_node);
		
		token = strtok(input_node, "-");
		if(token == NULL) break;
		int a = atoi(token);
		
		token = strtok(NULL, " ");
		if(token == NULL) break;
		int b = atoi(token);
		
		InsertEdge(G, a, b);
	}
	
	Topsort(G);
	
	free(int_node);
	DeleteGraph(G);
}

Graph CreateGraph(int* nodes) {
	Graph G = (Graph)malloc(sizeof(struct _Graph));
	G->size = n;
	G->node = (int*)malloc(sizeof(int)*n);
	G->matrix = (int**)malloc(sizeof(int*)*n);
	
	for(int i=0; i<G->size; i++) {
		G->matrix[i] = (int*)malloc(sizeof(int)*n);
	}
	
	for(int i=0; i<G->size; i++) {
		G->node[i] = nodes[i];
	}
	
	for(int i=0; i<G->size; i++) {
		for(int j=i+1; j<G->size; j++) {
			if(G->node[i] > G->node[j]) {
				int temp = G->node[j];
				G->node[j] = G->node[i];
				G->node[i] = temp;
			}
		}
	}
	
	for(int i=0; i<G->size; i++) {
		for(int j=0; j<G->size; j++) {
			G->matrix[i][j] = 0;
		}
	}
	
	return G;
}

void InsertEdge(Graph G, int a, int b) {
	int acnt = 0, bcnt = 0;
	
	for(int i=0; i<G->size; i++) {
		if(G->node[i] == a) break;
		else {
			acnt++;
		}
	}
	
	for(int i=0; i<G->size; i++) {
		if(G->node[i] == b) break;
		else {
			bcnt++;
		}
	}
	
	G->matrix[acnt][bcnt] = 1;
}

void DeleteGraph(Graph G) {
	if(G != NULL || G->size == 0) {
		free(G->node);
		
		int n = G->size;
		
		for(int i=0; i<n; i++) {
			free(G->matrix[i]);
		}
		free(G->matrix);
		
		free(G);
	}
}

void Topsort(Graph G) {
	Queue Q = MakeNewQueue(G->size);
	int Indegree[G->size];
	
	for(int i=0; i<G->size; i++) {
		Indegree[i] = 0;
	}
	
	for(int i=0; i<G->size; i++) {
		for(int j=0; j<G->size; j++) {
			if(G->matrix[i][j]){
				Indegree[j]++;
			}
		}
	}
	
	for(int i=0; i<G->size; i++) {
		if(Indegree[i] == 0)
			Enqueue(Q, G->node[i]);
	}
	
	while(!IsEmpty(Q)) {
		int x = Dequeue(Q);
		printf("%d ", x);
		
		int xcnt = 0;
		
		for(int i=0; i<G->size; i++) {
			if(G->node[i] == x) {
				break;
			}
			else{
			xcnt++;
			}
		}
		
		for(int i=0; i<G->size; i++) {
			if(G->matrix[xcnt][i]) {
				G->matrix[xcnt][i] = 0;
				Indegree[i]--;
				
				if(Indegree[i] == 0){
					Enqueue(Q, G->node[i]);
				}
			}
		}
	}
	printf("\n");
	DeleteQueue(Q);
}

Queue MakeNewQueue(int X) {
	Queue Q = (Queue)malloc(sizeof(struct _Queue));
	Q->key = (int*)malloc(sizeof(int)*X);
	Q->first = 0;
	Q->rear = -1;
	Q->qsize = 0;
	Q->max_queue_size = X;
	
	return Q;
}

int IsEmpty(Queue Q) {
	if(Q->qsize <= 0)
		return 1;
	else
		return 0;
}

int IsFull(Queue Q) {
	if(Q->rear == Q->max_queue_size-1)
		return 1;
	return 0;
}

int Dequeue(Queue Q) {
	if(Q->first > Q->rear) {
		printf("Error : Queue is empty.\n");
		return 0;
	}
	
	Q->qsize--;
	return Q->key[Q->first++];
}

void Enqueue(Queue Q, int X) {
	if(Q->rear == Q->max_queue_size-1) {
		printf("Error : Queue is full.\n");
		return ;
	}
	
	Q->qsize++;
	Q->key[++Q->rear] = X;
}

void DeleteQueue(Queue Q) {
	if(Q != NULL) {
		free(Q->key);
		free(Q);
	}
}

void MakeEmpty(Queue Q) {
	if(Q->first != 0 || Q->rear != -1) {
		free(Q->key);
		Q->key = (int*)malloc(sizeof(int)*Q->max_queue_size);
		Q->first = 0;
		Q->rear = -1;
		Q->qsize = 0;
	}
}