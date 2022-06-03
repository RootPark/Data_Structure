#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct{
	int Capacity;
	int Size;
	int *Element;
}Heap;

Heap* CreateHeap(int heapSize){
	Heap* H=(Heap*)malloc(sizeof(Heap));
	H->Capacity=heapSize;
	H->Size=0;
	H->Element=(int*)malloc(sizeof(int)*(heapSize+1));
	return H;
}

int Find(Heap *heap, int value){
	for(int i=1;heap->Size>=i;i++){
		if(heap->Element[i]==value){
			return 1;
		}
	}
	return 0;
}

void Insert(Heap *heap, int value){
	int i;
	if(heap->Capacity==heap->Size){
		printf("Insertion Error : Max Heap is full.\n");
		return;
	}
	else{
		if(Find(heap, value)){
			printf("%d is already in the heap.\n",value);
			return;
		}
		else{
			i=++(heap->Size);
			heap->Element[heap->Size]=value;
			while((i>=2)&&(value>heap->Element[i/2])){
				int tmp=heap->Element[i];
				heap->Element[i]=heap->Element[i/2];
				heap->Element[i/2]=tmp;
				i/=2;
			}
		}
		printf("insert %d\n",value);
	}
}

int DeleteMax(Heap* heap){
	int i=1,child=2;
	int max, last;
	
	if(heap->Size==0){
		printf("Delection Error : Max heap is empty!\n");
	}
	else{
		max=heap->Element[1];
		last=heap->Element[heap->Size--];
		while(child<=heap->Size){
			if(child<heap->Size&&heap->Element[child]<heap->Element[child+1]){
				child++;
			}
			if(last>=heap->Element[child]){
				break;
			}
			heap->Element[i]=heap->Element[child];
			i=child;
			child*=2;
		}
		printf("Max Element: %d deleted\n",max);
		heap->Element[i]=last;
		return max;
		}
}

void PrintHeap(Heap* heap){
	if(heap->Size==0){
		printf("Print Error : Max Heap is empty!");
	}
	else{
		for(int i=1; i<=heap->Size; i++){
			printf("%d ",heap->Element[i]);
		}
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	FILE *fi=fopen(argv[1],"r");
	char cv;
	Heap* maxHeap;
	int heapSize, key;
	while(!feof(fi)){
		fscanf(fi,"%c",&cv);
		if(feof(fi)) break;
		switch(cv){
			case 'n':
				fscanf(fi,"%d",&heapSize);
				maxHeap=CreateHeap(heapSize);
				break;
			case 'i':
				fscanf(fi,"%d",&key);
				Insert(maxHeap,key);
				break;
			case 'd':
				DeleteMax(maxHeap);
				break;
			case 'p':
				PrintHeap(maxHeap);
				break;
			case 'f':
				fscanf(fi,"%d",&key);
				if(Find(maxHeap,key)){
					printf("%d is in the heap.\n",key);
				}
				else{
					printf("%d is not in the heap.\n",key);
				}
				break;
		}
	}
}

