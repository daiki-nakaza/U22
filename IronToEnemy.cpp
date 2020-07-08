#include "DxLib.h"

#include "IronToEnemy.h"
#include "Map.h"


bool IronToEnemy(enemyInfo enemy) {

	if (enemy.picDir) {			//右向きの処理
		//次の移動の場所が鉄球と被っていたらtrueを返す
		if ((enemy.y + enemy.h) / MAP_SIZE == g_IronBall.y / MAP_SIZE + MapY
			&& (((enemy.x + enemy.w - MapDrawPointX) + (enemy.direct * enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x - g_IronBall.r) / MAP_SIZE + MapX) return true;
	}
	else {							//左向きの処理
		//次の移動の場所が鉄球と被っていたらtrueを返す
		if ((enemy.y + enemy.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
			&& (((enemy.x - MapDrawPointX) + (enemy.direct * enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x + g_IronBall.r) / MAP_SIZE + MapX) return true;
	}



	return false;
}