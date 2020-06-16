#include "DxLib.h"


#include "GameMain.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"



void DrawGameMain() {
	MapDisp();			//マップの描画
	MapMove();			//スクリーンの処理

	PlayerMove();
	PlayerDisp();


	enemyDisp();		//敵の描画処理
	enemyMove();		//敵の処理
}

