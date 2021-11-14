#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include<string>

class WeaponInfo;
class Dash;

class Button {
private:
	bool m_flag = true;//�@�\���Ȃ��{�^����false
	std::string m_tag = "";
	int m_x, m_y;//�{�^���̈ʒu
	int m_wide, m_height;
	int m_color;//�l�p�̒��̐F
	int m_color2;//�}�E�X���d�Ȃ��Ă���Ƃ��Ɏg���F
	int m_font_color;//�����̐F
	int m_font;
	int m_dx, m_dy;//������\��������W
	int m_graph_handle = -1;//�G
	int m_graph_ex;//�G�̊g�嗦
public:
	Button(std::string, int x, int y, int wide, int height, int color, int color2, int font, int font_color);
public:
	void change_flag(bool f, int new_color);
	int get_handle();//�摜���擾
	bool overlap(int hand_x, int hand_y);
	void draw(int hand_x, int hand_y);
	void set_graph(int handle, int ex);
	void set_string(std::string new_string);//�^�O�����Ȃ���
	//�t���O���擾
	inline bool get_flag() {
		return m_flag;
	}
};


#endif