#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"

#include "PlayerAndIronBall.h"
#include "IronToEnemy.h"

#define WALK_ENEMY_SIZE 48	//敵の大きさ
#define SHOOT_ENEMY_SIZE 64
#define ENEMY_MAX 10
#define  Bullet_MAX 3

/**************************************************
*		変数の宣言
***************************************************/
enemyInfo g_Enemy[ENEMY_MAX];			//敵の情報を持った変数
BulletInfo Bullet;			//弾丸をMAXの数ぶん配列を作る
  


/***************************************************
*　　敵の構造体の関数の定義
*****************************************************/

//////////////////////////////////////////////
/////////////歩く敵の処理////////////////////
/////////////////////////////////////////////

void enemyInfo::WalkInit() {                 // 敵の初期化
	x = 24 * MAP_SIZE;							 // 敵のX座標の初期位置(マップチップの場所)
	y = 14 * MAP_SIZE;								    // 敵のY座標の初期位置(マップチップの場所)
	w = WALK_ENEMY_SIZE;						//敵の横幅
	h = WALK_ENEMY_SIZE;						//敵の縦

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, WALK_ENEMY_SIZE, WALK_ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//左向きから始める
	picDir = true;

	speed = 2;						//敵のスピード

	Life = 3;					//敵のHP　とりま３


	DispFlg = TRUE;					//敵を表示


}


void enemyInfo::WalkMove(){

	static int AnmCnt = 0;

	const int FrmMax = 10;		//アニメーションフレームの間



	if (DispFlg) {//
		
		if (g_MapChip[(y + h) / MAP_SIZE][x / MAP_SIZE] == 1) {			//自分の足元を見て空中だったら
			y += GRAVITY;
		}


		if (direct < 0) picDir = false;		//左向きなら
		else picDir = true;					//右向きなら

		//x = (chipX * MAP_SIZE - MapDrawPointX) + direct * speed;				//移動のスピードを敵キャラに入れる
		x += direct * speed;

		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}

	}

}



////////////////////////////////////////////
//////////撃つ敵の処理//////////////////////
/////////////////////////////////////////////

void enemyInfo::ShootInit() {                 // 撃つ敵の初期化
	x = 24 * MAP_SIZE;							 // 敵のX座標の初期位置(マップチップの場所)
	y = 15 * MAP_SIZE;								    // 敵のY座標の初期位置(マップチップの場所)
	w = SHOOT_ENEMY_SIZE / 2;						//敵の横幅
	h = SHOOT_ENEMY_SIZE;						//敵の縦

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, SHOOT_ENEMY_SIZE, SHOOT_ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//左向きから始める

	speed = 0;						//敵のスピード
	picDir = true;

	DispFlg = TRUE;					//敵を表示


}


void enemyInfo::ShootMove() {		//撃つ敵の処理

	static int AnmCnt = 0;
	const int FrmMax = 10;		//アニメーションフレームの間



	if (DispFlg) {//
		if (g_MapChip[(y + h) / MAP_SIZE][x / MAP_SIZE] == 1) {			//自分の足元を見て空中だったら
			y += GRAVITY;
		}

		if (direct < 0) picDir = false;		//左向きなら
		else picDir = true;					//右向きなら


		//EnemyShoot();

		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}

	}

}

void enemyInfo::Disp() {			//敵の表示処理

	if (DispFlg) {		//敵表示
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,	// + MapDrawPointX - MapX * MAP_SIZE
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0xff0000, true);
		//DrawRotaGraphFast2(x, y,0,0,1,0, pic[anm], true,picDir);
	}
	else {				//敵非表示

	}
}

//////////////////////////////////////////////
////////////弾丸の関数の定義///////////////////
//////////////////////////////////////////////
void BulletInfo::Init() {			//弾丸の初期化処理
	//x = g_Enemy.x;
	//y = g_Enemy.y + (g_Enemy.h / 2);		//敵の真ん中ぐらいの高さから

	Speed = 4;							//弾丸のスピード


	DispFlg = true;			//表示フラグをオンにする
}

void BulletInfo::Move() {			//弾丸の処理
	if (DispFlg) {
		x += direct * Speed;

		if (x < 0 || x > WIDTH) DispFlg = false;
	}
	else {

	}
}

void BulletInfo::Disp() {			//弾丸の表示処理
	if (DispFlg) {
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0xff0000, true);
	}
}


/**************************************************
*　敵の関数の定義
***************************************************/
void enemyDisp() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_Enemy[i].Disp();
	}
	
	

	//EnemyShoot();
}

void enemyMove() {
	static int Initflg = true;

	if (Initflg) {
		//g_Enemy.ShootInit();
		g_Enemy[0].WalkInit();

		Initflg = false;
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		g_Enemy[i].WalkMove();

		if (EnemyCheckHit(g_Enemy[i])) {	//壁だったら
			g_Enemy[i].direct *= -1;			//移動の向きを反転させる
		}
	}
		
}

bool EnemyCheckHit(enemyInfo enemy) {
	int i = 0, j = 0, k = 0, l = 0, w = 0, z = 0;		//補正値用変数
	//的の位置（左）がマップをまたいでいる
	while (enemy.x / MAP_SIZE - k >= WIDTH) {
		k += WIDTH;
		l += HEIGHT;
	}

	//敵の位置(右)がマップをまたいでいる
	if ((enemy.x + enemy.h) / MAP_SIZE - k >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//真ん中の位置がマップをまたいでいる
	if ((enemy.x + enemy.h / 2) / MAP_SIZE - k >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}


	if (enemy.picDir)			//右向きの処理
	{
		if (g_MapChip[(enemy.y) / MAP_SIZE + l + j][(enemy.x + enemy.w) / MAP_SIZE - k - w] != 1	//右上
			|| g_MapChip[(enemy.y +( enemy.h /2) ) / MAP_SIZE + l + j][(enemy.x + enemy.w) / MAP_SIZE - k - w] != 1)	//右下
			 {return true;}
	}
	else {
		if (g_MapChip[(enemy.y) / MAP_SIZE + l][(enemy.x) / MAP_SIZE - k] != 1				//左上
			|| g_MapChip[(enemy.y +( enemy.h / 2) ) / MAP_SIZE + l][(enemy.x) / MAP_SIZE - k] != 1)	//左下
		{return true;}

	}
	if (IronToEnemy(enemy)) return true;

	return false;
}

//敵が弾丸を飛ばす処理
//void EnemyShoot() {
//
//	if (g_NowKey & PAD_INPUT_DOWN
//		&& !Bullet->DispFlg) {
//		Bullet->Init();
//	}
//
//	if (Bullet->DispFlg) {
//		Bullet->Move();
//	}
//	else {
//
//	}
//
//}