#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

void SetColor(int backgound_color, int text_color)
{   HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

//MINESWEEPER 219 220 223
void start()
{	FILE *f;
	f=fopen("intro", "r");
	char s[100];
	while(fgets(s, 100, f)!=NULL)
	{  	if (s[strlen(s)-1] =='\n')
   			s[strlen(s)-1] ='\0';
   		SetColor(0, rand()%15);
		printf("\t\t%s\n", s);
		SetColor(0, 7);
	}
	printf("\n");
	fclose(f);
}

void end1()
{	FILE *f;
	f=fopen("gameover", "r");
	char s[100];
	while(fgets(s, 100, f)!=NULL)
	{  	if (s[strlen(s)-1] =='\n')
   			s[strlen(s)-1] ='\0';
   		SetColor(0, 8);
		printf("\t%s\n", s);
		SetColor(0, 7);
	}
	fclose(f);
}

void end2()
{	FILE *f;
	f=fopen("gamewin", "r");
	char s[100];
	while(fgets(s, 100, f)!=NULL)
	{  	if (s[strlen(s)-1] =='\n')
   			s[strlen(s)-1] ='\0';
		SetColor(0, 9);
		printf("\t%s\n", s);
		SetColor(0, 7);
	}
	fclose(f);
}

//int main()
//{	start();
//	end1();
//	end2();
//	return 0;
//}


