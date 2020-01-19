#include "sudokuGUI.h"
#include "base.h"
#include <QMessageBox>
#include <Qstring>
#include <stdio.h>
#include <time.h>

int question[9][9][100];
int answer[9][9][100];
int number;
int input()
{
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	fp1 = fopen("solver.txt", "r");
	fp2 = fopen("sudoku.txt", "r");
	int count = 0;
	while (fscanf(fp1, "%d", &question[0][0][count]) != EOF)//读入问题
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (i == 0 && j == 0) continue;
				else fscanf(fp1, "%d", &question[i][j][count]);
			}
		}
		count++;
	}
	int n = count;
	count = 0;
	while (fscanf(fp2, "%d", &answer[0][0][count]) != EOF)//读入答案
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (i == 0 && j == 0) continue;
				else fscanf(fp2, "%d", &answer[i][j][count]);
			}
		}
		count++;
	}
	fclose(fp1);
	fclose(fp2);
	return n;
}
void creat_the_end(int n)
{
	FILE* file = NULL;
	file = fopen("sudoku.txt", "w");   //没有文件时可以创造
	base generator(n, file);    //调用Generator
	generator.generate();
	fclose(file);
}
void change(int *sudoku)
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
					sudoku[((ran1 + i * 3) * 9) + (ran2 + j * 3)] = 0;
				}
			}
		}
	}
	a = 0, b = 8;
	for (int i = 0; i < 42; i++)
	{
		int ran1 = (rand() % (b - a + 1)) + a;
		int ran2 = (rand() % (b - a + 1)) + a;
		if (ran1*ran2 != 0)
		{
			sudoku[ran1 * 9 + ran2] = 0;
		}
	}
}

void Out(int *sudoku, FILE* solver)
{

	int pointer = 0;
	char temp[165];
	memset(temp, 0, sizeof(temp));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			temp[pointer] = sudoku[i * 9 + j] + '0';
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
void creat_the_question()
{
	FILE* question = NULL;
	FILE* solver = NULL;
	question = fopen("sudoku.txt", "r");
	solver = fopen("solver.txt", "w");
	srand((unsigned)time(NULL));
	int sudoku[9][9];
	while (fscanf(question, "%d", &sudoku[0][0]) != EOF)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (i == 0 && j == 0) continue;
				fscanf(question, "%d", &sudoku[i][j]);
			}
		}
		change(&sudoku[0][0]);
		Out(&sudoku[0][0], solver);
	}
	fclose(question);
	fclose(solver);
}
void running(int n)
{
	creat_the_end(n);
	creat_the_question();
	input();
	for (int i = 0; i < n; i++)
	{
		number = i;//编号
		Widget *w = new Widget();
		w->show();
	}
}

bool valid(int sudoku[][9])
{
	for (int i = 0; i < 9; i++)
	{
		bool line_exist[10];
		memset(line_exist, 0, sizeof(line_exist));
		for (int j = 0; j < 9; j++)
		{
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

sudokuGUI::sudokuGUI(QWidget *parent) 
	: QMainWindow(parent)
{
	qlt = new QLabel();
	qlt->setText(QObject::tr("输出数独题个数："));

	let = new QLineEdit();
	QIntValidator *validator = new QIntValidator(0, 999);
	let->setValidator(validator);
	let->setText("1");

	pbt = new QPushButton();
	connect(pbt, SIGNAL(clicked()), this, SLOT(ClickokButton()));
	pbt->setText("OK");

	hblayout = new QHBoxLayout(this);
	hblayout->addWidget(qlt);
	hblayout->addWidget(let);
	hblayout->addWidget(pbt);



	this->setWindowTitle("请输入");
	this->setFixedSize(300, 200);
}

sudokuGUI::~sudokuGUI()
{
}
void sudokuGUI::ClickokButton()//点击事件
{
	QString s = this->let->text();
	int geshu = s.toInt();
	s = QString::number(geshu);
	if (geshu > 0 && geshu < 1000)
	{
		running(geshu);
		QMessageBox::about(this, tr("提示信息"), tr("生成数独"));
		this->close();
		return;
	}
	else if (geshu == 0)
	{
		QMessageBox::about(this, tr("提示信息"), tr("不生成数独，程序结束！"));
		this->close();
		return;
	}
	else return;
}
Widget::Widget(QWidget *parent) : QWidget(parent)
{
	this->num = number;//当前数独编号
	pb = new QPushButton();
	pb->setText("验证答案");
	connect(pb, SIGNAL(clicked()), this, SLOT(ClickButton()));

	QIntValidator *aIntValidator = new QIntValidator();
	aIntValidator->setRange(1, 9);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			le[i][j].setAlignment(Qt::AlignCenter);//文字居中
			le[i][j].setValidator(aIntValidator);
			le[i][j].setMaximumSize(50, 50);//文本框大小
			le[i][j].setFont(QFont("Timers", 30));//文字字体大小
			glayout.addWidget(&le[i][j], i, j);
		}
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (question[i][j][this->num] != 0)
			{
				QString str = QString::number(question[i][j][this->num]);
				le[i][j].setText(str);
				le[i][j].setEnabled(false);//不可编辑
			}
		}
	}
	glayout.addWidget(pb, 9, 3, 1, 3);
	this->setLayout(&glayout);
	QString nums = QString::number(this->num + 1);
	this->setWindowTitle("第" + nums + "篇数独");//窗口标题
	this->setFixedSize(500, 550);
}
void Widget::ClickButton()//验证数独正确性
{
	    for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{
				QString s=this->le[i][j].text();
				if(s.toInt()!=answer[i][j][this->num])
				{
					QMessageBox::about(this,tr("提示信息"),tr("Wrong Answer!"));//弹窗提示错误
					//qDebug("%d %d %d %d",i,j,s.toInt(),answer[i][j][this->num]);//调试
					return ;
				}
			}
		}
		QMessageBox::about(this,tr("提示信息"),tr("You Got it!"));//成功解出
	
	int checkedsd[9][9];
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			QString s = this->le[i][j].text();
			checkedsd[i][j] = s.toInt();
		}
	}
	if (valid(checkedsd) == true)
	{
		QMessageBox::about(this, tr("提示信息"), tr("You Got it!"));//成功解出
	}
	else QMessageBox::about(this, tr("提示信息"), tr("Wrong Answer!"));//弹窗提示错误
}

Widget::~Widget()
{

}