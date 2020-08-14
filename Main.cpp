#include"DxLib.h"
#include <math.h>

#include "GameMain.h"
#include "GameTitle.h"
#include "GameEnd.h"
#include "GameInit.h"
#include "GameHelp.h"
#include "GameMenu.h"
#include "Map.h"
#include "Player.h"




/****************************************************
*定数の宣言
****************************************************/


/****************************************************
*変数の宣言
****************************************************/


int g_OldKey;
int g_NowKey;
int g_KeyFlg;
int g_OldKey2;
int g_NowKey2;
int g_KeyFlg2;
int g_MouseX;//マウスｘ座標
int g_MouseY;//マウスｙ座標


int g_GameState = GAME_TITLE;//ゲームモード



//int g_MapChip[HEIGHT * 2][WIDTH];

/***************************************
*サウンド用変数
***************************************/



/*********************************************
*関数のプロトタイプ宣言
*********************************************/


int LoadImages();//画像読み込み
int LoadSounds();//音声読み込み





/******************************************************
*プログラムの開始
******************************************************/

//プログラムはWinMainから始まります//
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);//ウィンドウモードで起動
	SetMainWindowText("");//タイトルを設定
	SetGraphMode(1024, 700, 16);


	if (DxLib_Init() == -1) {                    //DXライブラリ初期化処理

		return -1;								//エラーが起きたら直ちに終了
	}
	//画像読み込み関数を呼び出し
	if (LoadImages() == -1) {
		return -1;
	}

	//サウンド読み込み関数を呼び出し
	if (LoadSounds() == -1) {
		return -1;
	}
	if (DebugMode) {
		g_GameState = GAME_MAIN;//ゲームモード
	}


	//DrawInit();

	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0 && g_GameState != END && !(g_KeyFlg & PAD_INPUT_START)) {

		//PlaySoundMem(g_TitleBGM, DX_PLAYTYPE_LOOP, FALSE);

		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & g_OldKey;

		g_OldKey2 = g_NowKey2;
		g_NowKey2 = GetMouseInput();
		g_KeyFlg2 = g_NowKey2 & g_OldKey2;

		//マウスの位置を取得
		GetMousePoint(&g_MouseX, &g_MouseY);

		ClearDrawScreen();
		DrawBox(0, 0, 1050, 620, 0x2f4f4f, TRUE); // 画面全体を希望の色で塗りつぶす
		//DrawBox(0, 0, 1050, 620, 0xffffff, TRUE); // 画面全体を希望の色で塗りつぶす

		switch (g_GameState) {
		case GAME_TITLE:
			DrawGameTitle();
			break;
		case GAME_MAIN:
			DrawGameMain();
			break;
		case GAME_HELP:
			DrawHelp();
			break;
		case GAME_END:
			DrawEnd();
			break;
		case GAME_MENU:
			DrawMenu();
			break;
		case GAME_INIT:
			DrawInit();
			break;
		case GAME_CLEAR:
			DrawClear();
			break;
		case GAME_OVER:
			DrawGameOver();
			break;
		
		}

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}



int LoadImages() {
	//マップチップ
	MapTip = LoadGraph("images/kenkyu7.png");
	//背景
	if ((g_BackGroundImage = LoadGraph("images/haikei2.png")) == -1) return -1;

	//プレイヤー画像
	LoadDivGraph("images/shujin.png", 4, 4, 1, CHA_SIZE_X, CHA_SIZE_Y, Player_Pic);
	LoadDivGraph("images/shujin2.png", 4, 4, 1, CHA_SIZE_X, CHA_SIZE_Y, Player_Pic_R);
	LoadDivGraph("images/attack.png", 6, 6, 1, CHA_SIZE_X * 2, CHA_SIZE_Y, Player_Pic_Attack);
	LoadDivGraph("images/attack2.png", 6, 6, 1, CHA_SIZE_X * 2, CHA_SIZE_Y, Player_Pic_Attack_R);
	Player_Pic_Down = LoadGraph("images/shagami.png", true);
	Player_Pic_Down_R = LoadGraph("images/shagami2.png", true);
	LoadDivGraph("images/motu.png", 4, 4, 1, CHA_SIZE_X, CHA_SIZE_Y, Player_Pic_Hold);
	LoadDivGraph("images/motu2.png", 4, 4, 1, CHA_SIZE_X, CHA_SIZE_Y, Player_Pic_Hold_R);

	//ゲームタイトル背景
	if ((g_GameTitleImage = LoadGraph("images/Title.png")) == -1) return -1;
	//ゲームオーバー背景
	if ((g_GameOverImage = LoadGraph("images/GameOver.png")) == -1) return -1;


	return 0;

}
int LoadSounds() {
	return 0;
}