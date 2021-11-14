#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

////マウスなどの入力系////

int UpdateKey();

void mouse_limit(int& hand_x, const int hand_y);

void mouse_click();
int left_click();
int right_click();

//デバッグモード起動用
int control_debug();

//バックスペースキー
int control_back();

//矢印キー
int control_move();

//Z,Xキー
int control_ex();

//Ｃキー
int control_c();

//Shiftキー
int control_space();

//ゲーム終了用
int control_esc();

#endif
