#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include<string>

class Deck;//デッキ
class CardList;//AA,DA,PA,手札,捨て札
class Button;

enum STATE {
	SEE_AA,//AAを見てる
	SEE_DA,//DAを見てる
	SEE_PA,//PAを見てる
	SEE_HAND,//手札を見てる
	SEE_CEMETERY,//捨て札を見てる
};

class Player {
private:
	Deck* m_deck;//デッキ
	CardList* m_aa;//AAにあるカード
	CardList* m_da;//DAにあるカード
	CardList* m_pa;//PAにあるカード
	CardList* m_hand;//手札
	CardList* m_cemetery;//捨て札
	int m_area_num;//注目中のエリアにあるカードの数
private:
	int m_font;
	Button* m_aa_button;
	Button* m_da_button;
	Button* m_pa_button;
	Button* m_hand_button;
	Button* m_cemetery_button;
	Button* m_back_button;//カードの裏表を変える
	Button* m_hold_button;//カードをホールド・リリースする
	int m_small_font;
	Button* m_toaa_button;//AAへ移動させる
	Button* m_toda_button;//DAへ移動させる
	Button* m_topa_button;//PAへ移動させる
	Button* m_tohand_button;//手札へ移動させる
	Button* m_tocemetery_button;//捨て札へ移動させる
	Button* m_todeckfront_button;//山札の１番上へ移動させる
	Button* m_todeckback_button;//山札の１番下へ移動させる
	Button* m_shuffle_button;//山札シャッフルボタン
	Button* m_draw_button;//1枚ドローボタン
	Button* m_deckpop_button;//1枚捨て札ボタン
	int m_right_handle, m_left_handle;//矢印の画像
	Button* m_right_button;//右へ移動ボタン
	Button* m_left_button;//左へ移動ボタン
private:
	int hand_x, hand_y;
	int m_input_mouse;
	int m_state;//今、どの画面か
	int m_focus_card;//今のどのカードに注目しているか
	int m_focus_num;//注目しているカードは左から何番目か
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
