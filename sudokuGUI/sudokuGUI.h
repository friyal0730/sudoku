#pragma once
#ifndef MAIN_UI_H
#define MAIN_UI_H
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QtWidgets/QMainWindow>


class sudokuGUI : public QMainWindow
{
	Q_OBJECT
	QLineEdit *let;
	QPushButton *pbt;
	QLabel *qlt;
	QHBoxLayout *hblayout;
public slots:
	void ClickokButton();//点击事件
public:
	sudokuGUI(QWidget *parent = 0);
	~sudokuGUI();
};

class Widget : public QWidget
{
	Q_OBJECT
	QLineEdit le[9][9];
	QGridLayout glayout;
	QPushButton *pb;
	QIntValidator *aIntValidator;
	int num;
public slots:
	void ClickButton();//点击事件
public:
	Widget(QWidget *parent = 0);
	~Widget();
};
#endif // MAIN_UI_H
