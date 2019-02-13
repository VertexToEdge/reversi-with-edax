#pragma once

#include <QTcpSocket>

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include "ui_Game.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <cstdlib>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Game : public QWidget
{
	Q_OBJECT


private:
	HINSTANCE hInst;

	Ui::Game ui;
	int map[8][8] = {0,};   //0: empty 1:black  2:white  3:available

	char moveLogs[65] = { 0, }; //실제론 60개면 충분할거
	bool turnLogs[65] = { 0, };
	int moveCnt = 0;

	QTcpSocket tcpSocket;

	const int sx = 40, sy = 100;
	const int boxSize = 480;
	const int stoneSize = 56;
	const int availableSize = 16;
	const int direction[8][2] = { {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1} };

	bool isSingle;
	bool isAI;
	std::string svrIP;
	int svrPort;

	int focusPosition=-1;

	bool NetworkAIflag=false;
	int BlackPlyaerType=0; // 0:man  1:network  2:AI
	int WhitePlayerType=0;// 0:man  1:network  2:AI

	bool currentTurn=true;  //1:black  0:white
	bool lastTurn;
	int blackTime = 0;
	int whiteTime = 0;
	bool aiTurn = false;
	int aiX = 0;
	int aiY = 0;

	
	int timerID;
	bool timerAllocated = false;
	void setTimeout(int black, int white) {
		blackTime = black;
		whiteTime = white;
	}
	void setOpponentTimeout(int time);
	quint32 PacketSize=0;
public:
	void AddrToXY(int addr,int &x,int &y);
	int xyToAddr(int x, int y);
	int getAImove();
	void moveLogInit();
	void addMoveLog(int x, int y);


	void ServerPacketReceived(QJsonObject data);

	void sendPutPacket(int x,int y);

	bool setMap(int x,int y,int value);
	int getMap(int x, int y);

	bool map_dfs(int x, int y, int d, int color, bool set = false);
	bool chkAvailable(int x, int y, int color,bool set=false);
	bool chkAvailables(int color,bool set=false);
	bool chkAvailables(bool turn, bool set = false);

	void ShowGameResult(int type=0);
	int getScoreGap();

	void removeAvailable();
	void setStone(int x,int y,int color);
	void moveGame(int x, int y);
	void resetMap();

	int getPlayerStones(int color);
	int getPlayerStones(bool turn);

	int turnToColor(bool turn);
	int turnToPlayer(bool turn);
	int flipColor(int color);

	int getThisPlayerColor();

	int lastTimeout = 30;

	bool isGameStart = false;
	Game(QWidget *parent = Q_NULLPTR);
	Game(bool isSingle, bool isAI, bool isPlayerFirst, QString serverIP, int port,QWidget *parent = Q_NULLPTR);
	~Game();

protected:

	void drawWhite(QPainter &painter,int x,int y) {
		x -= stoneSize / 2;
		y -= stoneSize / 2;
		painter.setBrush(QBrush(Qt::white));
		painter.drawEllipse(x, y, stoneSize, stoneSize);
	}
	void drawBlack(QPainter &painter, int x, int y) {
		x -= stoneSize / 2;
		y -= stoneSize / 2;
		painter.setBrush(QBrush(Qt::black));
		painter.drawEllipse(x, y, stoneSize, stoneSize);
	}
	void drawAvailable(QPainter &painter, int x, int y) {
		x -= availableSize / 2;
		y -= availableSize / 2;
		painter.setBrush(QBrush(Qt::blue));
		painter.drawEllipse(x, y, availableSize , availableSize );
	}
	void drawFocus(QPainter &painter, int x, int y) {
		x -= stoneSize / 2;
		y -= stoneSize / 2;

		Qt::BrushStyle bs = Qt::NoBrush;
		painter.setBrush(QBrush(Qt::blue,bs));
		painter.drawRect(x,y, stoneSize, stoneSize);
	}

	bool IsMouseInBoard(int x,int y);
	void convXY(int &posx, int &posy);

	void paintEvent(QPaintEvent *evt);
	void timerEvent(QTimerEvent *event);
	
	bool eventFilter(QObject *obj, QEvent *event);
	
	bool isBlackTurn();

public slots:
	void onConnectedServer();
	void readMessage();
	void connectionClosedByServer();
	void RecommandClick();

};
