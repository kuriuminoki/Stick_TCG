#ifndef CREATE_H_INCLUDED
#define CREATE_H_INCLUDED

#include<queue>
#include<utility>
#include<string>
#include<vector>

class Button;

class DeckCreate {
private:
	int m_card_handle;//画面に表示するカード(デッキ用)
	int m_list_handle;//画面に表示するカード(リスト用)
	int m_list_now;//今見ているカードのインデックス（リスト用）
	int m_font;
	std::string m_filename;
	std::deque<std::pair<int, int> > m_deck_left;//リストにおけるインデックス、枚数
	std::pair<int, int> m_deck_now;
	std::deque<std::pair<int, int> > m_deck_right;
	int m_deck_size;
	std::vector<std::string> m_card_list;//カードのファイル名"no○○"
private:
	int hand_x, hand_y;
	int m_round;//ホイールの回転量
	int m_right_handle, m_left_handle;
	Button* m_right_button;
	Button* m_left_button;
	Button* m_erase_button;
	Button* m_right_button2;//カードリスト用の左右ボタン
	Button* m_left_button2;
	Button* m_add_button;
	Button* m_edge_left_button;//左端へ飛ぶボタン
	Button* m_edge_right_button;//右端へ飛ぶボタン
public:
	DeckCreate(std::string filename);
	~DeckCreate();
private:
	bool load_deck();
	void load_card();
private:
	void set_now(int index);//表示するカードのロード
	void deck_check();//デッキ用の左右のボタン更新
	void move_deck_left();
	void move_deck_right();
	void erase_deck();
	void move_list_left();
	void move_list_right();
	void move_list_edge();
	void add_deck();
	void deck_adjust();//重複するカードをまとめる
public:
	bool play();
	void draw();
};


#endif