#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet
{
	int size_maze;
	int *ptr_arr;
} DisjointSets;


void init(DisjointSets *sets, DisjointSets *maze_print, int num)
{
	sets->size_maze = num*num;
	sets->ptr_arr = (int*)malloc(sizeof(int)*sets->size_maze+1);
	int i;
	for ( i = 1; i <= num*num; i++ )
	{
		sets->ptr_arr[i] = 0;
	}

	maze_print->size_maze = (num*2+1)*(num*2+1);
	maze_print->ptr_arr = (int*)malloc(sizeof(int)*maze_print->size_maze);
	int n = 0, low, col;
	for ( low = 0; low < num * 2 + 1; low++ )
	{
		for ( col = 0; col < num * 2 + 1; col++ )
		{
			if ( (low + col) % 2 != 0 ) maze_print->ptr_arr[n] = -1;
			else maze_print->ptr_arr[n] = 0;

			if( low == 1 && col == 0) maze_print->ptr_arr[n] = 0;
			if( low == (2*num+1)-2 && col == (2*num+1)-1 ) maze_print->ptr_arr[n] = 0;
			n++;
		}
	}
}

void _union( DisjointSets *sets, int i, int j )
{
	int first = find(sets, i);
	int second = find(sets, j);

	if ( sets->ptr_arr[second] < sets->ptr_arr[first] ) sets->ptr_arr[first] = second;
	else
	{
		if ( sets->ptr_arr[second] == sets->ptr_arr[first] ) sets->ptr_arr[first]--;
		sets->ptr_arr[second] = first;
	}
}

int find(DisjointSets *sets, int i)
{
	while ( sets->ptr_arr[i] > 0 ) i = sets->ptr_arr[i];
	return i;
}

void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num)
{
	srand((unsigned int)time(NULL));

	while ( 1 )
	{
		int a = (rand() % (num*num)) + 1;
		int b = (rand() % (num*num)) + 1;
		int uni1 = find(sets, a);
		int uni2 = find(sets, b);

		int up = (a <= num) ? -1 : a - num;
		int down = (a > num*(num-1)) ? -1 : a + num;
		int left = (a % num == 1) ? -1 : a - 1;
		int right = (a % num == 0) ? -1 : a + 1;

		if( uni1 == uni2 || a == b ) continue;
		if ( b == up || b == down || b == left || b == right )
		{
			_union(sets, uni1, uni2);

			int size = 2 * num + 1;
			if ( b == up )
			{
				int low = a / num;
				int col = a % num;
				if( col == 0 ) col = num, low -= 1;
				maze_print->ptr_arr[size * ( low * 2 ) + (2 * (col-1) + 1)] = 0;
			}
			else if ( b == down )
			{
				int low = b / num;
				int col = b % num;
				if( col == 0 ) col = num, low -= 1;
				maze_print->ptr_arr[size * ( low * 2 ) + ( 2 * (col-1) + 1 )] = 0;
			}
			else if ( b == left )
			{
				int low = b / num;
				int col = b % num;
				maze_print->ptr_arr[size * ( 2 * low + 1 ) + 2 * col] = 0;
			}
			else if ( b == right )
			{
				int low = a / num;
				int col = a % num;
				maze_print->ptr_arr[size * (2 * low + 1) + 2 * col] = 0;
			}
			if(find(sets, 1) == find(sets, num*num)) break;
		}
	}
}

void printMaze(DisjointSets *sets, int num)
{
	int n = 0, low, col;
	for ( low = 0; low < num * 2 + 1; low++ )
	{
		for ( col = 0; col < num * 2 + 1; col++ )
		{
			if ( low % 2 == 0 )
			{
				if ( sets->ptr_arr[n] == -1 ) printf("-");
				else printf(" ");
			}
			else
			{
				if ( sets->ptr_arr[n] == -1 ) printf("|");
				else printf(" ");
			}
			n++;
		}
		printf("\n");
	}
}

void freeMaze(DisjointSets *sets, DisjointSets *maze_print)
{
	free(sets->ptr_arr);
	free(sets);

	free(maze_print->ptr_arr);
	free(maze_print);
}

int main(int argc, char* argv[])
{
	int num, i;
	FILE *fi = fopen(argv[1], "r");
	DisjointSets *sets, *maze_print;
	fscanf(fi, "%d", &num);
	sets = (DisjointSets*)malloc(sizeof(DisjointSets));
	maze_print = (DisjointSets*)malloc(sizeof(DisjointSets));
	init(sets, maze_print, num);
	createMaze(sets, maze_print, num);
	printMaze(maze_print, num);
	

	freeMaze(sets, maze_print);
	fclose(fi);
	return 0;
}
