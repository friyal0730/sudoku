#pragma once
#ifndef __SOLVER_H__
#define __SOLVER_H__

#pragma warning(disable : 4996)

#include <map>
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;

int flag = 0;
class Solver{
public:
	int sudoku[9][9];
	FILE* question;
	FILE* file_write;
	int flag;
	
	Solver(FILE* path,FILE* ans)
	{
		flag = 0;
		question = path;
		file_write = ans;
		memset(sudoku,0,sizeof(sudoku));
	}

	int test()
	{
		return flag;
	}

	int in()
	{
		while (true)
		{
			if (fscanf_s(question, "%d", &sudoku[0][0]) == EOF)  //读完了
			{
				break;
			}

			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (i == 0 && j == 0) continue;   
					fscanf_s(question,"%d",&sudoku[i][j]);
				}
			}
			
			if (dfs(0))
			{
				if (valid(sudoku) != 1)
					flag = 1;
				Out();    //解决之后输出
			}
		}
		return test();
	}

private:
	void Out()
	{
		int pointer = 0;
		char num[165];
		memset(num, 0, sizeof(num));

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				num[pointer] = sudoku[i][j] + '0';
				pointer++;
				if (j != 8) 
				{
					num[pointer] = ' ';
					pointer++;
				}
			}
			num[pointer] = '\n';
			pointer++;
		}
		num[pointer] = '\n';
		fputs(num, file_write);
	}

	bool dfs(int tot)   //dfs搜索方法
	{             
		if (tot > 80)
		{
			return true;
		}
		
		int line = tot / 9;
		int col = tot % 9;

		if (sudoku[line][col] > 0)
		{
		    return dfs(tot + 1);
		}

		for(int i = 1;i <= 9;i++)
		{
			sudoku[line][col] = i;
			if (check(line, col, i))
			{
				if (dfs(tot + 1)) 
				{
					return true;
				}
			}
			sudoku[line][col] = 0;
		}
		
		return false;
	}

	bool check(int line, int col,int num)
	{
		for (int i = 0; i < 9; i++)
		{
			if ((col != i) && sudoku[line][i] == num) 
			{
				return false;
			}
		}

		for (int i = 0; i < 9; i++)
		{
			if ((i != line) && sudoku[i][col] == num)
			{
				return false;
			}
		}

		int base_line = line / 3 * 3;
		int base_col = col / 3 * 3;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if ((line != base_line + i) && (col != base_col + j) && sudoku[base_line + i][base_col + j] == num)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool valid(int sudoku[][9]) 
	{
		for (int i = 0; i < 9; i++) 
		{
			bool line_exist[10];
			memset(line_exist, 0, sizeof(line_exist));
			for (int j = 0; j < 9; j++) {
				if ((i == 0 && (j == 0 || j == 3 || j == 6)) || (i == 3 && (j == 0 || j == 3 || j == 6))
					|| (i == 6 && (j == 0 || j == 3 || j == 6))) 
				{
					bool exist[10];
					memset(exist, 0, sizeof(exist));
					for (int cell_i = 0; cell_i < 3; cell_i++)
					{
						for (int cell_j = 0; cell_j < 3; cell_j++) 
						{
							exist[sudoku[cell_i + i][cell_j + j]] = true;
						}
					}
					for (int exist_i = 1; exist_i < 10; exist_i++)
					{
						if (!exist[exist_i])
							return false;
					}
				}

				line_exist[sudoku[i][j]] = true;
			}

			for (int j = 1; j <= 9; j++)
			{
				if (!line_exist[j])
				{
					return false;
				}
			}
		}

		for (int i = 0; i < 9; i++)
		{
			bool col_exist[10];
			memset(col_exist, 0, sizeof(col_exist));
			for (int j = 0; j < 9; j++)
			{
				col_exist[sudoku[j][i]] = true;
			}
			for (int j = 1; j <= 9; j++)
			{
				if (!col_exist[j]) 
				{
					return false;
				}
			}
		}
		return true;
	}
};

#endif