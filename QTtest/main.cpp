#include "QTtest.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QTextCodec>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTtest w;

	w.show();
	return a.exec();
}
