#include <cstdio>
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


class Generator {
public:
	double totTime;
	int count;
	struct node
	{
		int num;
		bool dir;
	};

	struct node location[9];
//	FILE* file_write;

//	Generator(int number, FILE* file)
	{
		
	}

	void generate()   //生成函数
	{
		
	}


private:
	void Out()   //输出函数
	{
		
	}

	void TransForm()
	{
		
	}

	void Change()
	{
		
	}

	void Line_exchange_floor(int* number)
	{
		
	}

	void Line_exchange_middle(int* number)
	{
		
	}

	void Line_exchange_ground(int* number)
	{
		
	}

	void swap_line(int a, int b)
	{
		
	}
};

