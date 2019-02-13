#include "Game.h"
#include <qline.h>
#include <QVBoxLayout>
#include <windows.h>
#include <QThread>


void Game::RecommandClick() {

}

Game::Game(QWidget *parent)
	: QWidget(parent)
{

	ui.setupUi(this);

	qApp->installEventFilter(this);
	
	QObject::connect(ui.GetRecommend, SIGNAL(clicked()), this, SLOT(RecommandClick()));

	this->setMouseTracking(true);
	this->whiteTime = 50;
	this->blackTime = 50;
	this->timerID = startTimer(1000);
}
void Game::moveLogInit() {
	memset(moveLogs, -1, sizeof(moveLogs));
	moveCnt = 0;
}
void Game::addMoveLog(int x, int y) {
	QString buff((char)(97 + x));
	buff += QString::number(y + 1);
	strcat(moveLogs,buff.toLocal8Bit());
	//QMessageBox msgbox;
	//msgbox.setText(QString(moveLogs));
	//msgbox.exec();
}
Game::Game(bool isSingle, bool isAI, bool isPlayerFirst, QString serverIP, int port, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	// ->setStyleSheet("background-color: red");

	//serverIP = "113.30.24.43";

	qApp->installEventFilter(this);
	this->timerID = startTimer(1000);
	
	this->isSingle = isSingle;
	this->isAI = isAI;
	if (isSingle) {
		setTimeout(50, 50);
		//single play
		if (isAI) {
			hInst = LoadLibrary(L"edax.dll");
			if (GetLastError()!=0) {
				QMessageBox msgbox;
				msgbox.setText(QString::fromLocal8Bit("dll 로드에 실패했습니다"));
				msgbox.exec();
			}
			//with ai
			if (isPlayerFirst) {
				resetMap();
				chkAvailables(1, true);
				BlackPlyaerType = 0;
				WhitePlayerType = 2;
				currentTurn = true;
				isGameStart = true;
			}
			else {
				resetMap();
				chkAvailables(1, false);
				BlackPlyaerType = 2;
				WhitePlayerType = 0;
				currentTurn = true;
				isGameStart = true;
				moveGame(3, 2);
			}
		}
		else {
			//with man
			resetMap();
			chkAvailables(1, true);
			BlackPlyaerType = 0;
			WhitePlayerType = 0;
			currentTurn = true;
			isGameStart = true;
		}
	}
	else {
		//multiplay
		if (isAI) {
			hInst = LoadLibrary(L"edax.dll");
			if (GetLastError() != 0) {
				QMessageBox msgbox;
				msgbox.setText(QString::fromLocal8Bit("dll 로드에 실패했습니다"));
				msgbox.exec();
			}
			NetworkAIflag = true;
		}
		else {
			NetworkAIflag = false;
		}
		
		connect(&tcpSocket, SIGNAL(connected()), this, SLOT(onConnectedServer()));
		connect(&tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
		connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));

		tcpSocket.connectToHost(serverIP,port);
		this->setWindowTitle(QString::fromLocal8Bit("서버 접속 시도"));
	}
}

void Game::onConnectedServer() {
	this->setWindowTitle(QString::fromLocal8Bit("서버 접속 성공"));
}
void Game::readMessage() {
	QDataStream packet(&tcpSocket);

	while (true) {
		int size = tcpSocket.bytesAvailable();
		if (PacketSize == 0) {
			if (tcpSocket.bytesAvailable() > sizeof(qint32)) {
				packet >> PacketSize;
			}
		}
		else if (tcpSocket.bytesAvailable() >= PacketSize) {
			
			QString Buffer(tcpSocket.read(PacketSize));
			
			/*int thisPlayerColor;
			if (WhitePlayerType == 1) {
				thisPlayerColor = 1;  //black
			}
			else {
				thisPlayerColor = 2;  //white
			}
			QMessageBox a;
			a.setText( QString::number(thisPlayerColor)+ "  "+Buffer);
			a.exec();*/
			
			QJsonDocument jsonDoc = QJsonDocument::fromJson(Buffer.toUtf8());
			QJsonObject jsonObj = jsonDoc.object();

			ServerPacketReceived(jsonObj);

			PacketSize = 0;
			if (tcpSocket.bytesAvailable() == 0) {
				break;
			}
		}
	}
}
void Game::connectionClosedByServer() {
	this->setWindowTitle(QString::fromLocal8Bit("서버와의 연결이 끊켰습니다."));
}


int Game::getThisPlayerColor() {
	if (WhitePlayerType == 1) {
		return 1;  //black
	}
	else if(BlackPlyaerType == 1){
		return 2;  //white
	}
}

void Game::ServerPacketReceived(QJsonObject data) {
	int thisPlayerColor = getThisPlayerColor();

	switch (data["type"].toInt()) {
	case 0: {  //ready
		break;
	}
	case 1: {  //START
		currentTurn = true;
		resetMap();

		if (data["color"].toInt() == 1) {
			BlackPlyaerType = NetworkAIflag ? 2 : 0;
			WhitePlayerType = 1;
			isGameStart = true;
			setTimeout(30, 30);
			
			if (isAI) {
				//AddrToXY(getAImove(), aiX, aiY);
				moveGame(3, 2);
				sendPutPacket(3, 2);
			}
			else {
				chkAvailables(1, true);
			}

			this->update();
			qApp->processEvents();
		}
		else {
			BlackPlyaerType = 1;
			WhitePlayerType = NetworkAIflag ? 2 : 0;
			isGameStart = true;
			setTimeout(30, 30);
		}
		break;
	}
	case 2: {  //TURN
		lastTimeout = data["time_limit"].toInt();
		setTimeout(data["time_limit"].toInt(), data["time_limit"].toInt());
		QJsonArray other_put = data["opponent_put"].toArray();

		if (other_put.size() == 2) {
			moveGame(other_put[0].toInt(), other_put[1].toInt());
			this->update();
			qApp->processEvents();
		}

		break;
	}
	case 3: { //ACCEPT
		setOpponentTimeout(data["opponent_time_limit"].toInt());
		break;
	}
	case 5: { //NOPOINT
		QJsonArray other_put = data["opponent_put"].toArray();
		setTimeout(lastTimeout,lastTimeout);
		if (other_put.size() == 2) {
			moveGame(other_put[0].toInt(), other_put[1].toInt());
			this->update();
			qApp->processEvents();
		}
		break;
	}
	case 6: {
		QJsonArray other_put = data["opponent_put"].toArray();

		if (other_put.size() == 2) {
			moveGame(other_put[0].toInt(), other_put[1].toInt());
			this->update();
			qApp->processEvents();
		}

		bool isWin = data["result"].toInt();

		switch (data["reason"].toInt()) {
		case 3:
			if (isWin) {
				ShowGameResult(getThisPlayerColor());
			}
			else {
				ShowGameResult(flipColor(getThisPlayerColor()));
			}
			break;
		case 4:
			if (isWin) {
				ShowGameResult(getThisPlayerColor() +2);
			}
			else {
				ShowGameResult(flipColor(getThisPlayerColor()) +2);
			}
			break;
		default:
			ShowGameResult();
			break;
		}
		break;
	}
	}
}
void Game::setOpponentTimeout(int time) {
	if (WhitePlayerType == 1) {
		whiteTime = time;
	}
	else if(BlackPlyaerType == 1){
		blackTime = time;  //white
	}
}
void Game::sendPutPacket(int x, int y) {
	setTimeout(30, 30);

	QByteArray sendBuf;
	QDataStream out(&sendBuf, QIODevice::WriteOnly);

	QJsonArray pos;
	pos.push_back(x);
	pos.push_back(y);

	QJsonObject sendJsonBuf;
	sendJsonBuf["type"] = 0;
	sendJsonBuf["point"] = pos;

	QJsonDocument jsonDoc(sendJsonBuf);
	QString strJson(jsonDoc.toJson(QJsonDocument::Compact));

	//out << quint32(strJson.toUtf8().length());
	out << strJson.toUtf8();

	tcpSocket.write(sendBuf);

}


void Game::paintEvent(QPaintEvent *evt) { //drawMap
	QPainter painter(this);
	painter.setPen(QPen(Qt::black));
	//painter.drawLine(10, 10, 100, 10);


	int sx = this->sx, sy = this->sy;
	int boxSize = this->boxSize;

	for (int i = 0; i < 9; i++) {    //drawmap
		painter.drawLine(sx, sy + (boxSize / 8)*i, sx + boxSize, sy + (boxSize / 8)*i);
		painter.drawLine(sx + (boxSize / 8)*i, sy, sx + (boxSize / 8)*i, sy + boxSize);
	}


	for (int i = 0; i < 8; i++) {   //draw stones
		for (int j = 0; j < 8; j++) {
			int x = sx + (boxSize / 8)*i + boxSize / 8 / 2;
			int y = sy + (boxSize / 8)*j + boxSize / 8 / 2;
			switch (map[i][j]) {
			case 0:   //none
				break;
			case 1:   //black
				drawBlack(painter, x, y);
				break;
			case 2:   //white
				drawWhite(painter, x, y);
				break;
			case 3:   //available
				drawAvailable(painter, x, y);
				break;
			}
		}
	}
	QFont fontScore = ui.BlackScore->font();
	fontScore.setPointSize(36);

	ui.BlackScore->setText(QString::number(getPlayerStones(1)));
	ui.BlackScore->setFont(fontScore);
	ui.WhiteScore->setText(QString::number(getPlayerStones(2)));
	ui.WhiteScore->setFont(fontScore);

	if (focusPosition != -1) {    //draw focus
		int x = sx + (boxSize / 8)*(focusPosition % 8) + boxSize / 8 / 2;  //1 dimension to 2 dimension
		int y = sy + (boxSize / 8)*(focusPosition/8) + boxSize / 8 / 2;
		drawFocus(painter,x,y);
	}

	
}


void Game::timerEvent(QTimerEvent *event) {
	if (!isGameStart)
		return;
	//if (aiTurn) {
	//	aiTurn = false;
	//	moveGame(aiX,aiY);
	//}
	if (isBlackTurn()) {
		if (blackTime == 0) {
			//killTimer(timerID);
			if (isSingle) {
				ShowGameResult(2);
			}
		}
		else {
			blackTime--;
		}
	}
	else {
		if (whiteTime == 0) {
			//killTimer(timerID);
			if (isSingle) {
				ShowGameResult(1);
			}
		}
		else {
			whiteTime--;
		}
	}
	//map[blackTime / 8 - 1][blackTime % 8] = 1;
	ui.BlackTime->setText(QString::number(blackTime));
	ui.WhiteTime->setText(QString::number(whiteTime));

}
int Game::getMap(int x, int y) {
	if ((0 <= x && x <= 7) && (0 <= y && y <= 7)) {
		return map[x][y];
	}
	else {
		return -1;
	}
}
bool Game::IsMouseInBoard(int x, int y) {
	return (sx <= x && x <= sx + boxSize) && (sy <= y && y <= sy + boxSize);
}
void Game::convXY(int &posx,int &posy) {
	
	if (IsMouseInBoard(posx, posy)) {
		posx -= sx; posx -= posx % (boxSize / 8);
		posy -= sy; posy -= posy % (boxSize / 8);

		posx = posx / (boxSize / 8);
		posy = posy / (boxSize / 8);
	}else {
		posx = -1;
		posy = -1;
	}
	
}

bool Game::eventFilter(QObject *obj, QEvent *event)
{

	switch(event->type())
	{
	case QEvent::MouseMove: {
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

		int x = mouseEvent->pos().x();
		int y = mouseEvent->pos().y();

		convXY(x, y);
		if (getMap(x, y) == 3) {
			focusPosition = y * 8 + x;
		}
		else {
			focusPosition = -1;
		}

		this->update();
		break;
	}
	case QEvent::MouseButtonRelease: {
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

		int x = mouseEvent->pos().x();
		int y = mouseEvent->pos().y();

		convXY(x, y);
		if (getMap(x, y) == 3) {
			//QMessageBox msgbox;
			//msgbox.setText("asdf");
			//msgbox.exec();
			if (!isSingle) {
				sendPutPacket(x, y);
			}
			moveGame(x,y);
			
			focusPosition = -1;
		}

		this->update();
		break;
	}
	}

	return false;
}

bool Game::setMap(int x, int y, int value) {
	if ((0 <= x && x <= 7) && (0 <= y && y <= 7)) {
		map[x][y] = value;
		this->update();
		return true;
	}
	else {
		return false;
	}

}



bool Game::map_dfs(int x,int y,int d,int color,bool set) {
	int value = getMap(x,y);
	if (value == -1 || value == 3 || value == 0) {
		return false;
	}

	if (value == color) {
		return true;
	}

	if (map_dfs(x + direction[d][0], y + direction[d][1], d, color, set)) {
		if (set) {
			map[x][y] = color;  //flip color
		}
		return true;
	}
	return false;
}

bool Game::chkAvailable(int x, int y, int color,bool set) {
	bool result = false;
	for (int i = 0; i < 8; i++) {
		if (getMap(x + direction[i][0], y + direction[i][1]) != color && map_dfs(x + direction[i][0], y + direction[i][1], i, color, set)) {
			if (set == false)
				return true;
			else
				result = true;
		}
	}
	return result;
}

bool Game::chkAvailables(int color, bool set) {
	bool result = false;
	removeAvailable();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (map[i][j] == 0) {
				if (chkAvailable(i,j,color)) {
					if (set) {
						map[i][j] = 3;
						result = true;
					}
					else {
						return true;
					}
				}
			}
		}
	}
	return result;
}
bool Game::chkAvailables(bool turn, bool set) {
	return chkAvailables(turnToColor(turn), set);
}

void Game::removeAvailable() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (map[i][j] == 3)
				map[i][j] = 0;
		}
	}
}

int Game::turnToColor(bool turn) {
	return !turn + 1;
}
int Game::turnToPlayer(bool turn) {
	if (turn) {
		return BlackPlyaerType;
	}
	else {
		return WhitePlayerType;
	}
}
int Game::flipColor(int color) {
	return color == 1 ? 2 : 1;
}

void Game::AddrToXY(int addr, int &x, int &y) {
	x = addr % 8;
	y = addr / 8;
}
int Game::xyToAddr(int x, int y) {
	return y * 8 + x;
}

int Game::getAImove() {
	
	PVOID pvoid = GetProcAddress(hInst, "printTest");
	int(__cdecl* printTest)(char *, int) = (int(__cdecl*)(char *, int))pvoid;
	int result = printTest(moveLogs, moveCnt);
	//QMessageBox msgbox;
	//msgbox.setText(QString::number(result));
	//msgbox.exec();
	return result;
}

/*void Game::moveGame(int x, int y) {
	int currentColor = turnToColor(currentTurn);
	setStone(x,y,currentColor);
	addMoveLog(x,y);

	if (isSingle) {
		setTimeout(50,50);
	}

	removeAvailable();

	currentTurn = !currentTurn;
	int thisPlayerType = turnToPlayer(currentTurn);

	
	//if (turnToPlayer(currentTurn)==0) { // next turn is human?
	if (!chkAvailables(currentTurn, turnToPlayer(currentTurn) ==0)) {  // no avaliable
		currentTurn = !currentTurn;
		addMoveLog(0,8); // PASS
		if (!chkAvailables(currentTurn, turnToPlayer(currentTurn) == 0)) {  // both of players cannot move ANYMORE
			if (isSingle) {
				ShowGameResult();
			}
		}
		else if (isAI &&  turnToPlayer(currentTurn) == 2) {
			//currentTurn = !currentTurn;
			AddrToXY(getAImove(), aiX, aiY);
			moveGame(aiX, aiY);
			chkAvailables(!currentTurn, turnToPlayer(!currentTurn) == 0);
		}
	}
	else {
		if (isAI && turnToPlayer(currentTurn) == 2) {
			AddrToXY(getAImove(), aiX, aiY);
			moveGame(aiX, aiY);
			chkAvailables(!currentTurn, turnToPlayer(!currentTurn) == 0);
		}
	}
	
	//}
	this->update();
}*/
void Game::moveGame(int x, int y) {
	if(isSingle){
		setTimeout(50, 50);
	}

	removeAvailable();
	
	//QThread::msleep(200);

	if (chkAvailable(x,y,turnToColor(currentTurn),true)) {
		setMap(x,y, turnToColor(currentTurn));
		addMoveLog(x,y);
		this->update();
		qApp->processEvents();

		if (chkAvailables(!currentTurn, turnToPlayer(!currentTurn) == 0)) {
			currentTurn = !currentTurn;
			if (isAI && turnToPlayer(currentTurn) == 2) {
				AddrToXY(getAImove(), aiX, aiY);
				if (!isSingle) {
					sendPutPacket(aiX,aiY);
				}
				moveGame(aiX,aiY);

			}
		}
		else {
			if (chkAvailables(currentTurn, turnToPlayer(currentTurn) == 0)) {
				if (isAI && turnToPlayer(currentTurn) == 2) {
					AddrToXY(getAImove(), aiX, aiY);
					if (!isSingle) {
						sendPutPacket(aiX, aiY);
					}
					moveGame(aiX, aiY);
				}
			}
			else {
				if (isSingle) {
					ShowGameResult(0);
				}
			}
		}
	}
	else {
		currentTurn = !currentTurn;
	}
}

int Game::getPlayerStones(int color) {
	int result = 0;
	for (int i = 0; i < 64; i++) {
		if ( ((int *)map)[i] == color)
			result++;
	}		
	return result;
}
int Game::getPlayerStones(bool turn) {
	return getPlayerStones(turnToColor(turn));
}


void Game::ShowGameResult(int type) { // Win Effect on here
	QMessageBox msgbox;

	int scoreResult = getScoreGap();
	
	
	if (scoreResult > 0) {
		msgbox.setText(QString::fromLocal8Bit("흑돌이 승리했습니다."));
	}
	else if(scoreResult < 0){
		msgbox.setText(QString::fromLocal8Bit("백돌이 승리했습니다."));
	}
	else {
		msgbox.setText(QString::fromLocal8Bit("비겼습니다."));
	}

	switch (type) {
	case 1:
		msgbox.setText(QString::fromLocal8Bit("백돌의 시간 초과로 흑돌이 승리"));
		break;
	case 2:
		msgbox.setText(QString::fromLocal8Bit("흑돌의 시간 초과로 백돌이 승리"));
		break;
	case 3:
		msgbox.setText(QString::fromLocal8Bit("백돌의 착수 오류로 흑돌이 승리"));
		break;
	case 4:
		msgbox.setText(QString::fromLocal8Bit("흑돌의 착수 오류로 백돌이 승리"));
		break;
	}
	
	isGameStart = false;
	removeAvailable();
	msgbox.exec();
}

int Game::getScoreGap() {
	int result = 0;
	for (int i = 0; i < 64; i++) {
		switch (((int *)map)[i]) {
		case 1:
			result++;
			break;
		case 2:
			result--;
			break;
		default:
			break;
		}
	}
	return result;
}

void Game::setStone(int x, int y,int color) {
	if (chkAvailable(x, y, color, false)) {
		setMap(x, y, color);
		chkAvailable(x, y, color, true);
	}

}

void Game::resetMap() {
	memset(map,0,sizeof(map));
	map[3][3] = 2;
	map[3][4] = 1;
	map[4][3] = 1;
	map[4][4] = 2;
}

bool Game::isBlackTurn()
{
	return this->currentTurn;
}

Game::~Game()
{
	FreeLibrary(hInst);
}

