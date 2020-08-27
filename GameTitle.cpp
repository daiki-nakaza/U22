#include "DxLib.h" 

#include "GameTitle.h" 
#include "Player.h" 


int g_MenuTime = 0;
int g_MenuNumber = 0;
int titleTime = 0;
int g_MenuY = 0;

int g_GameTitleImage;
int g_Cursor;


void DrawGameTitle() {		//ゲームタイトル描画処理
	//メニューカーソル移動処理
	if (--g_MenuTime <= 0) {
		if (g_KeyFlg & PAD_INPUT_DOWN) {
			PlaySoundMem(g_Cursor, DX_PLAYTYPE_BACK);//ここでseならせる
			if (++g_MenuNumber > 2) {
				g_MenuNumber = 0;
			}
			g_MenuTime = 10;
		}
		if (g_KeyFlg & PAD_INPUT_UP) {
			PlaySoundMem(g_Cursor, DX_PLAYTYPE_BACK);
			if (--g_MenuNumber < 0) {
				g_MenuNumber = 2;
			}
			g_MenuTime = 10;
		}

	}

	//ｚキーでメニュー選択
	if (--g_MenuTime <= 0) {
		if (g_KeyFlg & PAD_INPUT_A) {
			g_GameState = g_MenuNumber + 1;
			g_MenuTime = 10;
		}
	}

	//タイトル画像表示
	DrawGraph(0, 0, g_GameTitleImage, FALSE);

	if (++titleTime >= 60) {
		titleTime = 0;
	}

	/*if (titleTime < 30) {
		if (g_MenuNumber == 0) {
			DrawGraph(0, 0, g_Title5Image, FALSE);
		}
		else if (g_MenuNumber == 1) {
			DrawGraph(0, 0, g_Title7Image, FALSE);
		}
	}
	else if (titleTime < 60) {
		if (g_MenuNumber == 0) {
			DrawGraph(0, 0, g_Title6Image, FALSE);
		}
		else if (g_MenuNumber == 1) {
			DrawGraph(0, 0, g_Title8Image, FALSE);
		}

	}*/

	//メニューカーソル（三角形）の表示
	g_MenuY = g_MenuNumber * 111;

	//DrawString(265, 263, "ゲームスタート", 0xffffff);
	//DrawString(265, 315, "ゲームヘルプ", 0xffffff);
	//DrawString(265, 367, "終了", 0xffffff);

	DrawTriangle(25, 370 + g_MenuY, 75, 395 + g_MenuY,
		25, 420 + g_MenuY, GetColor(255, 0, 0), TRUE);
}