#include <stdio.h>
#include <stdlib.h>

typedef struct CompleteTree{
	int Size;
	int nodeNum;
	int* Element;
};

typedef struct CompleteTree* Tree;

Tree CreateTree(int treeSize){
	Tree new=(Tree)malloc(sizeof(Tree));
	new->Element = (int*)malloc(sizeof(int)*treeSize+1);
	new->nodeNum=0;
	new->Size=treeSize;
	return new;
}

void Insert(Tree tree, int value){
	if(tree->nodeNum < tree->Size){
		tree->nodeNum++;
		tree->Element[tree->nodeNum]=value;
	}
	else{
		printf("Error! Tree is FULL.\n");
	}
}

void printPreoerder(Tree tree, int index){
	if(index<=tree->Size){
		printf("%d ", tree->Element[index]);
		printPreoerder(tree, index*2);
		printPreoerder(tree, index*2+1);
	}
}

void printInorder(Tree tree, int index){
	if(index<=tree->Size){
		printInorder(tree, index*2);
		printf("%d ", tree->Element[index]);
		printInorder(tree, index*2+1);
	}
}



void printPostorder(Tree tree, int index){
	if(index<=tree->Size){
		printPostorder(tree, index*2);
		printPostorder(tree, index*2+1);
		printf("%d ", tree->Element[index]);

	}
}

void printTree(Tree tree){
	printf("Preorder: ");
	printPreoerder(tree, 1);
	printf("\n");
	printf("Inorder: ");
	printInorder(tree, 1);
	printf("\n");
	printf("Postorder: ");
	printPostorder(tree, 1);
	printf("\n");
}



void freeTree(Tree tree){
	if(tree){
		free(tree->Element);
		free(tree);
		
	}
}

int main(int argc, char *argv[]) {
	FILE *fi;
	Tree tree;
	int treeSize;
	int tempNum;
	
	fi=fopen(argv[1],"r");
	fscanf(fi, "%d", &treeSize);
	tree=CreateTree(treeSize);
	while(fscanf(fi,"%d",&tempNum)==1){
		Insert(tree, tempNum);
	}
	printTree(tree);
	freeTree(tree);
}