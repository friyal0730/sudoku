/* 
 * solve.h
 * 类名：solve
 * 作用：检查判断输入参数，并创建相应的数独生成对象或者数独解决对象
 * 
 */
#pragma once
#ifndef _solve_H_
#define _solve_H_

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstring>
#include"base.h"
#include"answer.h"
#define MAX 1000005
using namespace std;

class solve {
public:
	int argc;
	char** argv;
	int flag;
	solve(int argc, char** argv)
	{
		this->argc = argc;
		this->argv = argv;
		solveinput();   
	}

	int solveinput() //判断并执行命令
	{
		if (argc != 3) //输入格式不正确
		{
			cout << "Illegal paramater number" << endl;
			cout << "Input like this: [sudoku.exe -c n] or [sudoku.exe -s path]" << endl;
			return 1;
		}

		if (strcmp(argv[1], "-c") && strcmp(argv[1], "-s"))   //字母错误
		{
			cout << "The first parameter should only be -c or -s" << endl;
			cout << "-c means to generate the sudoku to file." << endl;
			cout << "-s means to solve the sudoku from the file." << endl;
			return 2;
		}

		if (!strcmp(argv[1], "-c"))   //创造数独终盘
		{
			int sum = 0;   //sudoku的个数
			int len = strlen(argv[2]);
			for (int i = 0; i < len; i++)
			{
				if (!(argv[2][i] >= '0' && argv[2][i] <= '9'))   //输入的字符不合法（不是数字）
				{
					cout << "The third paramater after -c should be number that indicate the sudoku you want." << endl;
					if (argv[2][i] == '+' || argv[2][i] == '-' || argv[2][i] == '/' || argv[2][i] == '*')
					{
						cout << "Please input the number!" << endl;
						return 8;
					}
					return 3;
				}
				sum = 10 * sum + argv[2][i] - '0';
			}

			if (sum > MAX || sum < 1)   //数字过大
			{
				cout << "The number is too large,the number should be 1-1000000" << endl;
				return 4;
			}
			/*----------------------------------*/
			/*创建数独终盘对象*/
			/*...........*/

			FILE* file;
			file = freopen("sudoku.txt", "w", stdout);   //没有文件时可以创造
			Base base(sum, file);    //调用Generator
			base.generate();
			/*----------------------------------*/

			return 5;
		}

		if (!strcmp(argv[1], "-s"))   //解题
		{
			FILE* ans;
			FILE* question;   //数独题目
			question = freopen(argv[2], "r", stdin);
			if (!question)
			{
				cout << "The file path is not right,please check." << endl;
				return 6;
			}
			/*----------------------------------*/
			/*创建数独求解对象*/
			/*...........*/
			ans = freopen("sudoku.txt", "w", stdout);
			Solver solver(question, ans);   //调用Solver
			flag = solver.in();
			/*----------------------------------*/
			return 7;
		}
		
		return 8;   //正常执行，消除警告
	}
};
#endif
