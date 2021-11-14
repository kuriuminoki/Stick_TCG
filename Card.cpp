#include"DxLib.h"
#include"Card.h"
#include<stdio.h>
#include<random>
#include<algorithm>

using namespace std;


//カード
Card::Card(int pic_handle) {
	m_pic_handle = pic_handle;
	m_hold = false;
	m_back = false;
}

Card::~Card() {
	DeleteGraph(m_pic_handle);
}



//デッキ
Deck::Deck(string filename) {
	//デッキをロードする
	load_deck(filename);
	//デッキをシャッフルする
	shuffle();
}

Deck::~Deck() {
	//全てのカードを削除
	for (int i = 0; i < m_size; i++) {
		delete m_cardlist[i];
	}
}

void Deck::load_deck(string filename) {
	m_back_sum = 0;
	m_size = 0;
	//txtファイルからデータを入手
	int fp;
	char buff[256];
	fp = FileRead_open(filename.c_str());
	while(FileRead_eof(fp) == 0) {
		//カードの画像ファイル名を取得
		FileRead_gets(buff, 256, fp);
		string pass = "picture/card/";
		pass += buff;
		pass += ".png";
		int handle = LoadGraph(pass.c_str());
		if (handle == -1) { break; }
		//そのカードの枚数を取得
		FileRead_gets(buff, 256, fp);
		int size = atoi(buff);
		for (int i = 0; i < size; i++) {
			m_cardlist.push_back(new Card(handle));
			m_cards.push_back(m_size + i);
		}
		m_size += size;
	}
	FileRead_close(fp);
}

void Deck::shuffle() {
	vector<int> vec;
	int size = m_cards.size();
	//山札のキューをベクタに変換
	while (!m_cards.empty()) {
		vec.push_back(m_cards.front());
		m_cards.pop_front();
	}
	//ベクタをシャッフルしながらキューに入れる
	for (int i = 0; i < size; i++) {
		int r = GetRand(size - 1 - i) + i;
		m_cards.push_front(vec[r]);
		vec[r] = vec[i];
	}
}

//カードの裏表を変更
void Deck::back_card(int index, bool flag) {
	if (flag != m_cardlist[index]->get_back()) {
		if (flag) {
			m_back_sum++;
		}
		else {
			m_back_sum--;
		}
	}
	m_cardlist[index]->set_back(flag);
}


//ＡＡなどのカード管理
CardList::CardList() {
	m_now = -1;
}
//カードを追加
void CardList::push_card(int index) {
	if (m_now == -1) { m_now = index; }
	//else { m_right.push_back(index); }
	else { m_left.push_front(index); }
}
//m_nowを１つ右のカードに変更
void CardList::move_left() {
	if (m_right.empty()) { return; }
	m_left.push_back(m_now);
	m_now = m_right.front();
	m_right.pop_front();
}
//m_nowを１つ左のカードに変更
void CardList::move_right() {
	if (m_left.empty()) { return; }
	m_right.push_front(m_now);
	m_now = m_left.back();
	m_left.pop_back();
}
//カードの枚数を返す
int CardList::get_size() {
	if (m_now == -1) { return 0; }
	return 1 + m_left.size() + m_right.size();
}
//カードを外す
void CardList::pop_card() {
	if (m_now == -1) { return; }
	if (m_right.empty() && m_left.empty()) {
		m_now = -1;
	}
	else if (!m_right.empty()) {
		m_now = m_right.front();
		m_right.pop_front();
	}
	else {
		m_now = m_left.back();
		m_left.pop_back();
	}
}
