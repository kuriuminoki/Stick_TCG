#ifndef CREATE_H_INCLUDED
#define CREATE_H_INCLUDED

#include<queue>
#include<utility>
#include<string>
#include<vector>

class Button;

class DeckCreate {
private:
	int m_card_handle;//��ʂɕ\������J�[�h(�f�b�L�p)
	int m_list_handle;//��ʂɕ\������J�[�h(���X�g�p)
	int m_list_now;//�����Ă���J�[�h�̃C���f�b�N�X�i���X�g�p�j
	int m_font;
	std::string m_filename;
	std::deque<std::pair<int, int> > m_deck_left;//���X�g�ɂ�����C���f�b�N�X�A����
	std::pair<int, int> m_deck_now;
	std::deque<std::pair<int, int> > m_deck_right;
	int m_deck_size;
	std::vector<std::string> m_card_list;//�J�[�h�̃t�@�C����"no����"
private:
	int hand_x, hand_y;
	int m_round;//�z�C�[���̉�]��
	int m_right_handle, m_left_handle;
	Button* m_right_button;
	Button* m_left_button;
	Button* m_erase_button;
	Button* m_right_button2;//�J�[�h���X�g�p�̍��E�{�^��
	Button* m_left_button2;
	Button* m_add_button;
	Button* m_edge_left_button;//���[�֔�ԃ{�^��
	Button* m_edge_right_button;//�E�[�֔�ԃ{�^��
public:
	DeckCreate(std::string filename);
	~DeckCreate();
private:
	bool load_deck();
	void load_card();
private:
	void set_now(int index);//�\������J�[�h�̃��[�h
	void deck_check();//�f�b�L�p�̍��E�̃{�^���X�V
	void move_deck_left();
	void move_deck_right();
	void erase_deck();
	void move_list_left();
	void move_list_right();
	void move_list_edge();
	void add_deck();
	void deck_adjust();//�d������J�[�h���܂Ƃ߂�
public:
	bool play();
	void draw();
};


#endif