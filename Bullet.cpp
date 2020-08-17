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
	MoveSum = 0;

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
		MoveSum += Speed;

		if (CheckWindow() || CheckHitBall())DispFlg = false;

		if (CheckHitPlayer()) {		//プレイヤーにあたっていたら
			DispFlg = false;
		}
	}
	else {

	}
}


//プレイヤーの頭に向かって飛ぶ弾丸
void LockBullet::Init(const int Ex, const int Ey) {			//弾丸の初期化処理
	const int valanceY = 10;		//弾丸の高さの補正値
	int rangeX = abs(PlayerX - Ex + MapDrawPointX - MapX * MAP_SIZE);
	int rangeY = (PlayerY - Ey + MapDrawPointY - MapY * MAP_SIZE) + (CHA_SIZE_Y / 2);

	Speed = 4;							//横の弾丸のスピード

	SpeedY = rangeY / (rangeX / Speed);

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

		if (CheckWindow() || CheckHitBall())DispFlg = false;

		if (CheckHitPlayer()) {		//プレイヤーにあたっていたら
			DispFlg = false;
		}
	}
	else {

	}
}


//上に向かって飛んでく弾丸の初期化処理
void ChargeBullet::Init(const int Ex, const int Ey) {			//弾丸の初期化処理
	const int valanceY = 10,valanceX = SHOOT_ENEMY_SIZE / 2;		//弾丸の補正値
	const int SizeW = MAP_SIZE, SizeH = MAP_SIZE;

	Speed = 8;							//横の弾丸のスピード

	srand((unsigned int)time(NULL) + rand()); // 現在時刻の情報で初期化

	type = (rand() % 2) + 2;
	anm = 0;

	if (type == 2) LoadDivGraph("images/Red bulletAll.png", 2, 2, 1, MAP_SIZE, MAP_SIZE, pic);
	else           LoadDivGraph("images/Green bulletAll.png", 2, 2, 1, MAP_SIZE, MAP_SIZE, pic);

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
		if (CheckHitBall())DispFlg = false;

		if (CheckHitPlayer()) {		//プレイヤーにあたっていたら
			DispFlg = false;
		}
		if (CheckWindow() && sequence > 1 && y > (WIDTH / 2 * MAP_SIZE))DispFlg = false;

		switch (sequence)
		{
		case 1:		//上に打ち上げる処理
			y -= Speed;

			if (y + h < -50) {		//上に行ったら右か左にSet
				LockX = GetPlayerX() + CHA_SIZE_X/2;
				y = 0 + CHA_SIZE_Y / 2;

				Replace = w;
				w = h;
				h = Replace;
				anm++;

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
	const int valanceY = 4;		//弾丸の高さの補正値

	Speed = 8;							//横の弾丸のスピード

	x = Ex + (RAZER_ENEMY_SIZE / 4);		//敵キャラの座標にSet
	y = Ey - valanceY;

	w = BULLET_W;
	h = MAP_SIZE;

	BWidth = 0;
	MoveSum = 0;

	pic = LoadGraph("images/Laser.png");

	DispFlg = true;			//表示フラグをオンにする
}

void RazerBullet::Move(int direct) {
	const int rangeX = MAP_SIZE * WIDTH;		//レーザーの長さ

	if (DispFlg) {
		x += direct * Speed;
		MoveSum += Speed;

		if(BWidth < rangeX) BWidth -= direct * Speed;

		if (x + BWidth + MapDrawPointX - MapX * MAP_SIZE < 0) {
			DispFlg = false;
		}
	}
}





//弾丸の描画処理
void BulletInfo::Disp() {			//弾丸の表示処理
	if (DispFlg) {
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0x000000, true);
	}
}

void RazerBullet::Disp() {			//上にむっかていく弾丸の表示処理
	if (DispFlg) {
		//DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
		//	x + BWidth + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0x00ff00, true);
		DrawExtendGraph(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
			x + BWidth + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, pic, true);
	}
}

void ChargeBullet::Disp() {			//上にむっかていく弾丸の表示処理
	if (DispFlg) {
		DrawGraph(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,pic[anm], true);
	}
}



/************************************************************
***********************当たり判定****************************
************************************************************/

bool BulletInfo::CheckHitBall() {		//鉄球との当たり判定
	if (y - MapDrawPointY - MapY * MAP_SIZE < (g_IronBall.y + MapDrawPointY - MapY * MAP_SIZE) + g_IronBall.r
		&& y + h - MapDrawPointY - MapY * MAP_SIZE > (g_IronBall.y + MapDrawPointY - MapY * MAP_SIZE) - g_IronBall.r) {
		if ( (x + MapDrawPointX - MapX * MAP_SIZE) < ( (g_IronBall.x + MapDrawPointX - MapX * MAP_SIZE) + g_IronBall.r)
			&& (x + w + MapDrawPointX - MapX * MAP_SIZE) > ( (g_IronBall.x + MapDrawPointX - MapX * MAP_SIZE) - g_IronBall.r) ) {
			return true;
		}
	}

	return false;
}


//当たり判定
bool BulletInfo::CheckHitPlayer() {		//プレイヤーとの当たり判定

	if (y - MapDrawPointY - MapY * MAP_SIZE < PlayerY + CHA_SIZE_Y
		&& y + h - MapDrawPointY - MapY * MAP_SIZE > PlayerY) {
		if (x + MapDrawPointX - MapX * MAP_SIZE < (PlayerX + CHA_SIZE_X)
			&& x + w + MapDrawPointX - MapX * MAP_SIZE >(PlayerX)) {
			return true;
		}
	}
	return false;
}


bool BulletInfo::CheckWindow() {		//画面に入っているか

	if ((x + h + MapDrawPointX - MapX * MAP_SIZE < -1 * ( (WIDTH / 8) * MAP_SIZE))
		|| (x + MapDrawPointX - MapX * MAP_SIZE > WIDTH * MAP_SIZE + (WIDTH / 8 * MAP_SIZE))) {
		return true;
	}

	return false;
}