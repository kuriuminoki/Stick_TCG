#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

////�J�[�h�̃N���X�Q////

#include<queue>
#include<vector>

//�J�[�h�̃N���X
class Card {
private:
	int m_pic_handle;//�摜�n���h��
	bool m_hold;//�z�[���h��ԂȂ�true
	bool m_back;//�������Ȃ�true
public:
	Card(int pic_handle);
	~Card();
public:
	inline void set_hold(bool hold) {
		m_hold = hold;
	}
	inline void set_back(bool back) {
		m_back = back;
	}
	inline bool get_hold() {
		return m_hold;
	}
	inline bool get_back() {
		return m_back;
	}
	inline int get_handle() {
		return m_pic_handle;
	}
};

//�f�b�L
class Deck {
private:
	int m_size;
	std::deque<int> m_cards;//�R�D front���P�ԏ�
	std::vector<Card*> m_cardlist;//�S�ẴJ�[�h���X�g
	int m_back_sum;//�������̃J�[�h�̑���
public:
	Deck(std::string filename);
	~Deck();
public:
	void shuffle();//�R�D���V���b�t������
	void load_deck(std::string filename);//�e�L�X�g�t�@�C������f�b�L�̏������[�h����
public:
	//�J�[�h���X�g����A�J�[�h�̉摜���擾
	inline int get_card_handle(int index) {
		return m_cardlist[index]->get_handle();
	}
	//�R�D�̈�ԏ�̃J�[�h������ ��Ȃ�-1
	inline int get_deck_front() {
		if (m_cards.empty()) { return -1; }
		return m_cards.front();
	}
	//�R�D�̈�ԏ�̃J�[�h���폜
	inline void pop_deck_front() {
		m_cards.pop_front();
	}
	//�R�D�̎c�薇��
	inline int get_deck_size() {
		return m_cards.size();
	}
	//�J�[�h�̃z�[���h��Ԃ�ύX
	inline void hold_card(int index, bool flag) { m_cardlist[index]->set_hold(flag); }
	//�J�[�h�̃z�[���h��Ԃ��m�F
	inline bool check_hold_card(int index) { return m_cardlist[index]->get_hold(); }
	//�J�[�h�̗��\��ύX
	void back_card(int index, bool flag);
	//�J�[�h�̗��\��Ԃ��m�F
	inline bool check_back_card(int index) { return m_cardlist[index]->get_back(); }
	//�J�[�h���R�D�̏�ɖ߂�
	inline void push_front(int index) { m_cards.push_front(index); }
	//�J�[�h���R�D�̉��ɖ߂�
	inline void push_back(int index) { m_cards.push_back(index); }
	//�������̃J�[�h�̐����m�F
	inline int get_back_sum() { return m_back_sum; }
};


//�J�[�h���Ǘ����邽�߂̊��N���X
class CardList {
private:
	std::deque<int> m_left;//�\������J�[�h��荶�̃J�[�h
	int m_now;//�\������J�[�h
	std::deque<int> m_right;//�\������J�[�h���E�̃J�[�h
public:
	CardList();
public:
	inline bool right_limit() { return m_right.empty(); }
	inline bool left_limit() { return m_left.empty(); }
	inline int get_now_index() { return m_now; }
	inline int get_now_num() {
		if (m_now == -1) { return 0; }
		return m_right.size() + 1;
	}
	void push_card(int index);
	void move_left();
	void move_right();
	int get_size();
	void pop_card();
};


#endif
