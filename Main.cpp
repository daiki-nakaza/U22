#include"DxLib.h"
#include <math.h>

#define HEIGHT 100
#define WIDTH 100
#define STAGE 10

/****************************************************
*列挙体の宣言
****************************************************/
typedef enum MENU_MODE {
	GAME_TITLE,//０
	GAME_MAIN,//１
	GAME_END,//２
	GAME_MENU,//3
	GAME_INIT,//4
	GAME_CLEAR,//5
	GAME_HELP,//6


	END = 99
};


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



/***************************************
*サウンド用変数
***************************************/



/*********************************************
*関数のプロトタイプ宣言
*********************************************/
void DrawGameTitle(void);
void DrawGameMain(void);
void DrawEnd(void);
void DrawMenu(void);
void DrawInit(void);
void DrawClear(void);
void DrawGameOver(void);//ゲームオーバー描画処理
void DrawHelp(void);


int LoadImages();//画像読み込み
int LoadSounds();//音声読み込み

void DrawStage(void);



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
		case GAME_HELP:
			DrawHelp();
			break;
		}

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}


void DrawGameTitle(){}
void DrawGameMain(){}
void DrawEnd(){}
void DrawMenu(){}
void DrawInit(void){}
void DrawClear(void){}
void DrawGameOver(void) {}//ゲームオーバー描画処理
void DrawHelp(void){}


int LoadImages() {
	return 0;
}
int LoadSounds() {
	return 0;
}

void DrawStage(void){}
