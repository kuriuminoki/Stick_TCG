#include"DxLib.h"
#include"Card.h"
#include<stdio.h>
#include<random>
#include<algorithm>

using namespace std;


//�J�[�h
Card::Card(int pic_handle) {
	m_pic_handle = pic_handle;
	m_hold = false;
	m_back = false;
}

Card::~Card() {
	DeleteGraph(m_pic_handle);
}



//�f�b�L
Deck::Deck(string filename) {
	//�f�b�L�����[�h����
	load_deck(filename);
	//�f�b�L���V���b�t������
	shuffle();
}

Deck::~Deck() {
	//�S�ẴJ�[�h���폜
	for (int i = 0; i < m_size; i++) {
		delete m_cardlist[i];
	}
}

void Deck::load_deck(string filename) {
	m_back_sum = 0;
	m_size = 0;
	//txt�t�@�C������f�[�^�����
	int fp;
	char buff[256];
	fp = FileRead_open(filename.c_str());
	while(FileRead_eof(fp) == 0) {
		//�J�[�h�̉摜�t�@�C�������擾
		FileRead_gets(buff, 256, fp);
		string pass = "picture/card/";
		pass += buff;
		pass += ".png";
		int handle = LoadGraph(pass.c_str());
		if (handle == -1) { break; }
		//���̃J�[�h�̖������擾
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
	//�R�D�̃L���[���x�N�^�ɕϊ�
	while (!m_cards.empty()) {
		vec.push_back(m_cards.front());
		m_cards.pop_front();
	}
	//�x�N�^���V���b�t�����Ȃ���L���[�ɓ����
	for (int i = 0; i < size; i++) {
		int r = GetRand(size - 1 - i) + i;
		m_cards.push_front(vec[r]);
		vec[r] = vec[i];
	}
}

//�J�[�h�̗��\��ύX
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


//�`�`�Ȃǂ̃J�[�h�Ǘ�
CardList::CardList() {
	m_now = -1;
}
//�J�[�h��ǉ�
void CardList::push_card(int index) {
	if (m_now == -1) { m_now = index; }
	//else { m_right.push_back(index); }
	else { m_left.push_front(index); }
}
//m_now���P�E�̃J�[�h�ɕύX
void CardList::move_left() {
	if (m_right.empty()) { return; }
	m_left.push_back(m_now);
	m_now = m_right.front();
	m_right.pop_front();
}
//m_now���P���̃J�[�h�ɕύX
void CardList::move_right() {
	if (m_left.empty()) { return; }
	m_right.push_front(m_now);
	m_now = m_left.back();
	m_left.pop_back();
}
//�J�[�h�̖�����Ԃ�
int CardList::get_size() {
	if (m_now == -1) { return 0; }
	return 1 + m_left.size() + m_right.size();
}
//�J�[�h���O��
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
