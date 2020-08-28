#include "DxLib.h"


#include "GameMain.h"
#include "GameMenu.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "accessory.h"
#include "UI.h"

int reset = 0;

void DrawGameMain() {
	//static int i = 0;
	if (reset++ == 0) {
		Stage = 1;
		PlayerInit();
		MapChipInit();
		enemyInit();
		g_IronBall.HoldFlg = false;
		g_IronBall.ThrowFlg = false; 
		g_IronBall.Init();
		Locka.Init();
		PlaySoundMem(g_Stage1, DX_PLAYTYPE_LOOP,true); //
	}
	else if (reset++ == 5) {//ライフ以外のリセット
	}



	MapDisp();			//マップの描画
	MapMove();			//スクリーンの処理

	IronBallDisp();		//鉄球の描画処理
	IronBallMove();		//	鉄球の動きの処理
	
	
	PlayerMove();
	PlayerDisp();


	enemyDisp();		//敵の描画処理
	enemyMove();		//敵の処理

	PlayerAttack();		//プレイヤー攻撃

	HUDDisp();


	if (g_KeyFlg & PAD_INPUT_8) {//Wキー
		if (PoseTime <= 0) {
			g_GameState = GAME_MENU;
			PoseTime = 90;
		}
	}
	PoseTime--;
}

