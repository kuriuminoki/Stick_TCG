#include"Create.h"
#include"Button.h"
#include"DxLib.h"
#include"Value.h"
#include"Control.h"
#include<fstream>
#include<sstream>

using namespace std;


//�t�@�C���̑��݊m�F ���݂���Ȃ�true
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

//��ʂɕ\������J�[�h�̉摜�����[�h����
void DeckCreate::set_now(int index) {
	DeleteGraph(m_card_handle);
	if (index == -1) { return; }
	load_card_handle(m_card_list[index], m_card_handle);
}

void DeckCreate::deck_check() {
	//�f�b�L�p
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
	//���X�g�p
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
	//�J�[�h�̃��X�g�ƃf�b�L
	load_card();//�J�[�h�̃��X�g�����[�h
	load_deck();//���Ƀt�@�C��������Ȃ烍�[�h
	m_list_now = 0;
	load_card_handle(m_card_list[m_list_now], m_list_handle);
	//�t�H���g
	m_font = CreateFontToHandle(NULL, 40, 3);
	//�{�^��
	m_right_handle = LoadGraph("picture/icon/�E���.png");
	m_left_handle = LoadGraph("picture/icon/�����.png");
	m_right_button = new Button("", 480, 250, 70, 400, LIGHT_YELLOW, RED, m_font, BLACK);
	m_left_button = new Button("", 50, 250, 70, 400, LIGHT_YELLOW, RED, m_font, BLACK);
	m_right_button->set_graph(m_right_handle, 2);
	m_left_button->set_graph(m_left_handle, 2);
	m_right_button2 = new Button("", 1160, 250, 70, 400, LIGHT_YELLOW, RED, m_font, BLACK);
	m_left_button2 = new Button("", 730, 250, 70, 400, LIGHT_YELLOW, RED, m_font, BLACK);
	m_right_button2->set_graph(m_right_handle, 2);
	m_left_button2->set_graph(m_left_handle, 2);
	deck_check();//���E�{�^���̍X�V
	m_edge_left_button = new Button("���[�ֈړ�", 670, 70, 250, 70, LIGHT_RED, RED, m_font, BLACK);
	m_edge_right_button = new Button("�E�[�ֈړ�", 1000, 70, 250, 70, LIGHT_RED, RED, m_font, BLACK);
	m_erase_button = new Button("1���O��", 150, 800, 300, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_add_button = new Button("1��������", 830, 800, 300, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
}

DeckCreate::~DeckCreate() {
	//�t�@�C���ւ̕ۑ�
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
	//�f�[�^�폜
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

//�f�b�L�����[�h����
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
		//�J�[�h�̉摜�t�@�C�������擾
		FileRead_gets(buff, 256, fp);
		str = buff;
		int num = 0;//�J�[�h�̉摜�t�@�C�����ɍ��v����z��̃C���f�b�N�X��ۑ�
		for (int i = 0; i < m_card_list.size(); i++) {
			if (str == m_card_list[i]) {
				num = i;
			}
		}
		//���̃J�[�h�̖������擾
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

//�J�[�h���X�g��p��
void DeckCreate::load_card() {
	string name;
	for (int i = 0; true; i++) {
		name = "no" + to_string(i + 1);
		string path = card_dir;
		path += name + ".png";
		if (!checkFileExistence(path)) { break; }
		m_card_list.push_back(name);
		//�G���Ⴂ�̉摜�����[�h
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
	DrawStringToHandle(650, 10, "�G�X�P�[�v�L�[�ŕۑ����ďI��", BLACK, m_font);
	//�J�[�h
	if (m_card_handle != -1) {
		int handle = m_card_handle;
		DrawRotaGraph(300, 450, 0.4, 0, handle, TRUE, FALSE);
		ostringstream deck_sum;
		deck_sum << "�f�b�L�̖����F" << m_deck_size << "/40";
		DrawStringToHandle(110, 150, deck_sum.str().c_str(), DARK_RED, m_font);
		ostringstream card_sum;
		card_sum << "���̃J�[�h�̖����F" << m_deck_now.second;
		DrawStringToHandle(110, 700, card_sum.str().c_str(), DARK_BLUE, m_font);
	}
	DrawRotaGraph(980, 450, 0.4, 0, m_list_handle, TRUE, FALSE);
	DrawStringToHandle(900, 150, m_card_list[m_list_now].c_str(), DARK_RED, m_font);
	//�{�^��
	m_right_button->draw(hand_x, hand_y);
	m_left_button->draw(hand_x, hand_y);
	m_erase_button->draw(hand_x, hand_y);
	m_right_button2->draw(hand_x, hand_y);
	m_left_button2->draw(hand_x, hand_y);
	m_add_button->draw(hand_x, hand_y);
	m_edge_right_button->draw(hand_x, hand_y);
	m_edge_left_button->draw(hand_x, hand_y);
	//�f�o�b�O�p
	//ostringstream os;
	//os << "hand_x�F" << hand_x << "hand_y:" << hand_y;
	//DrawStringToHandle(10, 10, os.str().c_str(), GetColor(255, 255, 255), m_font);
}

void DeckCreate::move_deck_right() {
	bool flag = false;
	if (m_right_button->get_flag() && hand_x < 1280 / 2 && m_round < 0) { flag = true; }
	if (m_right_button->overlap(hand_x, hand_y) && left_click() == 1) { flag = true; }
	if (!flag) { return; }
	m_deck_right.push_front(m_deck_now);
	m_deck_now = m_deck_left.back();
	set_now(m_deck_now.first);//�摜���[�h
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
	set_now(m_deck_now.first);//�摜���[�h
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

//�s�̗p
void DeckCreate::deck_adjust() {
	vector<pair<int, int> > new_cards;
	vector<pair<int, int> > prev_cards;
	int now = m_deck_now.first;//�����Ă�J�[�h
	//�܂���vector�ɕϊ�
	while (!m_deck_left.empty()) {
		prev_cards.push_back(m_deck_left.front());
		m_deck_left.pop_front();
	}
	prev_cards.push_back(m_deck_now);
	while (!m_deck_right.empty()) {
		prev_cards.push_back(m_deck_right.back());
		m_deck_right.pop_back();
	}

	//�d��������
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