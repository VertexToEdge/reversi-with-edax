#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTtest.h"
#include <QMessageBox>
#include <QTextStream>
#include <Game.h>

class QTtest : public QMainWindow
{
	Q_OBJECT

public:
	QTtest(QWidget *parent = Q_NULLPTR);
	void showGame(bool isSingle, bool isAI, bool isPlayerFirst=false, QString serverIP=QString(""), int port=0);
public slots:
	void Singleplay_man_click();
	void Singleplay_com_click();
	void Multiplay_man_click();
	void Multiplay_com_click();
private:
	Ui::QTtestClass ui;
};
