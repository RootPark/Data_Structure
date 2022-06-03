#include <stdio.h>
#include <stdlib.h>

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;

struct AVLNode{
	int Element;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

AVLTree Insert(int X, AVLTree T);
void printInorder(AVLTree T);
void DeleteTree(AVLTree T);
Position SingleRotateWithLeft(Position node);
Position SIngleRotateWithRight(Position node);
int Height(Position P);
int Max(int a,int b);

int Max(int a, int b){
	return (a>b ? a : b);
}

int Height(Position P){
	if(P==NULL){
		return -1;
	}
	else{
		return P->Height;
	}
}

Position SingleRotateWithLeft(Position node){
	Position K;
	
	K=node->Left;
	
	node->Left=K->Right;
	K->Right=node;
	
	node->Height=Max(Height(node->Left),Height(node->Right))+1;
	K->Height=Max(Height(K->Left),node->Height)+1;
	
	return K;
}

Position SingleRotateWithRight(Position node){
	Position K;
	
	K=node->Right;
	
	node->Right=K->Left;
	K->Left=node;
	
	node->Height=Max(Height(node->Right),Height(node->Left))+1;
	K->Height=Max(Height(K->Right),node->Height)+1;
	
	return K;
}

/*Position DoubleRotateWithLeft(Position node){
	
}*/

/*Position DoubleRotateWithRight(Position node){
	
}*/

AVLTree Insert(int X, AVLTree T){
	if(T==NULL){
		T=malloc(sizeof(struct AVLNode));
		if(T==NULL){
			printf("Out of space!!!\n");
		}
		else{
			T->Element=X;
			T->Height=0;
			T->Left=T->Right=NULL;
		}
	}
	else if(X<T->Element){
		T->Left=Insert(X, T->Left);
		if(Height(T->Left)-Height(T->Right)==2){
			if(X<T->Left->Element){
				T=SingleRotateWithLeft(T);
			}
			/*else{
				T=DoubleRotateWithLeft(T);
			}*/
		}
	}
	else if(X>T->Element){
		T->Right=Insert(X, T->Right);
		if(Height(T->Right)-Height(T->Left)==2){
			if(X>T->Right->Element){
				T=SingleRotateWithRight(T);
			}
			/*else{
				T=DoubleRotateWithRight(T);
			}*/
		}
	}
	else{
		printf("[Error] %d is already in the tree!\n",X);
		return T;
	}
	T->Height=Max(Height(T->Left),Height(T->Right))+1;
	return T;
}

void printInorder(AVLTree T){
	if(T!=NULL){
		printInorder(T->Left);
		printf("%d(%d) ",T->Element,T->Height);
		printInorder(T->Right);
	}
}

void DeleteTree(AVLTree T){
	if(T!=NULL){
		DeleteTree(T->Left);
		DeleteTree(T->Right);
		free(T);
		}
}

int main(int argc, char **argv) {
	FILE *fp=fopen(argv[1],"r");
	AVLTree myTree =NULL;
	int num;
	
	if(fp==NULL){
		printf("There is no file : %s\n",argv[1]);
		return 0;
	}
	
	while(fscanf(fp,"%d",&num)!=EOF){
		myTree=Insert(num,myTree);
		printInorder(myTree);
		printf("\n");
	}
	
	DeleteTree(myTree);
	return 0;
}
