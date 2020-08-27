#include "DxLib.h"

#include "Define.h" 
#include "Player.h" 
#include "Map.h"
#include "GameEnd.h" 
#include "GameTitle.h"
#include "accessory.h"

int g_OvreY = 0;
int g_OverNumber = 0;
int g_OverTime = 0;

int g_GameOverImage;
int g_GameClearImage;

int ClearTime = 0;


void DrawEnd() {			//
	static int WaitTime = 0;

	//タイトル画像表示
	//DrawGraph(0, 0, g_TitleImage, FALSE);

	SetFontSize(24);
	DrawString(360, 480 - 24, "Thank you for Playing", 0xffffff, 0);

	//タイムの加算処理＆終了（3秒後）
	if (++WaitTime > 180) {
		g_GameState = END;
	}
}


void DrawClear(void) {				//ゲームクリア描画処理
	if (ClearTime > 60) {
		DrawGraph(0, 0, g_GameClearImage, FALSE);

		//メニューカーソル移動処理
		if (--g_OverTime <= 0) {
			if (g_KeyFlg & PAD_INPUT_DOWN) {

				if (++g_OverNumber > 1) {
					g_OverNumber = 0;
				}
				g_OverTime = 10;
			}
			if (g_KeyFlg & PAD_INPUT_UP) {
				if (--g_OverNumber < 0) {
					g_OverNumber = 1;
				}
				g_OverTime = 10;
			}

		}

		//ｚキーでメニュー選択
		if (--g_OverTime <= 0) {
			if (g_KeyFlg & PAD_INPUT_A) {
				if (g_OverNumber == 1) {
					g_GameState = 0;
					ClearTime = 0;
				}
				else {
					g_GameState = 0;
					ClearTime = 0;
				}

				g_MenuTime = 20;
			}
		}

		//メニューカーソル（三角形）の表示
		g_OvreY = g_OverNumber * 130;

		/*DrawString(265, 263, "ゲームスタート", 0xffffff);
		DrawString(265, 315, "ゲームヘルプ", 0xffffff);
		DrawString(265, 367, "終了", 0xffffff);*/

		DrawTriangle(40, 335 + g_OvreY, 80, 370 + g_OvreY,
			40, 405 + g_OvreY, GetColor(255, 0, 0), TRUE);
		DrawFormatString(0, 0, 0xffffff, "mouseX = %d   Y = %d", g_MouseX, g_MouseY);

	}
	else if (ClearTime <= 60) {
		MapDisp();
		IronBallDisp();		//鉄球の描画処理
		PlayerDisp();
		ClearTime++;
	}
	
}


void DrawGameOver(void) {			//ゲームオーバー描画処理
	DrawGraph(0, 0, g_GameOverImage, FALSE);

	//メニューカーソル移動処理
	if (--g_OverTime <= 0) {
		if (g_KeyFlg & PAD_INPUT_DOWN) {

			if (++g_OverNumber > 1) {
				g_OverNumber = 0;
			}
			g_OverTime = 10;
		}
		if (g_KeyFlg & PAD_INPUT_UP) {
			if (--g_OverNumber < 0) {
				g_OverNumber = 1;
			}
			g_OverTime = 10;
		}

	}

	//ｚキーでメニュー選択
	if (--g_OverTime <= 0) {
		if (g_KeyFlg & PAD_INPUT_A) {
			if (g_OverNumber == 1) {
				g_GameState = GAME_END;
			}
			else {
				g_GameState = 0;

			}
			
			g_MenuTime = 20;
		}
	}
	
	//タイトル画像表示
	/*if (++titleTime >= 60) {
		titleTime = 0;
	}*/

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
	g_OvreY = g_OverNumber * 130;

	/*DrawString(265, 263, "ゲームスタート", 0xffffff);
	DrawString(265, 315, "ゲームヘルプ", 0xffffff);
	DrawString(265, 367, "終了", 0xffffff);*/

	DrawTriangle(60, 365 + g_OvreY, 80, 400 + g_OvreY,
		60, 435 + g_OvreY, GetColor(255, 0, 0), TRUE);
	DrawFormatString(0, 0, 0xffffff, "mouseX = %d   Y = %d", g_MouseX, g_MouseY);
}