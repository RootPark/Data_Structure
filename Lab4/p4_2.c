#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack{
	int* key;
	int top;
	int max_stack_size;
}Stack;

int IsEmpty(Stack *S){
	if(S->top==-1){
		return 1;
	}
	return 0;
}

int Pop(Stack* S){
	if(IsEmpty(S)){
		printf("Error\n");
		return 0;
	}
	else{
		int result=S->key[S->top];
		S->top--;
		return result;
	}
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
	if(!IsFull(S)){
		printf("%d ",X);
		S->key[++S->top]=X;
	}
}

int Postfix(Stack* stack, char input_char){
	int a,b;
	int result=0;
	switch(input_char){
		case '+':
			a=Pop(stack);
			b=Pop(stack);
			result=b+a;
			Push(stack, result);
			break;
		case '-':
			a=Pop(stack);
			b=Pop(stack);
			result=b-a;
			Push(stack, result);
			break;
		case '*':
			a=Pop(stack);
			b=Pop(stack);
			result=b*a;
			Push(stack, result);
			break;
		case '/':
			a=Pop(stack);
			b=Pop(stack);
			result=b/a;
			Push(stack, result);
			break;
		case '%':
			a=Pop(stack);
			b=Pop(stack);
			result=b%a;
			Push(stack, result);
			break;
		default:
			Push(stack, input_char-'0');
			break;
	}
	return result;
}
void DeleteStack(Stack* S){
	free(S);
}

Stack* CreateStack(int max){
	Stack* S=NULL;
	S= (Stack*)malloc(sizeof(struct Stack));
	S->key=(int*)malloc(sizeof(int)*max);
	S->max_stack_size=max;
	S->top=-1;
	return S;
}

int Top(Stack* S){
	if(!IsEmpty(S)){
		return S->key[S->top];
	}
	else{
		return 0;
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
	
	printf("Top numbers :");
	
	for(i=0;i<strlen(input_str)&&input_str[i]!='#';i++){
		result=Postfix(stack, input_str[i]);
	}
	
	printf("\nevalutation result : %d\n",result);
	fclose(fi);
	DeleteStack(stack);
}

