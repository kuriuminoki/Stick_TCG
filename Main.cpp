#include "DxLib.h"
#include "Control.h"
#include "Battle.h"
#include "Create.h"
#include <math.h>
#include<string>
#include<iostream>

using namespace std;

static int WINDOW = TRUE;

///////fpsの調整///////////////
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
		DrawStringToHandle(10, 10, "デッキ１の名前を入力（拡張子なし）：", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 60, deckname1.c_str(), GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 110, ">エンターキーで次へ進む", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 160, "　>右クリックかバックスペースキーで1字削除", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 850, "スペースキーでデッキ作成に切り替え", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 900, "エスケープキーで終了", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 950, "（シミュレーション中に押したらこの画面に戻る）", GetColor(255, 255, 255), font);
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
		DrawStringToHandle(10, 10, "デッキ２の名前を入力（拡張子なし）：", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 60, deckname2.c_str(), GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 110, ">エンターキーで次へ進む", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 160, "　>右クリックかバックスペースキーで1字削除", GetColor(255, 255, 255), font);
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
		DrawStringToHandle(10, 10, "プレイマット１の名前を入力（拡張子あり）：", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 60, sheet1_name.c_str(), GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 110, ">エンターキーで次へ進む", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 160, "　>右クリックかバックスペースキーで1字削除", GetColor(255, 255, 255), font);
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
		DrawStringToHandle(10, 10, "プレイマット２の名前を入力（拡張子あり）：", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 60, sheet2_name.c_str(), GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 110, ">エンターキーでスタート", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 160, "　>右クリックかバックスペースキーで1字削除", GetColor(255, 255, 255), font);
	}
	else {
		bf->play();
		bf->draw(sheet1_handle, sheet2_handle);
	}
	if (control_esc() == TRUE) {
		if (state < 4) {
			DxLib_End(); // DXライブラリ終了処理
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
		DrawStringToHandle(10, 10, "作成・編集するデッキの名前を入力（拡張子なし）：", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 60, deckname1.c_str(), GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 110, ">エンターキーで編集画面へ", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 160, "　>右クリックかバックスペースキーで1字削除", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 850, "スペースキーでシミュレータに切り替え", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 900, "エスケープキーで終了", GetColor(255, 255, 255), font);
		DrawStringToHandle(10, 950, "（デッキ作成画面中に押したらこの画面に戻る）", GetColor(255, 255, 255), font);
	}
	else {
		dc->play();
		dc->draw();
	}
	if (control_esc() == TRUE) {
		if (state < 1) {
			DxLib_End(); // DXライブラリ終了処理
		}
		else {
			state = 0;
			ClearInputCharBuf();
			delete dc;
		}
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetWindowSizeChangeEnableFlag(TRUE);//windowサイズ変更可能
	SetUseDirectInputFlag(TRUE);
	SetGraphMode(1280, 1024, 16);
	ChangeWindowMode(WINDOW), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	//SetAlwaysRunFlag(TRUE);//画面を常にアクティブ
	SetMainWindowText("TCG Simulator");
	////マウス関連////
	SetMouseDispFlag(TRUE);//マウス表示
	//SetMousePoint(320, 240);//マウスカーソルの初期位置
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//SetDrawMode(DX_DRAWMODE_NEAREST);
	int state = 0;//0(デッキ１入力) -> 1(デッキ２入力) -> 2(シミュレーション中)
	int font = CreateFontToHandle(NULL, 40, 3);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		UpdateKey();
		mouse_click();

		/////メイン////
		if (mode_flag) {
			play_simulate(state, font);
		}
		else {
			create_deck(state, font);
		}
		///////////////

		//FPS操作
		if (control_debug() == TRUE) {
			if (debug == FALSE) { debug = TRUE; }
			else { debug = FALSE; }
		}
		Update();
		if (debug == TRUE) { Draw(); }
		Wait();
		//FPS操作ここまで
	}
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}