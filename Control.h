#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

////�}�E�X�Ȃǂ̓��͌n////

int UpdateKey();

void mouse_limit(int& hand_x, const int hand_y);

void mouse_click();
int left_click();
int right_click();

//�f�o�b�O���[�h�N���p
int control_debug();

//�o�b�N�X�y�[�X�L�[
int control_back();

//���L�[
int control_move();

//Z,X�L�[
int control_ex();

//�b�L�[
int control_c();

//Shift�L�[
int control_space();

//�Q�[���I���p
int control_esc();

#endif
