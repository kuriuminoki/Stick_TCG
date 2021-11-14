#include"Create.h"
#include"Button.h"
#include"DxLib.h"
#include"Value.h"
#include"Control.h"
#include<fstream>
#include<sstream>

using namespace std;


//ファイルの存在確認 存在するならtrue
bool checkFileExistence(const std::string& str)
{
	std::ifstream ifs(str);
	return ifs.is_open();
}

const char* const card_dir = "picture/card/";
void load_card_handle(string name, int& handle) {
	name = card_dir + name + ".png";
	handle = LoadGraph(name.c_str());
}

//画面に表示するカードの画像をロードする
void DeckCreate::set_now(int index) {
	DeleteGraph(m_card_handle);
	if (index == -1) { return; }
	load_card_handle(m_card_list[index], m_card_handle);
}

void DeckCreate::deck_check() {
	//デッキ用
	if (m_deck_left.empty()) {
		m_right_button->change_flag(false, DARK_YELLOW);
	}
	else {
		m_right_button->change_flag(true, LIGHT_YELLOW);
	}
	if (m_deck_right.empty()) {
		m_left_button->change_flag(false, DARK_YELLOW);
	}
	else {
		m_left_button->change_flag(true, LIGHT_YELLOW);
	}
	//リスト用
	if (m_list_now == m_card_list.size() - 1) {
		m_right_button2->change_flag(false, DARK_YELLOW);
	}
	else {
		m_right_button2->change_flag(true, LIGHT_YELLOW);
	}
	if (m_list_now == 0) {
		m_left_button2->change_flag(false, DARK_YELLOW);
	}
	else {
		m_left_button2->change_flag(true, LIGHT_YELLOW);
	}
}

DeckCreate::DeckCreate(string filename) {
	m_filename = filename;
	m_card_handle = -1;
	m_deck_now.first = -1;
	m_deck_now.second = 0;
	m_deck_size = 0;
	//カードのリストとデッキ
	load_card();//カードのリストをロード
	load_deck();//既にファイルがあるならロード
	m_list_now = 0;
	load_card_handle(m_card_list[m_list_now], m_list_handle);
	//フォント
	m_font = CreateFontToHandle(NULL, 40, 3);
	//ボタン
	m_right_handle = LoadGraph("picture/icon/右矢印.png");
	m_left_handle = LoadGraph("picture/icon/左矢印.png");
	m_right_button = new Button("", 480, 250, 70, 400, LIGHT_YELLOW, RED, m_font, BLACK);
	m_left_button = new Button("", 50, 250, 70, 400, LIGHT_YELLOW, RED, m_font, BLACK);
	m_right_button->set_graph(m_right_handle, 2);
	m_left_button->set_graph(m_left_handle, 2);
	m_right_button2 = new Button("", 1160, 250, 70, 400, LIGHT_YELLOW, RED, m_font, BLACK);
	m_left_button2 = new Button("", 730, 250, 70, 400, LIGHT_YELLOW, RED, m_font, BLACK);
	m_right_button2->set_graph(m_right_handle, 2);
	m_left_button2->set_graph(m_left_handle, 2);
	deck_check();//左右ボタンの更新
	m_edge_left_button = new Button("左端へ移動", 670, 70, 250, 70, LIGHT_RED, RED, m_font, BLACK);
	m_edge_right_button = new Button("右端へ移動", 1000, 70, 250, 70, LIGHT_RED, RED, m_font, BLACK);
	m_erase_button = new Button("1枚外す", 150, 800, 300, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_add_button = new Button("1枚加える", 830, 800, 300, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
}

DeckCreate::~DeckCreate() {
	//ファイルへの保存
	string file_path = "deck/" + m_filename;
	file_path += ".txt";
	ofstream writing_file;
	writing_file.open(file_path);
	string name;
	int sum;
	while (!m_deck_right.empty()) {
		name = m_card_list[m_deck_right.back().first];
		sum = m_deck_right.back().second;
		writing_file << name << endl;
		writing_file << sum << endl;
		m_deck_right.pop_back();
	}
	name = m_card_list[m_deck_now.first];
	sum = m_deck_now.second;
	writing_file << name << endl;
	writing_file << sum << endl;
	while (!m_deck_left.empty()) {
		name = m_card_list[m_deck_left.back().first];
		sum = m_deck_left.back().second;
		writing_file << name << endl;
		writing_file << sum << endl;
		m_deck_left.pop_back();
	}

	writing_file.close();
	//データ削除
	DeleteFontToHandle(m_font);
	DeleteGraph(m_right_handle);
	DeleteGraph(m_left_handle);
	DeleteGraph(m_list_handle);
	DeleteGraph(m_card_handle);
	delete m_right_button;
	delete m_left_button;
	delete m_erase_button;
	delete m_right_button2;
	delete m_left_button2;
	delete m_add_button;
	delete m_edge_left_button;
	delete m_edge_right_button;
	InitGraph();
}

//デッキをロードする
bool DeckCreate::load_deck() {
	string file_path = "deck/" + m_filename;
	file_path += ".txt";
	int fp = FileRead_open(file_path.c_str());
	if (fp == 0) {
		return false;
	}
	char buff[256];
	while (FileRead_eof(fp) == 0) {
		string str;
		//カードの画像ファイル名を取得
		FileRead_gets(buff, 256, fp);
		str = buff;
		int num = 0;//カードの画像ファイル名に合致する配列のインデックスを保存
		for (int i = 0; i < m_card_list.size(); i++) {
			if (str == m_card_list[i]) {
				num = i;
			}
		}
		//そのカードの枚数を取得
		FileRead_gets(buff, 256, fp);
		int sum = atoi(buff);
		m_deck_size += sum;
		if (m_deck_now.first == -1) {
			m_deck_now = make_pair(num, sum);
			set_now(num);
		}
		else {
			m_deck_left.push_front(make_pair(num, sum));
		}
	}
	FileRead_close(fp);
	return true;
}

//カードリストを用意
void DeckCreate::load_card() {
	string name;
	for (int i = 0; true; i++) {
		name = "no" + to_string(i + 1);
		string path = card_dir;
		path += name + ".png";
		if (!checkFileExistence(path)) { break; }
		m_card_list.push_back(name);
		//絵柄違いの画像をロード
		name += "_";
		for (int j = 2; true; j++) {
			string new_name = name + to_string(j);
			path = card_dir;
			path += new_name;
			path += ".png";
			if (!checkFileExistence(path)) { break; }
			m_card_list.push_back(new_name);
		}
	}
}

bool DeckCreate::play() {
	GetMousePoint(&hand_x, &hand_y);
	m_round = GetMouseWheelRotVol();
	move_deck_right();
	move_deck_left();
	erase_deck();
	move_list_right();
	move_list_left();
	move_list_edge();
	add_deck();
	return false;
}

void DeckCreate::draw() {
	DrawBox(-1, -1, 1280, 1024, GRAY, TRUE);
	DrawBox(635, -1, 645, 1024, YELLOW, TRUE);
	DrawStringToHandle(10, 10, m_filename.c_str(), BLACK, m_font);
	DrawStringToHandle(650, 10, "エスケープキーで保存して終了", BLACK, m_font);
	//カード
	if (m_card_handle != -1) {
		int handle = m_card_handle;
		DrawRotaGraph(300, 450, 0.4, 0, handle, TRUE, FALSE);
		ostringstream deck_sum;
		deck_sum << "デッキの枚数：" << m_deck_size << "/40";
		DrawStringToHandle(110, 150, deck_sum.str().c_str(), DARK_RED, m_font);
		ostringstream card_sum;
		card_sum << "このカードの枚数：" << m_deck_now.second;
		DrawStringToHandle(110, 700, card_sum.str().c_str(), DARK_BLUE, m_font);
	}
	DrawRotaGraph(980, 450, 0.4, 0, m_list_handle, TRUE, FALSE);
	DrawStringToHandle(900, 150, m_card_list[m_list_now].c_str(), DARK_RED, m_font);
	//ボタン
	m_right_button->draw(hand_x, hand_y);
	m_left_button->draw(hand_x, hand_y);
	m_erase_button->draw(hand_x, hand_y);
	m_right_button2->draw(hand_x, hand_y);
	m_left_button2->draw(hand_x, hand_y);
	m_add_button->draw(hand_x, hand_y);
	m_edge_right_button->draw(hand_x, hand_y);
	m_edge_left_button->draw(hand_x, hand_y);
	//デバッグ用
	//ostringstream os;
	//os << "hand_x：" << hand_x << "hand_y:" << hand_y;
	//DrawStringToHandle(10, 10, os.str().c_str(), GetColor(255, 255, 255), m_font);
}

void DeckCreate::move_deck_right() {
	bool flag = false;
	if (m_right_button->get_flag() && hand_x < 1280 / 2 && m_round < 0) { flag = true; }
	if (m_right_button->overlap(hand_x, hand_y) && left_click() == 1) { flag = true; }
	if (!flag) { return; }
	m_deck_right.push_front(m_deck_now);
	m_deck_now = m_deck_left.back();
	set_now(m_deck_now.first);//画像ロード
	m_deck_left.pop_back();
	deck_check();
}

void DeckCreate::move_deck_left() {
	bool flag = false;
	if (m_left_button->get_flag() && hand_x < 1280 / 2 && m_round > 0) { flag = true; }
	if (m_left_button->overlap(hand_x, hand_y) && left_click() == 1) { flag = true; }
	if (!flag) { return; }
	m_deck_left.push_back(m_deck_now);
	m_deck_now = m_deck_right.front();
	set_now(m_deck_now.first);//画像ロード
	m_deck_right.pop_front();
	deck_check();
}

void DeckCreate::erase_deck() {
	if (!m_erase_button->overlap(hand_x, hand_y) || left_click() != 1) { return; }
	if (m_deck_now.second == 0) { return; }
	m_deck_now.second--; m_deck_size--;
	if (m_deck_now.second == 0) {
		if (!m_deck_left.empty()) {
			m_deck_now = m_deck_left.back();
			m_deck_left.pop_back();
			deck_check();
		}
		else if (!m_deck_right.empty()) {
			m_deck_now = m_deck_right.front();
			m_deck_right.pop_front();
			deck_check();
		}
		else {
			m_deck_now.first = -1;
		}
		set_now(m_deck_now.first);
	}
	if (m_deck_size == 0) { m_erase_button->change_flag(false, DARK_BLUE); }
}

void DeckCreate::move_list_right() {
	bool flag = false;
	if (m_right_button2->get_flag() && hand_x > 1280 / 2 && m_round < 0) { flag = true; }
	if (m_right_button2->overlap(hand_x, hand_y) && left_click() == 1) { flag = true; }
	if (!flag) { return; }
	m_list_now++;
	deck_check();
	load_card_handle(m_card_list[m_list_now], m_list_handle);
}

void DeckCreate::move_list_left() {
	bool flag = false;
	if (m_left_button2->get_flag() && hand_x > 1280 / 2 && m_round > 0) { flag = true; }
	if (m_left_button2->overlap(hand_x, hand_y) && left_click() == 1) { flag = true; }
	if (!flag) { return; }
	m_list_now--;
	deck_check();
	load_card_handle(m_card_list[m_list_now], m_list_handle);
}

void DeckCreate::move_list_edge() {
	if (left_click() != 1) { return; }
	if (m_edge_left_button->overlap(hand_x, hand_y)) {
		m_list_now = 0;
	}
	else if (m_edge_right_button->overlap(hand_x, hand_y)) {
		m_list_now = m_card_list.size() - 1;
	}
	deck_check();
	load_card_handle(m_card_list[m_list_now], m_list_handle);
}

void DeckCreate::add_deck() {
	if (!m_add_button->overlap(hand_x, hand_y) || left_click() != 1) { return; }
	if (m_deck_now.first == -1) { m_deck_now = make_pair(m_list_now, 1); }
	else {
		if (m_deck_now.first == m_list_now) {
			m_deck_now.second++;
		}
		else {
			m_deck_right.push_front(m_deck_now);
			m_deck_now = make_pair(m_list_now, 1);
		}
	}
	m_deck_size++;
	deck_check();
	set_now(m_deck_now.first);
	m_erase_button->change_flag(true, LIGHT_BLUE);
}

//不採用
void DeckCreate::deck_adjust() {
	vector<pair<int, int> > new_cards;
	vector<pair<int, int> > prev_cards;
	int now = m_deck_now.first;//今見てるカード
	//まずはvectorに変換
	while (!m_deck_left.empty()) {
		prev_cards.push_back(m_deck_left.front());
		m_deck_left.pop_front();
	}
	prev_cards.push_back(m_deck_now);
	while (!m_deck_right.empty()) {
		prev_cards.push_back(m_deck_right.back());
		m_deck_right.pop_back();
	}

	//重複を合体
	for (int i = 0; i < prev_cards.size(); i++) {
		bool flag = false;
		for (int j = 0; j < new_cards.size(); j++) {
			if (new_cards[j].first == prev_cards[i].first) {
				new_cards[j].second += prev_cards[i].second;
				flag = true;
				break;
			}
		}
		if (!flag) { new_cards.push_back(prev_cards[i]); }
	}

}