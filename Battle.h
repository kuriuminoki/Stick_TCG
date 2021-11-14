#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED

#include<string>

//プレイヤー二人の試合

class Player;
class Button;

class BattleField {
private:
	int hand_x, hand_y;
	int m_font;
	Button* m_change_button;//プレイヤー切り替えボタン
	Player* m_player[2];//2人のプレイヤー
	bool m_turn;//今はどっちのターンか
public:
	BattleField(std::string deckname1, std::string deckname2);
	~BattleField();
public:
	bool play();//メイン 終了でtrue
	void draw(int sheet1, int sheet2);//描画
};

#endif
