#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include<string>

class Deck;//�f�b�L
class CardList;//AA,DA,PA,��D,�̂ĎD
class Button;

enum STATE {
	SEE_AA,//AA�����Ă�
	SEE_DA,//DA�����Ă�
	SEE_PA,//PA�����Ă�
	SEE_HAND,//��D�����Ă�
	SEE_CEMETERY,//�̂ĎD�����Ă�
};

class Player {
private:
	Deck* m_deck;//�f�b�L
	CardList* m_aa;//AA�ɂ���J�[�h
	CardList* m_da;//DA�ɂ���J�[�h
	CardList* m_pa;//PA�ɂ���J�[�h
	CardList* m_hand;//��D
	CardList* m_cemetery;//�̂ĎD
	int m_area_num;//���ڒ��̃G���A�ɂ���J�[�h�̐�
private:
	int m_font;
	Button* m_aa_button;
	Button* m_da_button;
	Button* m_pa_button;
	Button* m_hand_button;
	Button* m_cemetery_button;
	Button* m_back_button;//�J�[�h�̗��\��ς���
	Button* m_hold_button;//�J�[�h���z�[���h�E�����[�X����
	int m_small_font;
	Button* m_toaa_button;//AA�ֈړ�������
	Button* m_toda_button;//DA�ֈړ�������
	Button* m_topa_button;//PA�ֈړ�������
	Button* m_tohand_button;//��D�ֈړ�������
	Button* m_tocemetery_button;//�̂ĎD�ֈړ�������
	Button* m_todeckfront_button;//�R�D�̂P�ԏ�ֈړ�������
	Button* m_todeckback_button;//�R�D�̂P�ԉ��ֈړ�������
	Button* m_shuffle_button;//�R�D�V���b�t���{�^��
	Button* m_draw_button;//1���h���[�{�^��
	Button* m_deckpop_button;//1���̂ĎD�{�^��
	int m_right_handle, m_left_handle;//���̉摜
	Button* m_right_button;//�E�ֈړ��{�^��
	Button* m_left_button;//���ֈړ��{�^��
private:
	int hand_x, hand_y;
	int m_input_mouse;
	int m_state;//���A�ǂ̉�ʂ�
	int m_focus_card;//���̂ǂ̃J�[�h�ɒ��ڂ��Ă��邩
	int m_focus_num;//���ڂ��Ă���J�[�h�͍����牽�Ԗڂ�
public:
	Player(std::string deck_filename);
	~Player();
public:
	bool play(int input_mouse);
	void draw();
private:
	void deck_draw();
	void dispose_deck();
	void push_deck_front(CardList& from);
	void push_deck_back(CardList& from);
private:
	void change_true_button();
	void change_state();
	void play_card_list(CardList& list);
	void move_card(CardList& from, CardList& to, bool state = false);
};

#endif
