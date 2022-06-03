#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **args) {
	int num=atoi(args[1]);
	printf("enter %d names:\n",num);
	
	char **name=(char**)malloc(sizeof(char*)*num);
	for(int i=0;i<num;i++){
		name[i]=(char*)malloc(sizeof(char*)*30);
		scanf("%s",name[i]);
	}
	printf("the names your entered:\n");
	for(int i=0;i<num;i++){
		printf("%s\n",name[i]);
		free(name[i]);
	}
	free(name);
	return 0;
}