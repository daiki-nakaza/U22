#include "DxLib.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Define.h"
#include "Map.h"
#include "IronToEnemy.h"


//////////////////////////////////////////////
////////////弾丸の関数の定義///////////////////
//////////////////////////////////////////////
void BulletInfo::Init(const int Ex, const int Ey) {			//弾丸の初期化処理
	const int valanceY = 10;		//弾丸の高さの補正値

	Speed = 4;							//弾丸のスピード

	x = Ex;		//敵キャラの座標にSet
	y = Ey - valanceY;

	w = BULLET_W;
	h = BULLET_H;

	

	DispFlg = true;			//表示フラグをオンにする
}

void BulletInfo::Move(const int dir) {			//弾丸の処理
	if (DispFlg) {
		direct = dir;

		if (direct < 0) picDir = false;		//左向きなら
		else picDir = true;					//右向きなら

		x += dir * Speed;

		if (x < 0 || x > WIDTH * MAP_SIZE) DispFlg = false;		//画面外に出たら表示フラグをfalseにする
		
	}
	else {

	}
}

void BulletInfo::Disp() {			//弾丸の表示処理
	if (DispFlg) {
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0x000000, true);
	}
}
