/********************************************************************************
** Form generated from reading UI file 'QTtest.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTEST_H
#define UI_QTTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTtestClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *Singleplay_man;
    QPushButton *Singleplay_com;
    QGroupBox *groupBox_2;
    QPushButton *Multiplay_man;
    QTextEdit *svr_ip;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *svr_port;
    QPushButton *Multiplay_com;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTtestClass)
    {
        if (QTtestClass->objectName().isEmpty())
            QTtestClass->setObjectName(QString::fromUtf8("QTtestClass"));
        QTtestClass->resize(402, 471);
        centralWidget = new QWidget(QTtestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(60, 30, 291, 141));
        Singleplay_man = new QPushButton(groupBox);
        Singleplay_man->setObjectName(QString::fromUtf8("Singleplay_man"));
        Singleplay_man->setGeometry(QRect(40, 30, 221, 41));
        Singleplay_com = new QPushButton(groupBox);
        Singleplay_com->setObjectName(QString::fromUtf8("Singleplay_com"));
        Singleplay_com->setGeometry(QRect(40, 80, 221, 41));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(60, 180, 291, 211));
        Multiplay_man = new QPushButton(groupBox_2);
        Multiplay_man->setObjectName(QString::fromUtf8("Multiplay_man"));
        Multiplay_man->setGeometry(QRect(30, 100, 231, 41));
        svr_ip = new QTextEdit(groupBox_2);
        svr_ip->setObjectName(QString::fromUtf8("svr_ip"));
        svr_ip->setGeometry(QRect(80, 30, 181, 21));
        svr_ip->setInputMethodHints(Qt::ImhNone);
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 41, 21));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 60, 41, 21));
        svr_port = new QTextEdit(groupBox_2);
        svr_port->setObjectName(QString::fromUtf8("svr_port"));
        svr_port->setGeometry(QRect(140, 60, 121, 21));
        svr_port->setInputMethodHints(Qt::ImhNone);
        Multiplay_com = new QPushButton(groupBox_2);
        Multiplay_com->setObjectName(QString::fromUtf8("Multiplay_com"));
        Multiplay_com->setGeometry(QRect(30, 150, 231, 41));
        Multiplay_com->setMouseTracking(true);
        QTtestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTtestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 402, 26));
        QTtestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTtestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QTtestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QTtestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QTtestClass->setStatusBar(statusBar);

        retranslateUi(QTtestClass);

        QMetaObject::connectSlotsByName(QTtestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTtestClass)
    {
        QTtestClass->setWindowTitle(QApplication::translate("QTtestClass", "Othello Stone!", nullptr));
        groupBox->setTitle(QApplication::translate("QTtestClass", "\354\213\261\352\270\200\355\224\214\353\240\210\354\235\264", nullptr));
        Singleplay_man->setText(QApplication::translate("QTtestClass", "\354\230\201\355\230\274\354\235\230 \353\247\236\353\213\244\354\235\264", nullptr));
        Singleplay_com->setText(QApplication::translate("QTtestClass", "AI \353\214\200\353\202\234\355\210\254", nullptr));
        groupBox_2->setTitle(QApplication::translate("QTtestClass", "\353\251\200\355\213\260\355\224\214\353\240\210\354\235\264", nullptr));
        Multiplay_man->setText(QApplication::translate("QTtestClass", "\354\247\201\354\240\221 \353\251\200\355\213\260\355\224\214\353\240\210\354\235\264", nullptr));
        svr_ip->setHtml(QApplication::translate("QTtestClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">127.0.0.1</p></body></html>", nullptr));
        label->setText(QApplication::translate("QTtestClass", "IP", nullptr));
        label_2->setText(QApplication::translate("QTtestClass", "PORT", nullptr));
        svr_port->setHtml(QApplication::translate("QTtestClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">8472</p></body></html>", nullptr));
        Multiplay_com->setText(QApplication::translate("QTtestClass", "\354\213\240\354\206\215\354\240\225\355\231\225 \353\214\200\353\246\254 \355\224\214\353\240\210\354\235\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTtestClass: public Ui_QTtestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTEST_H
