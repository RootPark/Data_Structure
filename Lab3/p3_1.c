#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node{
	ElementType element;
	Position next;
};
void Delete(ElementType X,List L){
	
}
Position Find(ElementType X, List L){
	
}
Position FindPrevious(ElementType X, List L){
	
}
void DeleteList(List L){
	
}
List MakeEmpty(List L){
	L=(List)malloc(sizeof(struct Node));
	L->next=NULL;
	return L;
}
int IsEmpty(List L){
	return L->next==NULL;
}
int IsLast(Position P, List L){
	return P->next==NULL;
}
void Insert(ElementType X, List L, Position P){
	if(P==NULL){
		printf("Insertion(%d) Failed : cannot find the location to be inserted",X);
	}
	else{
		Position tmp=malloc(sizeof(struct Node));
		tmp->element=X;
		tmp->next=P->next;
		P->next=tmp;
	}
}
void PrintList(List L){
	while(L->next!=NULL){
		L=L->next;
		printf("key:%d\n",L->element);
	}
}
int main(int argc, char *argv[]) {
	char command;
	int key1, key2;
	FILE *input;
	Position header;
	Position tmp;
	if(argc ==1){
		printf("No input file\n");
		return 0;
	}
	else{
		input= fopen(argv[1], "r");
	}
	header=MakeEmpty(header);
	while(1){
		command= fgetc(input);
		if(feof(input))break;
		switch(command){
			case 'i':
				fscanf(input, "%d %d",&key1,&key2);
				// tmp = Find(key2, header);
				// Insert(key1,header,tmp);
				Insert(key1,header,header);
				break;
			case 'd':
				fscanf(input, "%d",&key1);
				Delete(key1,header);
				break;
			case 'f':
				fscanf(input, "%d",&key1);
				tmp=FindPrevious(key1,header);
				if(IsLast(tmp,header)){
					printf("Could not find %d in the list\n",key1);
				}
				else{
					if(tmp->element>0){
						printf("Key of the previous node of %d is %d.\n",key1,tmp->element);
					}
					else{
						printf("Key of the previous node of %d is header.\n",key1);
					}
				}
				break;
			case 'p':
				PrintList(header);
				break;
			default:
				break;
		}
	}
	DeleteList(header); //free all memory used by linked list
	fclose(input);
	return 0;
}
