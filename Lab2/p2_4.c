#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define INT_MAX 2147438647

int Zero();
bool IsZero(int);
bool Equal(int,int);
int Successor(int);
int Add(int,int);
int Subtract(int,int);

int main(int argc, char **args) {
	int x=atoi(args[1]);
	int y=atoi(args[2]);
	
	printf("Is %d zero? %s\n",x,IsZero(x) ? "True": "False");
	printf("Is %d zero? %s\n",y,IsZero(y) ? "True": "False");
	printf("Does %d equal %d? %s\n",x,y,Equal(x, y) ? "True": "False");
	printf("%d's next number is %d\n",x,Successor(x));
	printf("%d's next number is %d\n",y,Successor(y));
	printf("%d + %d = %d\n",x,y,Add(x,y));
	printf("%d + %d = %d\n",x,y,Subtract(x,y));
	
	return 0;

}

bool IsZero(int a){
	if(a==0){
		return true;
	}
	else{
		return false;
	}
}

bool Equal(int a,int b){
	if(a==b){
		return true;
	}
	else{
		return false;
	}
}

int Successor(int a){
	if(a+1<INT_MAX && a+1>0){
		return a+1;
	}
	else{
		return a;
	}
}
int Add(int a,int b){
	if(a+b<INT_MAX && a+1<0){
		return a+b;
	}
	else{
		return INT_MAX;
	}
}
int Subtract(int a,int b){
	if(a>b){
		return a-b;
	}
	else{
		return 0;
	}
}
