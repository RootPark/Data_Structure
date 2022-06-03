#include <stdio.h>

int main(int argc, char *argv[]) {
	char name[30];
	printf("enter your name:\n");
	scanf("%[^\n]",name);
	printf("your name is %s\n",name);
}