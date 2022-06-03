#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack{
	int* key;
	int top;
	int max_stack_size;
}Stack;

int IsEmpty(Stack *S){
	
}
int Pop(Stack* S){
	
}
int Postfix(Stack *S, char input_str){
	
}
void DeleteStack(Stack* S){
	
}

Stack* CreateStack(int max){
	Stack* S=NULL;
	S= (Stack*)malloc(sizeof(struct Stack));
	S->key=(int*)malloc(sizeof(int)*max);
	S->max_stack_size=max;
	S->top=-1;
	return S;
}

int IsFull(Stack *S){
	if(S->top+1>=10){
		return 1;
	}
	return 0;
}

void Push(Stack* S, int X){
	if(IsFull(S)){
		printf("Error\n");
	}
	else{
		S->key[++S->top]=X;
		printf("%d inserted\n",X-48);
	}
}

int main(int argc, char* argv[]) {
	FILE* fi=fopen(argv[1],"r");
	
	Stack* stack;
	char input_str[101];
	int max,i=0,a,b,result;
	
	fgets(input_str,101,fi);
	max=10;
	stack=CreateStack(max);
	
	for(i=0;i<strlen(input_str)&&input_str[i]!='#';i++){
		Push(stack, input_str[i]);
	}
	fclose(fi);
	DeleteStack(stack);
	
}