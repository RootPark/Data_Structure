#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node
{
	int vertex;
	int dist; //distance
	int prev;
}Node;

typedef struct Graph
{
	int size;
	int** vertices;
	Node* nodes;
}Graph;

typedef struct Heap
{
	int Capacity;
	int Size;
	Node* Element;
}Heap;

Graph CreateGraph(int size);
void printShortestPath(Graph g);
Heap* createMinHeap(int heapSize);
void insertToMinHeap(Heap* minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);
int Find(Heap *heap, int value);

Graph CreateGraph(int size)
{
	int i = 0;
	Graph* g = malloc(sizeof(struct Graph));
	g->size = size;
	
	g->nodes = (Node*)malloc(sizeof(Node) * g->size);
	g->nodes[1].vertex = 1;
	g->nodes[1].dist = 0;
	for ( i = 2; i < size; i++ )
	{
		g->nodes[i].vertex = i;
		g->nodes[i].dist = 9999;
	}
	
	//matrix malloc
	g->vertices = (int**)malloc(sizeof(int*) * size);
	
	int length;
	for ( length = 0; length < size; length++ )
	{
		g->vertices[length] = (int*)malloc(sizeof(int) * size);
	}
	
	//matirx reset
	int col1, low1;
	for ( low1 = 0; low1 < size; low1++ )
	{
		for ( col1 = 0; col1 < size; col1++ )
		{
			if ( low1 == 0 ) g->vertices[0][col1 + 1] = g->nodes[col1].vertex;
			else if ( col1 == 0 ) g->vertices[low1][0] = g->nodes[low1 - 1].vertex;
			else g->vertices[low1][col1] = -1;
		}
	}
	
	return *g;
}

Heap* createMinHeap(int heapSize)
{
	Heap* newHeap;
	
	newHeap = malloc(sizeof(struct Heap));
	if ( newHeap == NULL )
	{
		printf("Out of space!!");
	}
	
	newHeap->Element = (Node*)malloc(sizeof(Node) * ( heapSize + 1 ));
	
	if ( newHeap->Element == NULL )
		printf("Out of space!!");
	
	newHeap->Capacity = heapSize;
	newHeap->Size = 0;
	
	return newHeap;
}

int Find(Heap *heap, int value)
{
	int i, result = 0;
	
	if ( heap == NULL )
		return -1;
	else
	{
		for ( i = 1; i < heap->Capacity; i++ )
		{
			if ( value == heap->Element[i].vertex )
			{
				result = 1;
				break;
			}
		}
		return result;
	}
}
void insertToMinHeap(Heap* minHeap, int vertex, int distance)
{
	int i;
	if ( minHeap->Size == minHeap->Capacity )
	{
		printf("Insertion Error : Min heap is full.\n");
		return;
	}
	
	if ( Find(minHeap, vertex) )
	{
		printf("%d is already in the tree\n", vertex);
		return;
	}
	
	for ( i = ++minHeap->Size; i > 1 && minHeap->Element[i / 2].dist > distance; i /= 2 )
		minHeap->Element[i] = minHeap->Element[i / 2];
	
	minHeap->Element[i].vertex = vertex;
	minHeap->Element[i].dist = distance;
}

Node deleteMin(Heap* minHeap)
{
	int i, Child;
	Node minElement, LastElement;
	
	if ( minHeap->Size == 0 )
		printf("Deletion Error : Min heap is empty!\n");
	else
	{
		minElement = minHeap->Element[1];
		LastElement = minHeap->Element[minHeap->Size--];
		
		for ( i = 1; i * 2 <= minHeap->Size; i = Child )
		{
			Child = i * 2;
			if ( Child != minHeap->Size && minHeap->Element[Child + 1].vertex < minHeap->Element[Child].vertex )
				Child++;
			
			if ( LastElement.vertex > minHeap->Element[Child].vertex )
				minHeap->Element[i] = minHeap->Element[Child];
			else
				break;
		}
		
		minHeap->Element[i] = LastElement;
		return minElement;
	}
}
void DeleteHeap(Heap* heap)
{
	free(heap->Element);
	free(heap);
}
void printShortestPath(Graph g)
{
	int gSize = g.size - 1;
	Heap* h = createMinHeap(gSize);
	Node* circle = (Node*)malloc(sizeof(struct Node) * gSize);
	int num = 0;
	
	int col;
	for ( col = 1; col <= gSize; col++ )
	{
		if ( g.vertices[1][col] != -1)
		{
			g.nodes[col].dist = g.vertices[1][col];
			g.nodes[col].prev = 1;
		}
	}
	
	//add each vertex to priority queue Q
	int index;
	for ( index = 1; index <= gSize; index++ )
	{
		insertToMinHeap(h, index, g.nodes[index].dist);
	}
	
	while ( h->Size != 0 )
	{
		Node n;
		n = deleteMin(h);
		circle[num++] = n;
		
		int i;
		for ( i = 1; i <= gSize; i++ )
		{
			if ( g.vertices[n.vertex][i] != -1 )
			{
				if ( g.nodes[n.vertex].dist + g.vertices[n.vertex][i] < g.nodes[i].dist )
				{
					g.nodes[i].dist = g.nodes[n.vertex].dist + g.vertices[n.vertex][i];
					g.nodes[i].prev = n.vertex;
				}
			}
		}
	}
	
	//print
	int startTo, cost = 0, order;
	for ( order = 2; order <= gSize; order++ )
	{
		int* path = (int*)malloc(sizeof(int) * gSize);
		int numberOfNode = 0;
		startTo = order;
		while ( g.nodes[startTo].vertex != 1 )
		{
			path[numberOfNode] = g.nodes[startTo].vertex;
			startTo = g.nodes[startTo].prev;
			numberOfNode++;
		}
		
		printf("%d->", 1);
		while ( numberOfNode > 0 )
		{
			if ( numberOfNode - 1 == 0 )
				printf("%d", path[--numberOfNode]);
			else
				printf("%d->", path[--numberOfNode]);
		}
		printf(" (cost : %d)\n", g.nodes[order].dist);
		free(path);
	}
	
	//free
	free(circle);
	DeleteHeap(h);
}

int main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	Graph g;
	
	int size;
	fscanf(fi, "%d\n", &size);
	g = CreateGraph(size + 1);
	char temp = 0;
	
	while ( !feof(fi) )
	{
		int node1, node2, weight;
		fscanf(fi, "%d-%d-%d", &node1, &node2, &weight);
		g.vertices[node1][node2] = weight;
		temp = fgetc(fi);
	}
	
	printShortestPath(g);
}
