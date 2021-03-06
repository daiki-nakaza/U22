#include "DxLib.h"

#include "Define.h" 
#include "Player.h" 
#include "Map.h"
#include "GameEnd.h" 
#include "GameMain.h"
#include "GameTitle.h"
#include "accessory.h"
#include "Enemy.h"

int PoseTime = 30;
int g_PoseImage;

void DrawMenu() {			//ゲームメニュー描画処理

	MapDisp();
	IronBallDisp();		//鉄球の描画処理
	PlayerDisp();
	enemyDisp();
	DrawGraph(0, 0, g_PoseImage, FALSE);


	if (g_KeyFlg & PAD_INPUT_8) {//Wキー
		if (PoseTime <= 0) {
			g_GameState = GAME_MAIN;
			PoseTime = 30;
			PlaySoundMem(g_Stage1, DX_PLAYTYPE_LOOP,false); //
		}
	}

	PoseTime--;
}