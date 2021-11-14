#include"Button.h"
#include"Control.h"
#include"DxLib.h"
#include<string>
#include<sstream>

using namespace std;

/////�{�^��/////////////
Button::Button(string tag, int x, int y, int wide, int height, int color, int color2, int font, int font_color) {
	m_graph_handle = -1;
	m_x = x; m_y = y;
	m_wide = wide; m_height = height;
	m_color = color;
	m_color2 = color2;
	m_font = font;
	m_font_color = font_color;
	set_string(tag);
}

//�{�^���̕`�� ���Ƀ��x���̕�������\���ł���
void Button::draw(int hand_x, int hand_y) {
	if (overlap(hand_x, hand_y)) {
		DrawBox(m_x - 5, m_y - 5, m_x + m_wide + 5, m_y + m_height + 5, m_color2, TRUE);
	}
	DrawBox(m_x, m_y, m_x + m_wide, m_y + m_height, m_color, TRUE);
	//�G�̕`��
	if (!m_flag) { SetDrawBright(100, 100, 100); }
	DrawRotaGraph(m_x + (m_wide / 2), m_y + (m_height / 2), m_graph_ex, 0, m_graph_handle, TRUE, FALSE);
	SetDrawBright(255, 255, 255);
	//�����̕`��
	DrawStringToHandle(m_dx, m_dy, m_tag.c_str(), m_font_color, m_font);
	//DrawFormatString(m_x, m_y - 20, WHITE, "font_size = %d", m_font_size);
	//DrawFormatString(m_x, m_y - 40, WHITE, "string_size = %d", m_string_size);
}

//�{�^���̃I���E�I�t
void Button::change_flag(bool f, int new_color) {
	m_flag = f;
	m_color = new_color;
}

//�{�^�����}�E�X�J�[�\���Əd�Ȃ��Ă��邩
bool Button::overlap(int hand_x, int hand_y) {
	if (!m_flag) {
		return false;
	}
	if (hand_x >= m_x && hand_x <= m_x + m_wide && hand_y >= m_y && hand_y <= m_y + m_height) {
		return true;
	}
	return false;
}

//�{�^�����ɕ����ł͂Ȃ��G��\������悤�ɃZ�b�g
void Button::set_graph(int handle, int ex) {
	m_graph_handle = handle;
	m_graph_ex = ex;
	m_tag = "";
}

//�^�O�����Ȃ���
void Button::set_string(std::string tag) {
	m_tag = tag;
	//�����񂪎�镝�𕶎��̑傫���ƕ�����̒�������v�Z
	int m_font_size;//�ꕶ���̑傫��
	int m_string_size;//�����񂪂Ƃ镝
	GetFontStateToHandle(NULL, &m_font_size, NULL, m_font);
	m_string_size = m_font_size * (m_tag.size() / 2);
	m_dx = m_x + (m_wide - m_string_size) / 2 - (m_tag.size() / 2);
	m_dy = m_y + (m_height - m_font_size) / 2;
}

//�摜���擾
int Button::get_handle() {
	return m_graph_handle;
}