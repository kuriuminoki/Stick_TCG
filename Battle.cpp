#include"Battle.h"
#include"Player.h"
#include"Button.h"
#include"Control.h"
#include"DxLib.h"
#include<algorithm>

using namespace std;

BattleField::BattleField(string deckname1, string deckname2) {
	//ボタン
	int LIGHT_GREEN = GetColor(150, 255, 150);
	int GREEN = GetColor(0, 255, 0);
	int BLACK = GetColor(0, 0, 0);
	m_font = CreateFontToHandle(NULL, 40, 3);
	m_change_button = new Button("プレイヤー切り替え", 850, 900, 410, 100, LIGHT_GREEN, GREEN, m_font, BLACK);
	//プレイヤー
	deckname1 = "deck/" + deckname1;
	deckname1 += ".txt";
	deckname2 = "deck/" + deckname2;
	deckname2 += ".txt";
	m_player[0] = new Player(deckname1.c_str());
	m_player[1] = new Player(deckname2.c_str());
	m_turn = false;
}

BattleField::~BattleField() {
	delete m_player[0];
	delete m_player[1];
	delete m_change_button;
	DeleteFontToHandle(m_font);
	InitGraph();
}

bool BattleField::play() {
	GetMousePoint(&hand_x, &hand_y);
	int input_mouse = GetMouseWheelRotVol();
	if (left_click() == 1) {
		if (m_change_button->overlap(hand_x, hand_y)) {
			m_turn = !m_turn;
		}
	}
	m_player[m_turn]->play(input_mouse);
	return false;
}

void move_sheet(int& dx, int& dy, double& dex, double& round) {
	int key = control_move();
	int key2 = control_ex();
	if (key == 1) {
		dx--;
	}
	else if (key == 2) {
		dx++;
	}
	else if (key == 3) {
		dy--;
	}
	else if (key == 4) {
		dy++;
	}

	if (key2 == 1) {
		dex -= 0.01;
	}
	else if (key2 == 2) {
		dex += 0.01;
	}

	if (control_c() == 1) {
		if (round < 2 * 3.14) { round += 0.5; }
		if (round >= 2.0) { round = 0; }
	}

	if (right_click() == 1) {
		dx = 0; dy = 0; dex = 0.0; round = 0.0;
	}
}

int haikei = GetColor(150, 150, 150);
int LIGHT_YELLOW2 = GetColor(255, 255, 150);
int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
double dex1 = 0.0, dex2 = 0.0;
double round1 = 0, round2 = 0;
void BattleField::draw(int sheet1, int sheet2) {

	int wide, height;
	DrawBox(-1, -1, 1281, 750, haikei, TRUE);
	if (!m_turn) {
		move_sheet(dx1, dy1, dex1, round1);
		GetGraphSize(sheet1, &wide, &height);
		double ex = min(1280.0 / wide, 750.0 / height);
		DrawRotaGraph(1280 / 2 + dx1, 750 / 2 + dy1, ex + dex1, round1*3.14159, sheet1, TRUE, FALSE);
		DrawBox(-1, -1, 250, 50, LIGHT_YELLOW2, TRUE);
		DrawStringToHandle(5, 5, "プレイヤーＡ", GetColor(0, 0, 100), m_font);
	}
	else {
		move_sheet(dx2, dy2, dex2, round2);
		GetGraphSize(sheet2, &wide, &height);
		double ex = min(1280.0 / wide, 750.0 / height);
		DrawRotaGraph(1280 / 2 + dx2, 750 / 2 + dy2, ex + dex2, round2*3.14159, sheet2, TRUE, FALSE);
		DrawBox(-1, -1, 250, 50, LIGHT_YELLOW2, TRUE);
		DrawStringToHandle(5, 5, "プレイヤーＢ", GetColor(200, 0, 0), m_font);
	}
	m_player[m_turn]->draw();
	m_change_button->draw(hand_x, hand_y);
}