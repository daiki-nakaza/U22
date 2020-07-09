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


bool IronToEnemy(BulletInfo Bullet) {			//鉄球と敵の弾丸の当たり判定
	if (Bullet.picDir) {			//右向きの処理
		//次の移動の場所が鉄球と被っていたらtrueを返す
		if ((Bullet.y + Bullet.h) / MAP_SIZE == g_IronBall.y / MAP_SIZE + MapY
			&& (((Bullet.x + Bullet.w - MapDrawPointX) + (Bullet.direct * Bullet.Speed)) / MAP_SIZE) + MapX == (g_IronBall.x - g_IronBall.r) / MAP_SIZE + MapX) return true;
	}
	else {							//左向きの処理
		//次の移動の場所が鉄球と被っていたらtrueを返す
		if ((Bullet.y + Bullet.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
			&& (((Bullet.x - MapDrawPointX) + (Bullet.direct * Bullet.Speed)) / MAP_SIZE) + MapX == (g_IronBall.x + g_IronBall.r) / MAP_SIZE + MapX) return true;
	}

	if (Bullet.picDir) {			//右向きの処理
		//次の移動の場所が鉄球と被っていたらtrueを返す
		if ((Bullet.y + Bullet.h) / MAP_SIZE == PlayerY + (CHA_SIZE_Y/2) / MAP_SIZE + MapY
			&& (((Bullet.x + Bullet.w - MapDrawPointX) + (Bullet.direct * Bullet.Speed)) / MAP_SIZE) + MapX == PlayerX / MAP_SIZE + MapX) return true;
	}
	else {							//左向きの処理
		//次の移動の場所が鉄球と被っていたらtrueを返す
		if ((Bullet.y + Bullet.h + MapDrawPointY) / MAP_SIZE + MapY == PlayerY + (CHA_SIZE_Y / 2) / MAP_SIZE + MapY
			&& (((Bullet.x - MapDrawPointX) + (Bullet.direct * Bullet.Speed)) / MAP_SIZE) + MapX == PlayerX + CHA_SIZE_X / MAP_SIZE + MapX) return true;
	}

	return false;
}