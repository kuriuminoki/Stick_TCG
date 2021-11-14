#include "DxLib.h"
#include "Control.h"
#include "Battle.h"
#include "Create.h"
#include <math.h>
#include<string>
#include<iostream>

using namespace std;

static int WINDOW = TRUE;

///////fps�̒���///////////////
static int mStartTime;
static int mCount;
static int debug = FALSE;
static float mFps;
static const int N = 30;
static const int FPS = 30;

bool Update() {
	if (mCount == 0) {
		mStartTime = GetNowCount();
	}
	if (mCount == N) {
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Draw() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;
	int waitTime = mCount * 1000 / FPS - tookTime;
	if (waitTime > 0) {
		Sleep(waitTime);
	}
}

string deckname1, deckname2;
string sheet1_name = "picture/sheet/", sheet2_name = "picture/sheet/";
int sheet1_handle, sheet2_handle;
BattleField* bf = NULL;
DeckCreate* dc = NULL;
bool mode_flag = true;

void play_simulate(int& state, const int font) {
	if (state == 0) {
		char c = GetInputChar(TRUE);
		if (c != 0 && c >= CTRL_CODE_CMP) {
			deckname1 += c;
		}
		if (right_click() == 1 || control_back() == TRUE) {
			deckname1.erase(--deckname1.end());
		}
		else if (c == 13) {
			state++;
		}
		else if (control_space() == TRUE) {
			mode_flag = !mode_flag;
			deckname1 = "";
		}
		DrawStringToHandle(10, 10, "�f�b�L�P�̖��O����́i�g���q�Ȃ��j�F", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 60, deckname1.c_str(), GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 110, ">�G���^�[�L�[�Ŏ��֐i��", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 160, "�@>�E�N���b�N���o�b�N�X�y�[�X�L�[��1���폜", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 850, "�X�y�[�X�L�[�Ńf�b�L�쐬�ɐ؂�ւ�", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 900, "�G�X�P�[�v�L�[�ŏI��", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 950, "�i�V�~�����[�V�������ɉ������炱�̉�ʂɖ߂�j", GetColor(255, 255, 255), font);
	}
	else if (state == 1) {
		char c = GetInputChar(TRUE);
		if (c != 0 && c >= CTRL_CODE_CMP) {
			deckname2 += c;
		}
		if (right_click() == 1 || control_back() == TRUE) {
			deckname2.erase(--deckname2.end());
		}
		else if (c == 13) {
			state++;
			bf = new BattleField(deckname1, deckname2);
		}
		DrawStringToHandle(10, 10, "�f�b�L�Q�̖��O����́i�g���q�Ȃ��j�F", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 60, deckname2.c_str(), GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 110, ">�G���^�[�L�[�Ŏ��֐i��", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 160, "�@>�E�N���b�N���o�b�N�X�y�[�X�L�[��1���폜", GetColor(255, 255, 255), font);
	}
	else if (state == 2) {
		char c = GetInputChar(TRUE);
		if (c != 0 && c >= CTRL_CODE_CMP) {
			sheet1_name += c;
		}
		if (right_click() == 1 || control_back() == TRUE) {
			sheet1_name.erase(--sheet1_name.end());
		}
		else if (c == 13) {
			state++;
			sheet1_handle = LoadGraph(sheet1_name.c_str());
		}
		DrawStringToHandle(10, 10, "�v���C�}�b�g�P�̖��O����́i�g���q����j�F", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 60, sheet1_name.c_str(), GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 110, ">�G���^�[�L�[�Ŏ��֐i��", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 160, "�@>�E�N���b�N���o�b�N�X�y�[�X�L�[��1���폜", GetColor(255, 255, 255), font);
	}
	else if (state == 3) {
		char c = GetInputChar(TRUE);
		if (c != 0 && c >= CTRL_CODE_CMP) {
			sheet2_name += c;
		}
		if (right_click() == 1 || control_back() == TRUE) {
			sheet2_name.erase(--sheet2_name.end());
		}
		else if (c == 13) {
			state++;
			sheet2_handle = LoadGraph(sheet2_name.c_str());
		}
		DrawStringToHandle(10, 10, "�v���C�}�b�g�Q�̖��O����́i�g���q����j�F", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 60, sheet2_name.c_str(), GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 110, ">�G���^�[�L�[�ŃX�^�[�g", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 160, "�@>�E�N���b�N���o�b�N�X�y�[�X�L�[��1���폜", GetColor(255, 255, 255), font);
	}
	else {
		bf->play();
		bf->draw(sheet1_handle, sheet2_handle);
	}
	if (control_esc() == TRUE) {
		if (state < 4) {
			DxLib_End(); // DX���C�u�����I������
		}
		else {
			state = 0;
			DeleteGraph(sheet1_handle);
			DeleteGraph(sheet2_handle);
			ClearInputCharBuf();
			delete bf;
		}
	}
}

void create_deck(int& state, int font) {
	if (state == 0) {
		char c = GetInputChar(TRUE);
		if (c != 0 && c >= CTRL_CODE_CMP) {
			deckname1 += c;
		}
		if (right_click() == 1 || control_back() == TRUE) {
			deckname1.erase(--deckname1.end());
		}
		else if (c == 13) {
			state++;
			dc = new DeckCreate(deckname1);
		}
		else if (control_space() == TRUE) {
			mode_flag = !mode_flag;
			deckname1 = "";
		}
		DrawStringToHandle(10, 10, "�쐬�E�ҏW����f�b�L�̖��O����́i�g���q�Ȃ��j�F", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 60, deckname1.c_str(), GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 110, ">�G���^�[�L�[�ŕҏW��ʂ�", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 160, "�@>�E�N���b�N���o�b�N�X�y�[�X�L�[��1���폜", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 850, "�X�y�[�X�L�[�ŃV�~�����[�^�ɐ؂�ւ�", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 900, "�G�X�P�[�v�L�[�ŏI��", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 950, "�i�f�b�L�쐬��ʒ��ɉ������炱�̉�ʂɖ߂�j", GetColor(255, 255, 255), font);
	}
	else {
		dc->play();
		dc->draw();
	}
	if (control_esc() == TRUE) {
		if (state < 1) {
			DxLib_End(); // DX���C�u�����I������
		}
		else {
			state = 0;
			ClearInputCharBuf();
			delete dc;
		}
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetWindowSizeChangeEnableFlag(TRUE);//window�T�C�Y�ύX�\
	SetUseDirectInputFlag(TRUE);
	SetGraphMode(1280, 1024, 16);
	ChangeWindowMode(WINDOW), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//SetAlwaysRunFlag(TRUE);//��ʂ���ɃA�N�e�B�u
	SetMainWindowText("TCG Simulator");
	////�}�E�X�֘A////
	SetMouseDispFlag(TRUE);//�}�E�X�\��
	//SetMousePoint(320, 240);//�}�E�X�J�[�\���̏����ʒu
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//SetDrawMode(DX_DRAWMODE_NEAREST);
	int state = 0;//0(�f�b�L�P����) -> 1(�f�b�L�Q����) -> 2(�V�~�����[�V������)
	int font = CreateFontToHandle(NULL, 40, 3);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		UpdateKey();
		mouse_click();

		/////���C��////
		if (mode_flag) {
			play_simulate(state, font);
		}
		else {
			create_deck(state, font);
		}
		///////////////

		//FPS����
		if (control_debug() == TRUE) {
			if (debug == FALSE) { debug = TRUE; }
			else { debug = FALSE; }
		}
		Update();
		if (debug == TRUE) { Draw(); }
		Wait();
		//FPS���삱���܂�
	}
	DxLib_End(); // DX���C�u�����I������
	return 0;
}