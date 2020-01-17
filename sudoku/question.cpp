#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <cstring>
#include <cstdio>
#include <ctime>

int incom_sudoku[9][9];
FILE* question;
FILE* solver;

void change()
{
	int a = 0, b = 2;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				int ran1 = (rand() % (b - a + 1)) + a;
				int ran2 = (rand() % (b - a + 1)) + a;
				if ((ran1 + i * 3)*(ran2 + j * 3) != 0)
				{
					incom_sudoku[ran1 + i * 3][ran2 + j * 3] = 0;
				}
			}
		}
	}
	a = 0, b = 8;
	for (int i = 0; i < 42; i++)
	{
		int ran1 = (rand() % (b - a + 1)) + a;
		int ran2 = (rand() % (b - a + 1)) + a;
		if (ran1 != 0 && ran2 != 0)
		{
			incom_sudoku[ran1][ran2] = 0;
		}
	}
}

void Out()
{
	int pointer = 0;
	char temp[165];
	memset(temp, 0, sizeof(temp));

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			temp[pointer] = incom_sudoku[i][j] + '0';
			pointer++;
			if (j != 8)
			{
				temp[pointer] = ' ';
				pointer++;
			}
		}
		temp[pointer] = '\n';
		pointer++;
	}
	temp[pointer] = '\n';
	fputs(temp, solver);
}

int main()
{
	question = freopen("sudoku.txt", "r", stdin);
	solver = freopen("solver.txt", "w", stdout);
	srand((unsigned)time(NULL));
	while (true)
	{
		if (fscanf_s(question, "%d", &incom_sudoku[0][0]) == EOF)
		{
			break;
		}
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (i == 0 && j == 0) continue;
				fscanf_s(question, "%d", &incom_sudoku[i][j]);
			}
		}
		change();
		Out();
	}
	return 0;
}
