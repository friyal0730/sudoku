#pragma once
#ifndef __Base_H__
#define __Base_H__

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

int Sudoku[9][9] = {//基础数独终盘
	{ 2, 9, 3, 4, 5, 1, 7, 8, 6 },
	{ 5, 4, 1, 7, 8, 6, 9, 2, 3 },
	{ 8, 7, 6, 9, 2, 3, 4, 5, 1 },
	{ 9, 2, 4, 3, 1, 5, 8, 6, 7 },
	{ 1, 3, 5, 8, 6, 7, 2, 9, 4 },
	{ 6, 8, 7, 2, 9, 4, 3, 1, 5 },
	{ 3, 5, 9, 1, 4, 2, 6, 7, 8 },
	{ 4, 1, 2, 6, 7, 8, 5, 3, 9 },
	{ 7, 6, 8, 5, 3, 9, 1, 4, 2 } };

int Sudoku_backup[9][9] = {//基础数独终盘
	{ 2, 9, 3, 4, 5, 1, 7, 8, 6 },
	{ 5, 4, 1, 7, 8, 6, 9, 2, 3 },
	{ 8, 7, 6, 9, 2, 3, 4, 5, 1 },
	{ 9, 2, 4, 3, 1, 5, 8, 6, 7 },
	{ 1, 3, 5, 8, 6, 7, 2, 9, 4 },
	{ 6, 8, 7, 2, 9, 4, 3, 1, 5 },
	{ 3, 5, 9, 1, 4, 2, 6, 7, 8 },
	{ 4, 1, 2, 6, 7, 8, 5, 3, 9 },
	{ 7, 6, 8, 5, 3, 9, 1, 4, 2 } };

class Base {
public:
	double totTime;
	int count;
	struct node
	{
		int num;
		bool dir;
	};

	struct node location[9];
	FILE* file_write;

	Base(int number, FILE* file)
	{
		this->count = number;
		file_write = file;
		totTime = 0;
		for (int i = 0; i < 9; i++)
		{
			location[i].num = i;
			location[i].dir = true;
		}
	}

	void generate()   //生成函数
	{
		int number = 0;
		while (number < count)
		{
			Out();
			number++;

			Line_exchange_floor(&number);
			Line_exchange_middle(&number);
			Line_exchange_ground(&number);    //换行

			if (number < count)
			{
				TransForm();
				Change();
			}
		}
	}


private:
	void Out()   //输出函数
	{
		int pointer = 0;
		char temp[165];
		memset(temp, 0, sizeof(temp));
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				temp[pointer] = Sudoku[i][j] + '0';
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
		fputs(temp, file_write);
	}

	void TransForm()
	{
		int move = 0;
		int move_num = 0;
		for (int i = 1; i <= 8; i++)
		{
			if (location[i].dir && (i > 1))
			{
				bool moveable;
				moveable = location[i].num > location[i - 1].num;
				if (moveable)
				{
					move = move_num > location[i].num ? move : i;
					move_num = move_num > location[i].num ? move_num : location[i].num;
				}
			}
			else if (!location[i].dir && (i < 8))
			{
				bool moveable;
				moveable = location[i].num > location[i + 1].num;
				if (moveable)
				{
					move = move_num > location[i].num ? move : i;
					move_num = move_num > location[i].num ? move_num : location[i].num;
				}
			}
		}

		int temp = move_num;
		bool temp_dir = location[move].dir;
		if (temp_dir)
		{
			location[move].num = location[move - 1].num;
			location[move].dir = location[move - 1].dir;
			location[move - 1].num = temp;
			location[move - 1].dir = temp_dir;
		}
		else
		{
			location[move].num = location[move + 1].num;
			location[move].dir = location[move + 1].dir;
			location[move + 1].num = temp;
			location[move + 1].dir = temp_dir;
		}


		for (int i = 1; i <= 8; i++)
		{
			if (location[i].num > move_num)
			{
				location[i].dir = !location[i].dir;
			}
		}
	}

	void Change()
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (Sudoku_backup[i][j] < 9)
				{
					Sudoku[i][j] = location[Sudoku_backup[i][j]].num;
				}
			}
		}
	}

	void Line_exchange_floor(int* number)
	{
		if (*number < count)
		{
			swap_line(2, 1);
			*number = (*number) + 1;
			Out();
			Line_exchange_middle(number);
		}
		if (*number < count)
		{
			swap_line(2, 1);
		}
	}

	void Line_exchange_middle(int* number)
	{
		if (*number < count)
		{
			swap_line(3, 4);
			*number = (*number) + 1;
			Out();
			Line_exchange_ground(number);
		}
		if (*number < count)
		{
			swap_line(4, 5);
			*number = (*number) + 1;
			Out();
			Line_exchange_ground(number);
		}
		if (*number < count) {
			swap_line(3, 5);
			*number = (*number) + 1;
			Out();
			Line_exchange_ground(number);
		}

		if (*number < count) {
			swap_line(3, 4);
			*number = (*number) + 1;
			Out();
			Line_exchange_ground(number);
		}

		if (*number < count)
		{
			swap_line(4, 5);
			*number = (*number) + 1;
			Out();
			Line_exchange_ground(number);
		}
		if (*number < count)
		{
			swap_line(3, 5);
		}
	}

	void Line_exchange_ground(int* number)
	{
		if (*number < count)
		{
			swap_line(6, 7);
			Out();
			*number = (*number) + 1;
		}
		if (*number < count)
		{
			swap_line(7, 8);
			Out();
			*number = (*number) + 1;
		}
		if (*number < count)
		{
			swap_line(6, 8);
			Out();
			*number = (*number) + 1;
		}
		if (*number < count)
		{
			swap_line(6, 7);
			Out();
			*number = (*number) + 1;
		}
		if (*number < count)
		{
			swap_line(7, 8);
			Out();
			*number = (*number) + 1;
		}
		if (*number < count)
		{
			swap_line(6, 8);
		}
	}

	void swap_line(int a, int b)
	{
		int temp;
		for (int i = 0; i < 9; i++)
		{
			temp = Sudoku[a][i];
			Sudoku[a][i] = Sudoku[b][i];
			Sudoku[b][i] = temp;
		}
	}
};

#endif
