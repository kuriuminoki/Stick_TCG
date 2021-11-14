#include "DxLib.h"
#include "Control.h"


//////////キーボードの入力状態を格納する////////////////

int Key[256]; // キーが押されているフレーム数を格納する

// キーの入力状態を更新する
int UpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}

void mouse_limit(int& hand_x, const int hand_y) {
	if (hand_x < 0 && hand_y > 0 && hand_y < 480) {
		hand_x = 0;
		SetMousePoint(0, hand_y);//マウスカーソルの位置
	}
	else if (hand_x > 640 && hand_y > 0 && hand_y < 480) {
		hand_x = 640;
		SetMousePoint(640, hand_y);//マウスカーソルの位置
	}
}

///////////マウスの入力状態を返す//////////////
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

//デバッグモード起動用
int control_debug() {
	if (Key[KEY_INPUT_F] == 1) { // Fキーが押された瞬間
		return TRUE;
	}
	return FALSE;
}

//バックスペースキー
int control_back() {
	if (Key[KEY_INPUT_BACK] == 1) { // Fキーが押された瞬間
		return TRUE;
	}
	return FALSE;
}

//矢印キー
int control_move() {
	if (Key[KEY_INPUT_LEFT] > 0) { // 左キーが押されている間
		return 1;
	}
	if (Key[KEY_INPUT_RIGHT] > 0) { // 右キーが押されている間
		return 2;
	}
	if (Key[KEY_INPUT_UP] > 0) { // 上キーが押されている間
		return 3;
	}
	if (Key[KEY_INPUT_DOWN] > 0) { // 下キーが押されている間
		return 4;
	}
	return FALSE;
}
//Z,Xキー
int control_ex() {
	if (Key[KEY_INPUT_Z] > 0) { // Zキーが押されている間
		return 1;
	}
	if (Key[KEY_INPUT_X] > 0) { // Xキーが押されている間
		return 2;
	}
	return FALSE;
}

//Cキー
int control_c() {
	if (Key[KEY_INPUT_C] == 1) { // Cキーが押されている間
		return 1;
	}
	return FALSE;
}

//SPACEキー
int control_space() {
	if (Key[KEY_INPUT_SPACE] == 1) { // スペースキーが押されている間
		return 1;
	}
	return FALSE;
}

//ゲーム終了用
int control_esc() {
	if (Key[KEY_INPUT_ESCAPE] == 2) { //ESCキーが2カウント押されていたら
		return TRUE;
	}
	return FALSE;
}