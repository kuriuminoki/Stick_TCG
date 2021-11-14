#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

////カードのクラス群////

#include<queue>
#include<vector>

//カードのクラス
class Card {
private:
	int m_pic_handle;//画像ハンドル
	bool m_hold;//ホールド状態ならtrue
	bool m_back;//裏向きならtrue
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

//デッキ
class Deck {
private:
	int m_size;
	std::deque<int> m_cards;//山札 frontが１番上
	std::vector<Card*> m_cardlist;//全てのカードリスト
	int m_back_sum;//裏向きのカードの総数
public:
	Deck(std::string filename);
	~Deck();
public:
	void shuffle();//山札をシャッフルする
	void load_deck(std::string filename);//テキストファイルからデッキの情報をロードする
public:
	//カードリストから、カードの画像を取得
	inline int get_card_handle(int index) {
		return m_cardlist[index]->get_handle();
	}
	//山札の一番上のカードを見る 空なら-1
	inline int get_deck_front() {
		if (m_cards.empty()) { return -1; }
		return m_cards.front();
	}
	//山札の一番上のカードを削除
	inline void pop_deck_front() {
		m_cards.pop_front();
	}
	//山札の残り枚数
	inline int get_deck_size() {
		return m_cards.size();
	}
	//カードのホールド状態を変更
	inline void hold_card(int index, bool flag) { m_cardlist[index]->set_hold(flag); }
	//カードのホールド状態を確認
	inline bool check_hold_card(int index) { return m_cardlist[index]->get_hold(); }
	//カードの裏表を変更
	void back_card(int index, bool flag);
	//カードの裏表状態を確認
	inline bool check_back_card(int index) { return m_cardlist[index]->get_back(); }
	//カードを山札の上に戻す
	inline void push_front(int index) { m_cards.push_front(index); }
	//カードを山札の下に戻す
	inline void push_back(int index) { m_cards.push_back(index); }
	//裏向きのカードの数を確認
	inline int get_back_sum() { return m_back_sum; }
};


//カードを管理するための基底クラス
class CardList {
private:
	std::deque<int> m_left;//表示するカードより左のカード
	int m_now;//表示するカード
	std::deque<int> m_right;//表示するカードより右のカード
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
