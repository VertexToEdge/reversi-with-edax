#include "QTtest.h"



QTtest::QTtest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.Singleplay_man, SIGNAL(clicked()), this, SLOT(Singleplay_man_click()));
	QObject::connect(ui.Singleplay_com, SIGNAL(clicked()), this, SLOT(Singleplay_com_click()));
	QObject::connect(ui.Multiplay_man, SIGNAL(clicked()), this, SLOT(Multiplay_man_click()));
	QObject::connect(ui.Multiplay_com, SIGNAL(clicked()), this, SLOT(Multiplay_com_click()));
}

void QTtest::showGame(bool isSingle, bool isAI, bool isPlayerFirst, QString serverIP, int port) {
	/*QMessageBox msgbox;
	msgbox.setText(QString::fromLocal8Bit("안녕"));
	msgbox.exec();*/
	Game *w = new Game(isSingle,isAI,isPlayerFirst,serverIP,port);
	w->setAttribute(Qt::WA_DeleteOnClose);
	w->show();
	this->close();
}


void QTtest::Singleplay_man_click() {
	showGame(true,false);
}

void QTtest::Singleplay_com_click() {
	QMessageBox msgBox;
	msgBox.setText(QString::fromLocal8Bit("AI를 상대로 선공하시겠습니까?"));
	msgBox.setInformativeText(QString::fromLocal8Bit("선빵은 승리한다"));
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	int msgboxResult = msgBox.exec();

	showGame(true, true,msgboxResult==QMessageBox::Yes);
}

void QTtest::Multiplay_man_click() {
	showGame(false,false,false,ui.svr_ip->toPlainText(),ui.svr_port->toPlainText().toInt() );
}

void QTtest::Multiplay_com_click() {
	showGame(false, true, false, ui.svr_ip->toPlainText(), ui.svr_port->toPlainText().toInt());

}




