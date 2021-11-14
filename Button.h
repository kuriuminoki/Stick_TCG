#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include<string>

class WeaponInfo;
class Dash;

class Button {
private:
	bool m_flag = true;//機能しないボタンはfalse
	std::string m_tag = "";
	int m_x, m_y;//ボタンの位置
	int m_wide, m_height;
	int m_color;//四角の中の色
	int m_color2;//マウスが重なっているときに使う色
	int m_font_color;//文字の色
	int m_font;
	int m_dx, m_dy;//文字を表示する座標
	int m_graph_handle = -1;//絵
	int m_graph_ex;//絵の拡大率
public:
	Button(std::string, int x, int y, int wide, int height, int color, int color2, int font, int font_color);
public:
	void change_flag(bool f, int new_color);
	int get_handle();//画像を取得
	bool overlap(int hand_x, int hand_y);
	void draw(int hand_x, int hand_y);
	void set_graph(int handle, int ex);
	void set_string(std::string new_string);//タグをつけなおす
	//フラグを取得
	inline bool get_flag() {
		return m_flag;
	}
};


#endif