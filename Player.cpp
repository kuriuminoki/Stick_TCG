#include"Player.h"
#include"Card.h"
#include"Button.h"
#include"Control.h"
#include"DxLib.h"
#include"Value.h"
#include<sstream>

using namespace std;

const double PI = 3.14159;


Player::Player(string deck_filename) {
	m_deck = new Deck(deck_filename);
	m_aa = new CardList;
	m_da = new CardList;
	m_pa = new CardList;
	m_hand = new CardList;
	m_cemetery = new CardList;

	m_font = CreateFontToHandle(NULL, 40, 3);
	m_aa_button = new Button("�`�`", 20, 900, 150, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_da_button = new Button("�c�`", 180, 900, 150, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_pa_button = new Button("�o�`", 340, 900, 150, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_hand_button = new Button("��D", 500, 900, 150, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_cemetery_button = new Button("�̂ĎD", 660, 900, 150, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	
	m_back_button = new Button("���\���]", 20, 780, 200, 100, LIGHT_YELLOW, YELLOW, m_font, BLACK);
	m_hold_button = new Button("�z�[���h�E�����[�X", 250, 780, 500, 100, LIGHT_YELLOW, YELLOW, m_font, BLACK);

	m_small_font = CreateFontToHandle(NULL, 20, 3);
	m_toaa_button = new Button("�`�`�ֈړ�", 900, 20, 300, 50, LIGHT_RED, RED, m_small_font, BLACK);
	m_toda_button = new Button("�c�`�ֈړ�", 900, 90, 300, 50, LIGHT_RED, RED, m_small_font, BLACK);
	m_topa_button = new Button("�o�`�ֈړ�", 900, 160, 300, 50, LIGHT_RED, RED, m_small_font, BLACK);
	m_tohand_button = new Button("��D�ֈړ�", 900, 230, 300, 50, LIGHT_RED, RED, m_small_font, BLACK);
	m_tocemetery_button = new Button("�̂ĎD�ֈړ�", 900, 300, 300, 50, LIGHT_RED, RED, m_small_font, BLACK);
	m_todeckfront_button = new Button("�R�D�̏�ֈړ�", 900, 380, 300, 50, LIGHT_BLUE, BLUE, m_small_font, BLACK);
	m_todeckback_button = new Button("�R�D�̉��ֈړ�", 900, 450, 300, 50, LIGHT_BLUE, BLUE, m_small_font, BLACK);
	m_shuffle_button = new Button("�R�D���V���b�t��", 900, 530, 300, 50, LIGHT_YELLOW, YELLOW, m_small_font, BLACK);
	m_draw_button = new Button("�P���h���[", 900, 600, 300, 50, LIGHT_YELLOW, YELLOW, m_small_font, BLACK);
	m_deckpop_button = new Button("�R�D�̏���P���̂ĎD", 900, 670, 300, 50, LIGHT_YELLOW, YELLOW, m_small_font, BLACK);

	m_right_handle = LoadGraph("picture/icon/�E���.png");
	m_left_handle = LoadGraph("picture/icon/�����.png");
	m_right_button = new Button("", 750, 250, 70, 400, LIGHT_YELLOW, RED, m_small_font, BLACK);
	m_left_button = new Button("", 100, 250, 70, 400, LIGHT_YELLOW, RED, m_small_font, BLACK);
	m_right_button->set_graph(m_right_handle, 2);
	m_left_button->set_graph(m_left_handle, 2);
	//�������
	m_state = SEE_HAND;
	m_hand_button->change_flag(false, DARK_BLUE);
	m_back_button->change_flag(false, DARK_YELLOW);
	m_hold_button->change_flag(false, DARK_YELLOW);
	m_focus_card = -1;
	for (int i = 0; i < 7; i++) {
		deck_draw();
	}
}

Player::~Player() {
	delete m_deck;
	delete m_aa;
	delete m_da;
	delete m_pa;
	delete m_hand;
	delete m_cemetery;

	DeleteFontToHandle(m_font);
	delete m_aa_button;
	delete m_da_button;
	delete m_pa_button;
	delete m_hand_button;
	delete m_cemetery_button;
	delete m_back_button;
	delete m_hold_button;
	DeleteFontToHandle(m_small_font);
	delete m_toaa_button;
	delete m_toda_button;
	delete m_topa_button;
	delete m_tohand_button;
	delete m_tocemetery_button;
	delete m_todeckfront_button;
	delete m_todeckback_button;
	delete m_shuffle_button;
	delete m_draw_button;
	delete m_deckpop_button;
	DeleteGraph(m_right_handle);
	DeleteGraph(m_left_handle);
	delete m_right_button;
	delete m_left_button;
}

//����
bool Player::play(int input_mouse) {
	GetMousePoint(&hand_x, &hand_y);
	m_input_mouse = input_mouse;
	//����G���A�̕ύX
	change_state();
	//�J�[�h�̏���
	switch (m_state) {
	case SEE_AA:
		play_card_list(*m_aa);
		break;
	case SEE_DA:
		play_card_list(*m_da);
		break;
	case SEE_PA:
		play_card_list(*m_pa);
		break;
	case SEE_CEMETERY:
		play_card_list(*m_cemetery);
		break;
	case SEE_HAND:
		play_card_list(*m_hand);
		break;
	}

	if (left_click() == 1) {
		if (m_shuffle_button->overlap(hand_x, hand_y)) {
			m_deck->shuffle();
		}
		else if (m_draw_button->overlap(hand_x, hand_y)) {
			deck_draw();
		}
		else if (m_deckpop_button->overlap(hand_x, hand_y)) {
			dispose_deck();
		}
	}

	return false;
}

//�`��
void Player::draw() {
	//���ڒ��̃J�[�h
	if (m_focus_card != -1) {
		int handle = m_deck->get_card_handle(m_focus_card);
		if (m_deck->check_back_card(m_focus_card)) {
			SetDrawBright(100, 100, 100);
		}
		if (m_deck->check_hold_card(m_focus_card)) {
			DrawRotaGraph(450, 450, 0.4, PI / 2.0, handle, TRUE, FALSE);
		}
		else {
			DrawRotaGraph(450, 450, 0.4, 0, handle, TRUE, FALSE);
		}
		SetDrawBright(255, 255, 255);
	}
	//�{�^��
	m_aa_button->draw(hand_x, hand_y);
	m_da_button->draw(hand_x, hand_y);
	m_pa_button->draw(hand_x, hand_y);
	m_hand_button->draw(hand_x, hand_y);
	m_cemetery_button->draw(hand_x, hand_y);
	m_back_button->draw(hand_x, hand_y);
	m_hold_button->draw(hand_x, hand_y);
	m_toaa_button->draw(hand_x, hand_y);
	m_toda_button->draw(hand_x, hand_y);
	m_topa_button->draw(hand_x, hand_y);
	m_tohand_button->draw(hand_x, hand_y);
	m_tocemetery_button->draw(hand_x, hand_y);
	m_todeckfront_button->draw(hand_x, hand_y);
	m_todeckback_button->draw(hand_x, hand_y);
	m_shuffle_button->draw(hand_x, hand_y);
	m_draw_button->draw(hand_x, hand_y);
	m_deckpop_button->draw(hand_x, hand_y);
	m_right_button->draw(hand_x, hand_y);
	m_left_button->draw(hand_x, hand_y);
	//����
	ostringstream os;
	os << "�c��R�D�F" << m_deck->get_deck_size();
	DrawBox(845, 775, 1150, 875, BLACK, TRUE);
	DrawStringToHandle(850, 780, os.str().c_str(), GetColor(255,255,255), m_font);
	ostringstream os2;
	os2 << "��_���[�W�F" << m_deck->get_back_sum();
	DrawStringToHandle(850, 830, os2.str().c_str(), GetColor(255, 255, 255), m_font);
	ostringstream os3;
	os3 << "�J�[�h�F" << m_focus_num << " / " <<  m_area_num;
	DrawBox(280, 695, 620, 750, LIGHT_BLUE, TRUE);
	DrawStringToHandle(300, 700, os3.str().c_str(), GetColor(0, 0, 0), m_font);
}

//�R�D�̈�Ԃ̃J�[�h���̂ĎD�ɂ���
void Player::dispose_deck() {
	int num = m_deck->get_deck_front();
	if (num != -1) {
		m_cemetery->push_card(num);
		m_deck->pop_deck_front();
	}
	//�R�D����ɂȂ����Ƃ�
	if (m_deck->get_deck_front() == -1) {
		m_draw_button->change_flag(false, DARK_YELLOW);
		m_deckpop_button->change_flag(false, DARK_YELLOW);
	}
}
//�P���h���[����
void Player::deck_draw() {
	int num = m_deck->get_deck_front();
	if (num != -1) {
		m_hand->push_card(num);
		m_deck->pop_deck_front();
	}
	//�R�D����ɂȂ����Ƃ�
	if (m_deck->get_deck_front() == -1) {
		m_draw_button->change_flag(false, DARK_YELLOW);
		m_deckpop_button->change_flag(false, DARK_YELLOW);
	}
}

void Player::push_deck_front(CardList& from) {
	int num = from.get_now_index();
	if (num == -1) { return; }
	m_deck->push_front(num);
	from.pop_card();
	m_focus_card = -1;
	//�J�[�h�������[�X��Ԃ̕\�����ɂ��Ă���
	m_deck->hold_card(num, false);
	m_deck->back_card(num, false);
}
void Player::push_deck_back(CardList& from) {
	int num = from.get_now_index();
	if (num == -1) { return; }
	m_deck->push_back(num);
	from.pop_card();
	m_focus_card = -1;
	//�J�[�h�������[�X��Ԃ̕\�����ɂ��Ă���
	m_deck->hold_card(num, false);
	m_deck->back_card(num, false);
}

//���ׂẴ{�^����true��
void Player::change_true_button() {
	m_aa_button->change_flag(true, LIGHT_BLUE);
	m_da_button->change_flag(true, LIGHT_BLUE);
	m_pa_button->change_flag(true, LIGHT_BLUE);
	m_hand_button->change_flag(true, LIGHT_BLUE);
	m_cemetery_button->change_flag(true, LIGHT_BLUE);
	m_back_button->change_flag(true, LIGHT_YELLOW);
	m_hold_button->change_flag(true, LIGHT_YELLOW);
	m_toaa_button->change_flag(true, LIGHT_RED);
	m_toda_button->change_flag(true, LIGHT_RED);
	m_topa_button->change_flag(true, LIGHT_RED);
	m_tohand_button->change_flag(true, LIGHT_RED);
	m_tocemetery_button->change_flag(true, LIGHT_RED);
}

//state�̕ω�
void Player::change_state() {
	if (left_click() != 1) { return; }
	//state��ω��A�����ă{�^�����g�p�s�ɕύX
	if (m_aa_button->overlap(hand_x, hand_y)) {
		m_state = SEE_AA;
		change_true_button();
		m_aa_button->change_flag(false, DARK_BLUE);
		m_back_button->change_flag(false, DARK_YELLOW);
	}
	else if (m_da_button->overlap(hand_x, hand_y)) {
		m_state = SEE_DA;
		change_true_button();
		m_da_button->change_flag(false, DARK_BLUE);
		m_back_button->change_flag(false, DARK_YELLOW);
	}
	else if (m_pa_button->overlap(hand_x, hand_y)) {
		m_state = SEE_PA;
		change_true_button();
		m_pa_button->change_flag(false, DARK_BLUE);
	}
	else if (m_hand_button->overlap(hand_x, hand_y)) {
		m_state = SEE_HAND;
		change_true_button();
		m_hand_button->change_flag(false, DARK_BLUE);
		m_back_button->change_flag(false, DARK_YELLOW);
		m_hold_button->change_flag(false, DARK_YELLOW);
	}
	else if (m_cemetery_button->overlap(hand_x, hand_y)) {
		m_state = SEE_CEMETERY;
		change_true_button();
		m_cemetery_button->change_flag(false, DARK_BLUE);
		m_back_button->change_flag(false, DARK_YELLOW);
		m_hold_button->change_flag(false, DARK_YELLOW);
	}
}

//�J�[�h���X�g�̑���
void Player::play_card_list(CardList& list) {
	//�����ڂ��Ă�J�[�h
	m_focus_card = list.get_now_index();
	m_area_num = list.get_size();
	m_focus_num = list.get_now_num();
	//���{�^���̍X�V
	if (list.left_limit()) {
		m_right_button->change_flag(false, DARK_YELLOW);
	}
	else {
		m_right_button->change_flag(true, LIGHT_YELLOW);
	}
	if (list.right_limit()) {
		m_left_button->change_flag(false, DARK_YELLOW);
	}
	else {
		m_left_button->change_flag(true, LIGHT_YELLOW);
	}
	//����J�[�h��ύX����Ƃ�
	if (left_click() == 1 && m_right_button->overlap(hand_x, hand_y)) {
		list.move_right();
	}
	else if (left_click() == 1 && m_left_button->overlap(hand_x, hand_y)) {
		list.move_left();
	}
	else if (m_right_button->get_flag() && m_input_mouse < 0) {
		list.move_right();
	}
	else if (m_left_button->get_flag() && m_input_mouse > 0) {
		list.move_left();
	}
	//���N���b�N�����o
	if (left_click() != 1) { return; }
	//�J�[�h�ւ̑���
	if (m_focus_card != -1) {
		//�J�[�h�̃z�[���h�E�����[�X
		if (m_hold_button->overlap(hand_x, hand_y)) {
			bool flag = m_deck->check_hold_card(m_focus_card);
			m_deck->hold_card(m_focus_card, !flag);
		}
		//�J�[�h�̔��]
		if (m_back_button->overlap(hand_x, hand_y)) {
			bool flag = m_deck->check_back_card(m_focus_card);
			m_deck->back_card(m_focus_card, !flag);
		}
	}
	//�J�[�h�̈ړ�
	if (m_toaa_button->overlap(hand_x, hand_y)) {
		move_card(list, *m_aa, true);
	}
	else if (m_toda_button->overlap(hand_x, hand_y)) {
		move_card(list, *m_da, true);
	}
	else if (m_topa_button->overlap(hand_x, hand_y)) {
		move_card(list, *m_pa);
	}
	else if (m_tohand_button->overlap(hand_x, hand_y)) {
		move_card(list, *m_hand);
	}
	else if (m_tocemetery_button->overlap(hand_x, hand_y)) {
		move_card(list, *m_cemetery);
	}
	else if (m_todeckfront_button->overlap(hand_x, hand_y)) {
		push_deck_front(list);
	}
	else if (m_todeckback_button->overlap(hand_x, hand_y)) {
		push_deck_back(list);
	}

}

//�J�[�h�̈ړ� state == true�Ȃ�z�[���h��Ԃ͈ێ�����
void Player::move_card(CardList& from, CardList& to, bool state) {
	int card_index = from.get_now_index();
	if (card_index == -1) { return; }
	//�ړ�
	to.push_card(card_index);
	from.pop_card();
	m_focus_card = -1;
	if (!state) {
		//�J�[�h�������[�X��ԂɕύX
		m_deck->hold_card(card_index, false);
	}
	//�J�[�h��\������
	m_deck->back_card(card_index, false);
}