#include <stdio.h>
#include <stdlib.h>

typedef struct BinarySearchTree* Tree;
struct BinarySearchTree{
	int value;
	Tree left;
	Tree right;
};

Tree findNode(Tree root, int key){
	if(root==NULL){
		printf("%d is not in the tree.\n",key);
		return NULL;

	}
	if(key<root->value){
		return findNode(root->left,key);
	}
	else if(key>root->value){
		return findNode(root->right,key);
	}
	else {
		printf("%d is in the tree.\n",key);
		return root;
		}
}

Tree insertNode(Tree root, int key){
	if(root==NULL){
		root=malloc(sizeof(struct BinarySearchTree));
		root->value=key;
		root->left=root->right=NULL;
		printf("insert %d\n",root->value);
	}
	else if(key<root->value){
		root->left=insertNode(root->left, key);
	}
	else if(key>root->value){
		root->right=insertNode(root->right, key);
	}
	else{
		printf("Insertion Error : There is already %d in the tree\n",key);
	}
	return root;
}

void printInorder(Tree root){
	if(root!=NULL){
		printInorder(root->left);
		printf("%d ",root->value);
		printInorder(root->right);
	}
}

void deleteTree(Tree root){
	if(root!=NULL){
	deleteTree(root->left);
	deleteTree(root->right);
	free(root);
	}
}

Tree getMaxValueInTree(Tree parentNode, Tree node){
	if(node==NULL){
		return parentNode;
	}
	if(node->right==NULL){
		return node;
	}
	else{
		return getMaxValueInTree(node, node->right);
	}
}

Tree deleteNode(Tree root, int key){
	Tree tmp;
	if(root==NULL){
		printf("Delection Error : %d is not in the tree.\n",key);
	}
	else if(root->value>key){
		root->left=deleteNode(root->left, key);
	}
	else if(root->value<key){
		root->right=deleteNode(root->right, key);
	}		
	else if(root->left&&root->right){
		tmp=getMaxValueInTree(root,root->left);
		root->value=tmp->value;
		root->left=deleteNode(root->left, root->value);
		printf("Delete %d\n",key);

	}
	else{
		tmp=root;
		if(root->left==NULL){
			root=root->right;
		}
		else if(root->right==NULL){
			root=root->left;
		}
	}
	return root;	
}



int main(int argc, char *argv[]) {
	
	FILE *fi=fopen(argv[1],"r");
	char cv;
	int key;
	
	Tree root=NULL;
	while(fscanf(fi, "%c", &cv) != -1){
		switch(cv){
			case 'i':
				fscanf(fi,"%d",&key);
				root=insertNode(root,key);
				break;
			case 'd':
				fscanf(fi,"%d",&key);
				deleteNode(root, key);
				break;
			case 'f':
				fscanf(fi,"%d",&key);
				findNode(root, key);
				break;
			case 'p':
				fscanf(fi,"%c",&cv);
				if(cv=='i'){
					printInorder(root);
				}
				printf("\n");
				break;
		}		
	}
	deleteTree(root);
}