#include<stdio.h>
#include<stdlib.h>
#include "do_hoa.c"

#define MINE -1

int level(int *M, int *N, int *slg)
{	int n;
	while(1)
	{	printf("Which level do you want to play: 1, 2 or 3?  ");
		scanf("%d", &n);
		switch(n)
		{	case 1:
			{	*M=*N=8;
				*slg=10;
				return 0;;
			}
			case 2:
			{	*M=*N=16;
				*slg=40;
				return 0;;
			}
			case 3:
			{	*M=16;
				*N=30;
				*slg=99;
				return 0;
			}
			default:
				break;
		}
	}
}
void init(int M, int N, int slg, int B[][N], int T[][N])
{	int i, j;
	for(i=0; i<M; i++)
		for(j=0; j<N; j++)
		{	B[i][j]=0;
			T[i][j]=0;
		}
	int count=0;
	while(count<slg)
	{	int r, c;
		r=rand()%M;
		c=rand()%N;
		if(B[r][c]!=MINE)
		{	B[r][c]=MINE;
			count++;
		}		
	}
}

int cnt(int i, int j, int M, int N, int B[][N])
{	int r, c;
	int count=0;
	for(r=i-1; r<=i+1; r++)
		for(c=j-1; c<=j+1; c++)
		{	if(!(r>=0 && r<M && c>=0 && c<N))
				break;
			else if(B[r][c]==-1)
				count++;	 
		}
	return count;
}

void count_mines(int M, int N, int B[][N])
{	int i, j;
	for(i=0; i<M; i++)
	{   for(j=0; j<N; j++)
		{	int count=cnt(i, j, M, N, B);
			if(B[i][j]!=MINE)
		    	B[i][j]=count;
		}
	}
}

void printMap1(int M, int N, int B[][N])
{	int i, j;
	printf("\t  ");
    for(i=0; i<N; i++)
    	printf("%d ", i%10);	
    printf("\n");
	for(i=0; i<M; i++)
	{	printf("\t%d ", i%10);	
		for(j=0; j<N; j++)
			{	if(B[i][j]==MINE) 
				{	SetColor(0, 14);
					printf("x ");
					SetColor(0, 7);
				}
				else if(B[i][j]==0)
					printf(". ");
				else 
				{	SetColor(0, B[i][j]);
					printf("%d ", B[i][j]);
					SetColor(0, 7);
				}
			}	 
		printf("\n");
	}
	printf("\n");
}

void printMap2(int M, int N, int B[][N], int T[][N])
{	int i, j;
	printf("\t  ");
    for(i=0; i<N; i++)
   		printf("%d ", i%10);	
    printf("\n");
	for(i=0; i<M; i++)
	{	printf("\t%d ", i%10);	
		for(j=0; j<N; j++)
		{	if(T[i][j]==0)	
				printf("%c ", 254);	
			else if(B[i][j]==MINE) 
			{	SetColor(0, 14);
				printf("x ");
				SetColor(0, 7);
			}	
			else if(B[i][j]==0) 
				printf(". ");	
			else 
			{	SetColor(0, B[i][j]);
				printf("%d ", B[i][j]);
				SetColor(0, 7);
			}	
		}	 
		printf("\n");
	}
	for(i=0; i<N*4; i++)
        printf("%c", 197);
    printf("\n");
}

int count_remain(int M, int N, int T[][N])
{	int i, j;
	int count=0;	
	for(i=0; i<M; i++)
		for(j=0; j<N; j++)
			if(T[i][j]==0)	
				count++;	
	return count;
}

void open_cell_3(int r, int c, int M, int N, int B[M][N], int T[M][N])
{	int i, j;
	if(r<0 || r>=M || c<0 || c>=N) 
	;
    if(T[r][c]==1) 
	;
	else 
	{	T[r][c]=1;
		if(B[r][c]==0) 
			for(i=r-1; i<=r+1; i++)
				for(j=c-1; j<=c+1; j++)
				    if(i>=0 && i<M && j>=0 && j<N)
					    open_cell_3(i, j, M, N, B, T);
	}
}

int main()
{	start();
	int M, N, slg;
	level(&M, &N, &slg);	
	printf("Press ENTER to start the game...");
//ban do min
	int B[M][N];
//trang thai mo
	int T[M][N];
	getch();
	system("cls");
	init(M, N, slg, B, T);
	count_mines(M, N, B);
	while(1)
	{	system("cls");
		printMap2(M, N, B, T);
		int r, c;
		printf("\nChoose the cell that you want to open: ");
		scanf("%d%d", &r, &c);
		if(r<0 || r>=M || c<0 || c>=N)
		{	printf("Incorrectly cell! Try again!");
			getch();
			continue;
		}
		if(B[r][c]==MINE)
		{	system("cls");
			printf("That cell is MINE!\n\n");
			printMap1(M, N, B);
			end1();
			break;
		}
		open_cell_3(r, c, M, N, B, T);
		if(count_remain(M, N, T)==slg)
		{	system("cls");
			printMap1(M, N, B);
			end2();
			break;
		}
	}
	return 0;
}
