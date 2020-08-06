#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"

#include "PlayerAndIronBall.h"
#include "IronToEnemy.h"


/**************************************************
*		変数の宣言
***************************************************/
//エラー防止用（後で消します）
enemyInfo g_Enemy[ENEMY_MAX];

WalkEnemy g_WalkEnemy[ENEMY_MAX];					//歩く敵
ShootEnemy g_ShootEnemy[ENEMY_MAX];					//真っすぐ撃つ敵
LockShootEnemy g_LockShootEnemy[ENEMY_MAX];			//狙い撃つ敵
TankEnemy g_TankEnemy[ENEMY_MAX];					//戦車の敵
RazerEnemy g_RazerEnemy[ENEMY_MAX];					//波動砲の敵

  


/***************************************************
*　　敵の構造体の関数の定義
*****************************************************/

void enemyInfo::Move() {
	/******************************************************
		*勝手に書きました
		******************************************************/
	if (outtime < 0) {
		outtime = 0;
	}
	if (Life <= 0) {
		DispFlg = false;
	}
	if (g_MapChip[(y + h) / MAP_SIZE][x / MAP_SIZE] == 1) {			//自分の足元を見て空中だったら
		y += GRAVITY;
	}
}

void enemyInfo::Disp() {			//敵の表示処理

	if (DispFlg) {		//敵表示
		//DrawBox(x + MapDrawPointX - MapX * MAP_SIZE,
		//	y - MapDrawPointY - MapY * MAP_SIZE,
		//	(x + MapDrawPointX - MapX * MAP_SIZE) + w,
		//	(y - MapDrawPointY - MapY * MAP_SIZE) + h, 0x000000, true);
		DrawGraph(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE, pic, true);
	}
	else {				//敵非表示

	}
}



//////////////////////////////////////////////
/////////////歩く敵の処理////////////////////
/////////////////////////////////////////////

void WalkEnemy::Init() {                 // 敵の初期化
	x = 24 * MAP_SIZE;							 // 敵のX座標の初期位置(マップチップの場所)
	y = 14 * MAP_SIZE;								    // 敵のY座標の初期位置(マップチップの場所)
	w = WALK_ENEMY_SIZE;						//敵の横幅
	h = WALK_ENEMY_SIZE;						//敵の縦

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, WALK_ENEMY_SIZE, WALK_ENEMY_SIZE, pic);
	pic = LoadGraph("images/Zako.png");

	anm = 0;

	direct = -1;						//左向きから始める
	picDir = true;

	AttckFlg = false;

	speed = 2;						//敵のスピード

	Life = 3;					//敵のHP　とりま３

	type = 0;					//敵のタイプ

	outtime = 0;				//１度攻撃をもらったら無敵


	DispFlg = TRUE;					//敵を表示


}


void WalkEnemy::WalkMove(){

	static int AnmCnt = 0;

	const int FrmMax = 10;		//アニメーションフレームの間



	if (DispFlg) {//
		

		if (direct < 0) picDir = false;		//左向きなら
		else picDir = true;					//右向きなら

		//x = (chipX * MAP_SIZE - MapDrawPointX) + direct * speed;				//移動のスピードを敵キャラに入れる
		x += direct * speed;

		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}
		Move();			//敵共通の関数

	}

}



////////////////////////////////////////////
//////////撃つ敵の処理//////////////////////
/////////////////////////////////////////////

void ShootEnemy::Init() {                 // 撃つ敵の初期化
	x = 24 * MAP_SIZE;							 // 敵のX座標の初期位置(マップチップの場所)
	y = 15 * MAP_SIZE;								    // 敵のY座標の初期位置(マップチップの場所)
	w = SHOOT_ENEMY_SIZE;						//敵の横幅
	h = SHOOT_ENEMY_SIZE;						//敵の縦

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, SHOOT_ENEMY_SIZE, SHOOT_ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//左向きから始める

	speed = 0;						//敵のスピード
	picDir = true;

	Life = 3;					//敵のHP　とりま３

	type = 1;					//敵のタイプ

	AttckFlg = false;			//攻撃用のフラグ

	pic = LoadGraph("images/teki.png");

	DispFlg = TRUE;					//敵を表示


}


void ShootEnemy::ShootMove() {		//撃つ敵の処理

	static int AnmCnt = 0;
	const int FrmMax = 10;		//アニメーションフレームの間

	const int Rate = 20;		//発射レート
	const int ReloadTime = 180;			//リロード時間　大体３秒


	static int Firecnt = 0;		 //発射のカウント
	static int BulletCnt = 0;		//３発連続で弾を発射させる
	static int ReloadCnt = 0;		//リロードの時間カウント


	if (DispFlg) {//

		//if(DirCheck)

		if (direct < 0) picDir = false;		//左向きなら
		else picDir = true;					//右向きなら



		if (++AnmCnt >= FrmMax) {				//アニメーションフレーム
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}
		if (Firecnt++ >= Rate
			&& BulletCnt < Bullet_MAX) {
			Bullet[BulletCnt].Init(x, y + h / 2);			//弾を飛ばす間隔
			BulletCnt++;
			Firecnt = 0;
		}

		if (!Bullet[0].DispFlg
			&& !Bullet[1].DispFlg
			&& !Bullet[2].DispFlg
			&& ReloadCnt > ReloadTime) {
			BulletCnt = 0;		//弾の表示フラグがすべてoffなら撃てるようになる
			ReloadCnt = 0;
		}
		if (ReloadCnt++ <= ReloadTime) {}

		for (int i = 0; i < Bullet_MAX; i++) {
			Bullet[i].Disp();
			Bullet[i].Move(direct);			//弾丸の処理
			if (IronToBullet(Bullet[i])) {
				Bullet[i].DispFlg = false;		//鉄球に当たっていたらとりま消す
			}
			if (PlayerToEnemy(Bullet[i])) {
				Bullet[i].DispFlg = false;		//鉄球に当たっていたらとりま消す
			}
		}

		Move();			//敵共通の関数

	}


}


////////////////////////////////////////////
//////////狙い撃つ敵の処理//////////////////////
/////////////////////////////////////////////

//狙い撃つ敵の初期化
void LockShootEnemy::Init() {
	x = 15 * MAP_SIZE;							 // 敵のX座標の初期位置(マップチップの場所)
	y = 8 * MAP_SIZE;								    // 敵のY座標の初期位置(マップチップの場所)
	w = SHOOT_ENEMY_SIZE;						//敵の横幅
	h = SHOOT_ENEMY_SIZE;						//敵の縦

	anm = 0;

	direct = -1;						//左向きから始める

	speed = 0;						//敵のスピード
	picDir = true;

	Life = 3;					//敵のHP　とりま３

	type = 1;					//敵のタイプ

	AttckFlg = false;			//攻撃用のフラグ

	pic = LoadGraph("images/teki.png");

	DispFlg = TRUE;					//敵を表示



}


void LockShootEnemy::LockShootMove() {			//撃つ敵の処理


	static int AnmCnt = 0;
	const int FrmMax = 10;		//アニメーションフレームの間

	const int Rate = 20;		//発射レート
	const int ReloadTime = 180;			//リロード時間　大体３秒


	static int Firecnt = 0;		 //発射のカウント
	static int BulletCnt = 0;		//３発連続で弾を発射させる
	static int ReloadCnt = 0;		//リロードの時間カウント


	if (DispFlg) {//

		//if(DirCheck)

		if (direct < 0) picDir = false;		//左向きなら
		else picDir = true;					//右向きなら



		if (++AnmCnt >= FrmMax) {				//アニメーションフレーム
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}
		if (Firecnt++ >= Rate
			&& BulletCnt < Bullet_MAX) {
			Bullet[BulletCnt].Init(x, y + h / 2);			//弾を飛ばす間隔
			BulletCnt++;
			Firecnt = 0;
		}

		if (!Bullet[0].DispFlg
			&& !Bullet[1].DispFlg
			&& !Bullet[2].DispFlg
			&& ReloadCnt > ReloadTime) {
			BulletCnt = 0;		//弾の表示フラグがすべてoffなら撃てるようになる
			ReloadCnt = 0;
		}
		if (ReloadCnt++ <= ReloadTime) {}

		for (int i = 0; i < Bullet_MAX; i++) {
			Bullet[i].Disp();
			Bullet[i].Move(direct);			//弾丸の処理
			if (IronToBullet(Bullet[i])) {
				Bullet[i].DispFlg = false;		//鉄球に当たっていたらとりま消す
			}
			if (PlayerToEnemy(Bullet[i])) {
				Bullet[i].DispFlg = false;		//鉄球に当たっていたらとりま消す
			}
		}

		Move();			//敵共通の関数

	}

}

//戦車の敵(上に向かって弾を飛ばす奴)
void TankEnemy::Init() {
	x = 15 * MAP_SIZE;							 // 敵のX座標の初期位置(マップチップの場所)
	y = 8 * MAP_SIZE;								    // 敵のY座標の初期位置(マップチップの場所)
	w = TANK_ENEMY_SIZE;						//敵の横幅
	h = TANK_ENEMY_SIZE;						//敵の縦幅

	anm = 0;

	direct = -1;						//左向きから始める

	speed = 0;						//敵のスピード
	picDir = true;

	Life = 3;					//敵のHP　とりま３

	type = 1;					//敵のタイプ

	AttckFlg = false;			//攻撃用のフラグ

	pic = LoadGraph("images/Enemy.Tank.png");

	DispFlg = TRUE;					//敵を表示


}

void TankEnemy::TankMove() {


	static int AnmCnt = 0;
	const int FrmMax = 10;		//アニメーションフレームの間

	const int Rate = 40;		//発射レート
	const int ReloadTime = 240;			//リロード時間　


	static int Firecnt = 0;		 //発射のカウント
	static int BulletCnt = 0;		//３発連続で弾を発射させる
	static int ReloadCnt = 0;		//リロードの時間カウント


	if (DispFlg) {//

		//if(DirCheck)

		if (direct < 0) picDir = false;		//左向きなら
		else picDir = true;					//右向きなら



		if (++AnmCnt >= FrmMax) {				//アニメーションフレーム
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}
		if (Firecnt++ >= Rate
			&& BulletCnt < Bullet_MAX) {
			Bullet[BulletCnt].Init(x, y + h / 2);			//弾を飛ばす間隔
			BulletCnt++;
			Firecnt = 0;
		}

		if (!Bullet[0].DispFlg
			&& !Bullet[1].DispFlg
			&& !Bullet[2].DispFlg
			&& ReloadCnt > ReloadTime) {
			BulletCnt = 0;		//弾の表示フラグがすべてoffなら撃てるようになる
			ReloadCnt = 0;
		}
		if (ReloadCnt++ <= ReloadTime) {}

		for (int i = 0; i < Bullet_MAX; i++) {
			Bullet[i].Disp();
			Bullet[i].Move(direct);			//弾丸の処理
			if (IronToBullet(Bullet[i])) {
				Bullet[i].DispFlg = false;		//鉄球に当たっていたらとりま消す
			}
			if (PlayerToEnemy(Bullet[i])) {
				Bullet[i].DispFlg = false;		//鉄球に当たっていたらとりま消す
			}
		}

		Move();			//敵共通の関数

	}
}

//波動砲を撃つ敵の関数定義
void RazerEnemy::Init(){
	x = 15 * MAP_SIZE;							 // 敵のX座標の初期位置(マップチップの場所)
	y = 8 * MAP_SIZE;								    // 敵のY座標の初期位置(マップチップの場所)
	w = TANK_ENEMY_SIZE;						//敵の横幅
	h = TANK_ENEMY_SIZE;						//敵の縦幅

	anm = 0;

	direct = -1;						//左向きから始める

	speed = 0;						//敵のスピード
	picDir = true;

	Life = 3;					//敵のHP　とりま３

	type = 1;					//敵のタイプ

	AttckFlg = false;			//攻撃用のフラグ

	LoadDivGraph("images/HadouhouAll.png",3,3,1, TANK_ENEMY_SIZE, TANK_ENEMY_SIZE,pic);

	//pic[2] = LoadGraph("images/Hadouhou2.png");

	DispFlg = TRUE;					//敵を表示

}

void RazerEnemy::ShotMove() {

	static int AnmCnt = 0;

	const int FrmMax = 10;		//アニメーションフレームの間



	if (DispFlg) {//


		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}
		Move();			//敵共通の関数

	}
}

void RazerEnemy::Disp() {

	if (DispFlg) {		//敵表示
		//DrawBox(x + MapDrawPointX - MapX * MAP_SIZE,
		//	y - MapDrawPointY - MapY * MAP_SIZE,
		//	(x + MapDrawPointX - MapX * MAP_SIZE) + w,
		//	(y - MapDrawPointY - MapY * MAP_SIZE) + h, 0x000000, true);
		DrawGraph(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE, pic[2], true);
	}
	else {				//敵非表示

	}
}
/**************************************************
*　敵の関数の定義
***************************************************/

void enemyInit() {			//敵の初期化処理

		//g_LockShootEnemy[0].Init();

}

void enemyDisp() {

	for (int i = 0; i < ENEMY_MAX; i++) {
		g_WalkEnemy[i].Disp();
		g_ShootEnemy[i].Disp();
		g_LockShootEnemy[i].Disp();
		g_TankEnemy[i].Disp();
		g_RazerEnemy[i].Disp();
	}
	
	//EnemyShoot();
}




void enemyMove() {
	static bool Initflg = true;

	if (Initflg) {
		g_RazerEnemy[0].Init();
		Initflg = false;
	}


	for (int i = 0; i < ENEMY_MAX; i++) {

		g_WalkEnemy[i].WalkMove();
		g_ShootEnemy[i].ShootMove();
		g_LockShootEnemy[i].LockShootMove();
		g_TankEnemy[i].TankMove();
		g_RazerEnemy[i].ShotMove();

		
	}	
}

bool EnemyCheckHit(WalkEnemy enemy) {
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

	return false;
}

