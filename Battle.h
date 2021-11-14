#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED

#include<string>

//�v���C���[��l�̎���

class Player;
class Button;

class BattleField {
private:
	int hand_x, hand_y;
	int m_font;
	Button* m_change_button;//�v���C���[�؂�ւ��{�^��
	Player* m_player[2];//2�l�̃v���C���[
	bool m_turn;//���͂ǂ����̃^�[����
public:
	BattleField(std::string deckname1, std::string deckname2);
	~BattleField();
public:
	bool play();//���C�� �I����true
	void draw(int sheet1, int sheet2);//�`��
};

#endif
