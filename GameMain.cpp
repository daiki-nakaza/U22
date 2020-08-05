#include "DxLib.h"


#include "GameMain.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "accessory.h"
#include "UI.h"



void DrawGameMain() {

	static int i = 0;
	if (i++ == 0) {
		PlayerInit();
		MapChipInit();
	}

	MapDisp();			//マップの描画
	MapMove();			//スクリーンの処理

	PlayerMove();
	PlayerDisp();

	IronBallDisp();		//鉄球の描画処理
	IronBallMove();		//	鉄球の動きの処理


	enemyDisp();		//敵の描画処理
	enemyMove();		//敵の処理

	PlayerAttack();		//プレイヤー攻撃

	HUDDisp();
}

