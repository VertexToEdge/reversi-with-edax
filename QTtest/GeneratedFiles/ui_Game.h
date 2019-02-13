/********************************************************************************
** Form generated from reading UI file 'Game.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Game
{
public:
    QLabel *label;
    QLabel *BlackScore;
    QLabel *WhiteScore;
    QLabel *BlackTime;
    QLabel *WhiteTime;
    QPushButton *GetRecommend;

    void setupUi(QWidget *Game)
    {
        if (Game->objectName().isEmpty())
            Game->setObjectName(QString::fromUtf8("Game"));
        Game->resize(554, 601);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Game->sizePolicy().hasHeightForWidth());
        Game->setSizePolicy(sizePolicy);
        Game->setStyleSheet(QString::fromUtf8("background-color: green"));
        label = new QLabel(Game);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 30, 31, 71));
        label->setAlignment(Qt::AlignCenter);
        BlackScore = new QLabel(Game);
        BlackScore->setObjectName(QString::fromUtf8("BlackScore"));
        BlackScore->setGeometry(QRect(180, 30, 81, 61));
        QFont font;
        font.setPointSize(36);
        BlackScore->setFont(font);
        BlackScore->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        WhiteScore = new QLabel(Game);
        WhiteScore->setObjectName(QString::fromUtf8("WhiteScore"));
        WhiteScore->setGeometry(QRect(290, 30, 81, 61));
        WhiteScore->setFont(font);
        WhiteScore->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        BlackTime = new QLabel(Game);
        BlackTime->setObjectName(QString::fromUtf8("BlackTime"));
        BlackTime->setGeometry(QRect(40, 60, 64, 31));
        WhiteTime = new QLabel(Game);
        WhiteTime->setObjectName(QString::fromUtf8("WhiteTime"));
        WhiteTime->setGeometry(QRect(460, 60, 64, 31));
        WhiteTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        GetRecommend = new QPushButton(Game);
        GetRecommend->setObjectName(QString::fromUtf8("GetRecommend"));
        GetRecommend->setGeometry(QRect(400, 30, 93, 28));

        retranslateUi(Game);

        QMetaObject::connectSlotsByName(Game);
    } // setupUi

    void retranslateUi(QWidget *Game)
    {
        Game->setWindowTitle(QApplication::translate("Game", "Game", nullptr));
        label->setText(QApplication::translate("Game", "<html><head/><body><p><span style=\" font-size:36pt;\">:</span></p></body></html>", nullptr));
        BlackScore->setText(QApplication::translate("Game", "<html><head/><body><p><span style=\" font-size:36pt;\">0</span></p></body></html>", nullptr));
        WhiteScore->setText(QApplication::translate("Game", "<html><head/><body><p><span style=\" font-size:36pt;\">0</span></p></body></html>", nullptr));
        BlackTime->setText(QApplication::translate("Game", "<html><head/><body><p><span style=\" font-size:18pt;\">0</span></p></body></html>", nullptr));
        WhiteTime->setText(QApplication::translate("Game", "<html><head/><body><p><span style=\" font-size:18pt;\">0</span></p></body></html>", nullptr));
        GetRecommend->setText(QApplication::translate("Game", "\354\236\220\353\246\254\354\266\224\354\262\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Game: public Ui_Game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
