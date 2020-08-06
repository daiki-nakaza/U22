#include "DxLib.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Define.h"
#include "Map.h"
#include "IronToEnemy.h"

#include <time.h>

//////////////////////////////////////////////
////////////弾丸の関数の定義///////////////////
//////////////////////////////////////////////

//真っすぐ飛ぶ弾丸の関数定義
void NormalBullet::Init(const int Ex, const int Ey) {			//弾丸の初期化処理
	const int valanceY = 10;		//弾丸の高さの補正値

	Speed = 4;							//横の弾丸のスピード

	x = Ex;		//敵キャラの座標にSet
	y = Ey - valanceY;

	w = BULLET_W;
	h = BULLET_H;

	

	DispFlg = true;			//表示フラグをオンにする
}

void NormalBullet::Move(const int dir) {			//弾丸の処理

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


//プレイヤーの頭に向かって飛ぶ弾丸
void LockBullet::Init(const int Ex, const int Ey) {			//弾丸の初期化処理
	const int valanceY = 10;		//弾丸の高さの補正値
	int rangeX = abs(GetPlayerX() - Ex);
	int rangeY = abs(GetPlayerY() - Ey);

	Speed = 4;							//横の弾丸のスピード

	SpeedY = (float)rangeY / ((float)rangeX / (float)Speed);

	x = Ex;		//敵キャラの座標にSet
	y = Ey - valanceY;

	w = BULLET_W;
	h = BULLET_H;



	DispFlg = true;			//表示フラグをオンにする
}


//
void LockBullet::Move(const int dir) {			//弾丸の処理
	if (DispFlg) {
		direct = dir;

		if (direct < 0) picDir = false;		//左向きなら
		else picDir = true;					//右向きなら

		x += dir * Speed;

		(y) += -dir * SpeedY;

		if (x < 0 || x > WIDTH * MAP_SIZE) DispFlg = false;		//画面外に出たら表示フラグをfalseにする

	}
	else {

	}
}

//上に向かって飛んでく弾丸の初期化処理
void ChargeBullet::Init(const int Ex, const int Ey) {			//弾丸の初期化処理
	const int valanceY = 10,valanceX = SHOOT_ENEMY_SIZE / 2;		//弾丸の補正値
	const int SizeW = 10, SizeH = 20;

	Speed = 8;							//横の弾丸のスピード

	srand((unsigned int)time(NULL) + rand()); // 現在時刻の情報で初期化

	type = (rand() % 2) + 2;

	if (type == 2) Cr = 0xff0000;
	else           Cr = 0x00ff00;

	sequence = 1;			//打上にSet

	x = Ex + valanceX;		//敵キャラの座標にSet
	y = Ey - valanceY;

	w = SizeW;
	h = SizeH;


	DispFlg = true;			//表示フラグをオンにする
}

//上に向かって飛んでく弾丸の処理
void ChargeBullet::Move(const int dir) {			//弾丸の処理
	static int LockX;
	int Replace;		//大きさを入れ替える用の変数

	if (DispFlg) {
		direct = dir; 
		//if (x < 0 || x > WIDTH * MAP_SIZE) DispFlg = false;		//画面外に出たら表示フラグをfalseにする
		if (y > HEIGHT * MAP_SIZE) DispFlg = false;

		switch (sequence)
		{
		case 1:		//上に打ち上げる処理
			y -= Speed;

			if (y + h < -50) {		//上に行ったら右か左にSet
				LockX = GetPlayerX();
				y = 0;

				Replace = w;
				w = h;
				h = Replace;

				if (type == 2)x =LockX + (HEIGHT - ((HEIGHT * MAP_SIZE) - GetPlayerY()) / MAP_SIZE) * MAP_SIZE;
				else          x =LockX - (HEIGHT - ((HEIGHT * MAP_SIZE) - GetPlayerY()) / MAP_SIZE)* MAP_SIZE;

				sequence = type;
			}
			break;
		case 2:		//右から飛んでくる処理
			y += Speed;
			x -= Speed;

			break;
		case 3:		//左から飛んでくる処理
			y += Speed;
			x += Speed;

			break;
		default:
			break;
		}
	}
	else {

	}
}


//レーザーの弾	
void RazerBullet::Init(const int Ex, const int Ey) {
	const int valanceY = 10;		//弾丸の高さの補正値

	Speed = 4;							//横の弾丸のスピード

	x = Ex;		//敵キャラの座標にSet
	y = Ey - valanceY;

	w = BULLET_W;
	h = BULLET_H;



	DispFlg = true;			//表示フラグをオンにする
}

void RazerBullet::Move(int direct) {

}





//弾丸の描画処理
void BulletInfo::Disp() {			//弾丸の表示処理
	if (DispFlg) {
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0x000000, true);
	}
}
void ChargeBullet::Disp() {			//上にむっかていく弾丸の表示処理
	if (DispFlg) {
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, Cr, true);
	}
}


