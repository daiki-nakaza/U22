#include "DxLib.h"


#include "GameMain.h"
#include "Map.h"
#include "Enemy.h"



void DrawGameMain() {
	MapDisp();			//マップの描画
	MapMove();			//スクリーンの処理

	enemyDisp();		//敵の描画処理
	enemyMove();		//敵の処理
}

