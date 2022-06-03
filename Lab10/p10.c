#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
		int vertex;
		int dist;
		int prev;
}Node;

typedef struct Graph {
	int size;
	int** vertices;
	Node* nodes;
}Graph;

typedef struct Heap {
	int Capacity;
	int Size;
	Node* Element;
}Heap;

Graph CreateGraph(int size);
void printShortestPath(Graph g);
Heap* createMinHeap(int heapSize);
void insertToMinHeap(Heap *minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);
void printpath(int i, Graph g);

int main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	
	if(fi == NULL) {
		printf("There is not file : %s\n", argv[1]);
		return 0;
	}
	
	Graph g;
	
	int size;
	fscanf(fi, "%d\n", &size);
	g = CreateGraph(size+1);
	char temp = 0;
	while(temp != '\n')
	{
		int node1, node2, weight;
		fscanf(fi, "%d-%d-%d", &node1, &node2, &weight);
		g.vertices[node1][node2] = weight;
		temp = fgetc(fi);
	}
	printShortestPath(g);
	
	for(int i=0; i<=size; i++)
		free(g.vertices[i]);
	free(g.vertices);
	free(g.nodes);
}

Graph CreateGraph(int size) {
	Graph g;
	g.size = size-1;
	
	g.vertices = (int**)malloc(sizeof(int*)*size);
	for(int i=0; i<size; i++)
		g.vertices[i] = (int*)malloc(sizeof(int)*size);
	
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			g.vertices[i][j] = 0;
	
	g.nodes = (Node*)malloc(sizeof(struct Node)*size);
	
	for(int i=1; i<size; i++) {
		g.nodes[i].vertex = i;
		g.nodes[i].dist = 9999999;
		g.nodes[i].prev = 0;
	}
	g.nodes[1].dist = 0;
	
	return g;
}

void printShortestPath(Graph g) {
	Heap* h = createMinHeap(g.size);
	
	insertToMinHeap(h, 1, 0);
	
	while(h->Size != 0) {
		Node minNode = deleteMin(h);
		int a = minNode.vertex;
		for(int i=1; i<=g.size; i++) {
			if(g.vertices[a][i] != 0) {
				int d = g.nodes[a].dist + g.vertices[a][i];
				if(g.nodes[i].dist > d) {
					g.nodes[i].dist = d;
					g.nodes[i].prev = a;
					insertToMinHeap(h, i, d);
				}
			}
		}
	}
	
	for(int i=2; i<=g.size; i++) {
		if(g.nodes[i].dist >= 99999999) {
			printf("Cannot reach to node %d.\n", i);
			continue;
		}
		
		printpath(i, g);
		printf(" (cost: %d)\n", g.nodes[i].dist);
	}
}

void printpath(int i, Graph g) {
	if(g.nodes[i].prev != 0) {
		printpath(g.nodes[i].prev, g);
		printf("->%d", i);
	}
	else
		printf("%d", i);
}

Heap* createMinHeap(int heapSize) {
	Heap* h = malloc(sizeof(struct Heap));
	h->Size = 0;
	h->Element = malloc(sizeof(struct Node)*(heapSize+1));
	h->Capacity = heapSize;
	
	return h;
}

void insertToMinHeap(Heap *minHeap, int vertex, int distance) {
	if(minHeap->Size == 0) {
		minHeap->Element[++minHeap->Size].vertex = vertex;
		minHeap->Element[minHeap->Size].dist = distance;
		minHeap->Element[minHeap->Size].prev = 0;
	}
	else {
		int i, count = 1;
		for(i=1; i<=minHeap->Size; i++) {
			if(minHeap->Element[i].vertex == vertex) {
				minHeap->Element[i].dist = distance;
				count = 0;
				break;
			}
		}
		
		if(count == 0) {
			for(int j=i; minHeap->Element[j/2].dist < distance && j>=2; j/=2) {
				Node tmp = minHeap->Element[j];
				minHeap->Element[j] = minHeap->Element[j/2];
				minHeap->Element[j/2] = tmp;
			}
			return ;
		}
		
		else if(count == 1) {
			minHeap->Element[++minHeap->Size].vertex = vertex;
			minHeap->Element[minHeap->Size].dist = distance;
			minHeap->Element[minHeap->Size].prev = 0;
		}
		
		for(i = minHeap->Size; minHeap->Element[i/2].dist < distance && i>=2; i/=2) {
			Node tmp = minHeap->Element[i];
			minHeap->Element[i] = minHeap->Element[i/2];
			minHeap->Element[i/2] = tmp;
		}
	}
}

Node deleteMin(Heap* minHeap) {
	int i, Child;
	Node Min = minHeap->Element[1];
	minHeap->Element[1] = minHeap->Element[minHeap->Size--];
	
	for(int i=1; i*2<=minHeap->Size; i=Child) {
		Child = i*2;
		if(Child != minHeap->Size && minHeap->Element[Child+1].dist < minHeap->Element[Child].dist)
			Child++;
		
		if(minHeap->Element[i].dist > minHeap->Element[Child].dist) {
			Node tmp = minHeap->Element[i];
			minHeap->Element[i] = minHeap->Element[Child];
			minHeap->Element[Child] = tmp;
		}
		
		else
			break;
	}
	
	return Min;
}