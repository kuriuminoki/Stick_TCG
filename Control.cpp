#include "DxLib.h"
#include "Control.h"


//////////�L�[�{�[�h�̓��͏�Ԃ��i�[����////////////////

int Key[256]; // �L�[��������Ă���t���[�������i�[����

// �L�[�̓��͏�Ԃ��X�V����
int UpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}

void mouse_limit(int& hand_x, const int hand_y) {
	if (hand_x < 0 && hand_y > 0 && hand_y < 480) {
		hand_x = 0;
		SetMousePoint(0, hand_y);//�}�E�X�J�[�\���̈ʒu
	}
	else if (hand_x > 640 && hand_y > 0 && hand_y < 480) {
		hand_x = 640;
		SetMousePoint(640, hand_y);//�}�E�X�J�[�\���̈ʒu
	}
}

///////////�}�E�X�̓��͏�Ԃ�Ԃ�//////////////
static int left_cnt = 0;
static int right_cnt = 0;
void mouse_click() {
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) { left_cnt++; }
	else { left_cnt = 0; }
	if (GetMouseInput() == MOUSE_INPUT_RIGHT) { right_cnt++; }
	else { right_cnt = 0; }
}
int left_click() {
	return left_cnt;
}
int right_click() {
	return right_cnt;
}

//�f�o�b�O���[�h�N���p
int control_debug() {
	if (Key[KEY_INPUT_F] == 1) { // F�L�[�������ꂽ�u��
		return TRUE;
	}
	return FALSE;
}

//�o�b�N�X�y�[�X�L�[
int control_back() {
	if (Key[KEY_INPUT_BACK] == 1) { // F�L�[�������ꂽ�u��
		return TRUE;
	}
	return FALSE;
}

//���L�[
int control_move() {
	if (Key[KEY_INPUT_LEFT] > 0) { // ���L�[��������Ă����
		return 1;
	}
	if (Key[KEY_INPUT_RIGHT] > 0) { // �E�L�[��������Ă����
		return 2;
	}
	if (Key[KEY_INPUT_UP] > 0) { // ��L�[��������Ă����
		return 3;
	}
	if (Key[KEY_INPUT_DOWN] > 0) { // ���L�[��������Ă����
		return 4;
	}
	return FALSE;
}
//Z,X�L�[
int control_ex() {
	if (Key[KEY_INPUT_Z] > 0) { // Z�L�[��������Ă����
		return 1;
	}
	if (Key[KEY_INPUT_X] > 0) { // X�L�[��������Ă����
		return 2;
	}
	return FALSE;
}

//C�L�[
int control_c() {
	if (Key[KEY_INPUT_C] == 1) { // C�L�[��������Ă����
		return 1;
	}
	return FALSE;
}

//SPACE�L�[
int control_space() {
	if (Key[KEY_INPUT_SPACE] == 1) { // �X�y�[�X�L�[��������Ă����
		return 1;
	}
	return FALSE;
}

//�Q�[���I���p
int control_esc() {
	if (Key[KEY_INPUT_ESCAPE] == 2) { //ESC�L�[��2�J�E���g������Ă�����
		return TRUE;
	}
	return FALSE;
}