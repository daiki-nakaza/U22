#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"
#include "accessory.h"
#include "Boss.h"

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

// ↓敵の効果音等↓ //
int g_ColorL;
int g_Hadou;  // 波動砲のSE格納変数
int g_Kakusan;// 拡散弾のSE格納変数
int g_Shot;   // 通常弾のSE格納変数(ボスと雑魚敵)
int g_Warp;   // ボスのワープSE格納変数


/***************************************************
*　　敵の構造体の関数の定義
*****************************************************/

void enemyInfo::Move() {
	/******************************************************
		*勝手に書きました
		******************************************************/
	if (CheckHitPlayer() && Attack > 0 && outtime == 0) {		//プレイヤーが攻撃していたら
		outtime = 60;
		if (Life-- <= 0)DispFlg = false;
	}
	else {		//プレイヤーの体力を減らす

	}
	if (outtime > 0) {
		if (outtime-- < 0) outtime = 0;
	}
	if (Life <= 0) {
		DispFlg = false;
	}
}

void enemyInfo::Disp() {			//敵の表示処理
	if (DispFlg && CheckWindow()) {		//敵表示
		if (outtime == 0) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic, true, picDir);
		}
		else if (outtime % 2 == 1) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic, true, picDir);
		}
	}
	else {				//敵非表示

	}
}

bool enemyInfo::CheckHitBall() {
	if (y - MapDrawPointY - MapY * MAP_SIZE < (g_IronBall.y + MapDrawPointY - MapY * MAP_SIZE) + g_IronBall.r
		&& y + h - MapDrawPointY - MapY * MAP_SIZE >(g_IronBall.y + MapDrawPointY - MapY * MAP_SIZE) - g_IronBall.r) {
		if ((x + MapDrawPointX - MapX * MAP_SIZE) < ((g_IronBall.x + MapDrawPointX - MapX * MAP_SIZE) + g_IronBall.r)
			&& (x + w + MapDrawPointX - MapX * MAP_SIZE) > ((g_IronBall.x + MapDrawPointX - MapX * MAP_SIZE) - g_IronBall.r)) {
			return true;
		}
	}
	return false;
}


bool enemyInfo::CheckHitPlayer() {

	if (y - MapDrawPointY - MapY * MAP_SIZE < PlayerY + CHA_SIZE_Y
		&& y + h - MapDrawPointY - MapY * MAP_SIZE > PlayerY) {
		if (x + MapDrawPointX - MapX * MAP_SIZE < (PlayerX + CHA_SIZE_X)
			&& x + w + MapDrawPointX - MapX * MAP_SIZE >(PlayerX)) {
			return true;
		}
	}
	return false;
}
//////////////////////////////////////////////
/////////////歩く敵の処理////////////////////
/////////////////////////////////////////////

void WalkEnemy::Init(int Tempx, int Tempy) {                 // 敵の初期化
	int SetX = Tempx * MAP_SIZE + ( ( (Tempy / HEIGHT) * WIDTH) * WIDTH) , SetY = (Tempy % HEIGHT) * MAP_SIZE;


	x = SetX;							 // 敵のX座標の初期位置(マップチップの場所)
	y = SetY - (WALK_ENEMY_SIZE - MAP_SIZE) + 3;								    // 敵のY座標の初期位置(マップチップの場所)

	w = WALK_ENEMY_SIZE;						//敵の横幅
	h = WALK_ENEMY_SIZE;						//敵の縦

	LoadDivGraph("images/ZakoWalk.png", 4, 4, 1, WALK_ENEMY_SIZE, WALK_ENEMY_SIZE, pic);
	//pic = LoadGraph("images/Zako.png");

	anm = 0;

	direct = -1;						//左向きから始める
	picDir = true;


	speed = 2;						//敵のスピード

	Life = 3;					//敵のHP　とりま３

	type = 0;					//敵のタイプ

	outtime = 0;				//１度攻撃をもらったら無敵


	DispFlg = TRUE;					//敵を表示


}


void WalkEnemy::WalkMove(){
	NewDir = direct;
	NewX = x;

	const int FrmMax = 20;		//アニメーションフレームの間

	int Enemy_MapX, Enemy_MapY;		//マップチップ上の座標を作る

	Enemy_MapX = (x % (WIDTH * MAP_SIZE) ) / MAP_SIZE;
	Enemy_MapY = ( ( (y + h) / MAP_SIZE) + (x / (WIDTH * MAP_SIZE) ) * HEIGHT);

	if (DispFlg && CheckWindow()) {//
		if (g_MapChip[Enemy_MapY][Enemy_MapX] == 1) y += GRAVITY;

		if (direct < 0) picDir = true;		//左向きなら
		else picDir = false;					//右向きなら

		x += direct * speed;

		if (EnemyCheckHit(x, y, direct)) {
			if (x % 32 <= 16) {
				direct *= -1;
				x -= x % 32;
			}
			else {
				direct *= -1;
				x += x % 32;
			}
		}
		Move();			//敵共通の関数	


		if (CheckHitPlayer() 
			&& outtime == 0
			&& Playerouttime == 0) {		//どっちも無傷の状態で雑魚的とぶつかったら
			direct *= -1; 
			PlayerDamage();
		}


		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}

		if (CheckHitBall()) {
			direct *= -1;
			if ((x + MapDrawPointX - MapX * MAP_SIZE) - (g_IronBall.x + MapDrawPointX - MapX * MAP_SIZE) < 0) {
				x -= x % 32;
			}
			else {
				x += x % 32;
			}
		}
	}

}

void WalkEnemy::Disp() { 
	if (DispFlg && CheckWindow()) {		//敵表示
		if (outtime == 0) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic[anm], true, picDir);
		}
		else if (outtime % 2 ==  1) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic[anm], true, picDir);
		}
	}
	else {				//敵非表示

	}
}

////////////////////////////////////////////
//////////撃つ敵の処理//////////////////////
/////////////////////////////////////////////

void ShootEnemy::Init(int Tempx, int Tempy) {                 // 撃つ敵の初期化
	int SetX = Tempx * MAP_SIZE + (((Tempy / HEIGHT) * WIDTH) * WIDTH), SetY = (Tempy % HEIGHT) * MAP_SIZE;


	x = SetX ;							 // 敵のX座標の初期位置(マップチップの場所)
	y = SetY - (SHOOT_ENEMY_SIZE - MAP_SIZE);								    // 敵のY座標の初期位置(マップチップの場所)

	w = SHOOT_ENEMY_SIZE;						//敵の横幅
	h = SHOOT_ENEMY_SIZE;						//敵の縦

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, SHOOT_ENEMY_SIZE, SHOOT_ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//左向きから始める

	Firecnt = 0;		 //発射のカウント
	BulletCnt = 0;		//３発連続で弾を発射させる
	ReloadCnt = 0;		//リロードの時間カウント

	speed = 0;						//敵のスピード
	picDir = true;

	Life = 3;					//敵のHP　とりま３

	type = 1;					//敵のタイプ

	pic = LoadGraph("images/Enemy Soldier.png");

	DispFlg = TRUE;					//敵を表示


}


void ShootEnemy::ShootMove() {		//撃つ敵の処理

	const int FrmMax = 10;		//アニメーションフレームの間

	const int Rate = 20;		//発射レート
	const int ReloadTime = 180;			//リロード時間　大体３秒




	if (DispFlg && CheckWindow()) {//

		if (direct < 0) picDir = false;		//左向きなら
		else picDir = true;					//右向きなら


		if (Firecnt++ >= Rate
			&& BulletCnt < Bullet_MAX
			&& !Bullet[BulletCnt].DispFlg) {
			Bullet[BulletCnt].Init(x, y + h / 2);			//弾を飛ばす間隔
			BulletCnt++;
			Firecnt = 0;
			if (BulletCnt >= Bullet_MAX - 1) ReloadCnt = 0;
		}

		if (!Bullet[0].DispFlg
			&& !Bullet[1].DispFlg
			&& !Bullet[2].DispFlg
			&& ReloadCnt++ > ReloadTime) {
			BulletCnt = 0;		//弾の表示フラグがすべてoffなら撃てるようになる

		}

		for (int i = 0; i < Bullet_MAX; i++) {
			Bullet[i].Disp();
			Bullet[i].Move(direct);			//弾丸の処理

		}

		Move();			//敵共通の関数

	}


}


////////////////////////////////////////////
//////////狙い撃つ敵の処理//////////////////////
/////////////////////////////////////////////

//狙い撃つ敵の初期化
void LockShootEnemy::Init(int Tempx, int Tempy) {
	int SetX = Tempx * MAP_SIZE + (((Tempy / HEIGHT) * WIDTH) * WIDTH), SetY = (Tempy % HEIGHT) * MAP_SIZE;


	x = SetX;										// 敵のX座標の初期位置(マップチップの場所)
	y = SetY - (SHOOT_ENEMY_SIZE - MAP_SIZE);		// 敵のY座標の初期位置(マップチップの場所)

	w = SHOOT_ENEMY_SIZE;						//敵の横幅
	h = SHOOT_ENEMY_SIZE;						//敵の縦

	anm = 0;

	Firecnt = 0;		 //発射のカウント
	BulletCnt = 0;		//３発連続で弾を発射させる
	ReloadCnt = 0;		//リロードの時間カウント

	direct = -1;						//左向きから始める

	speed = 0;						//敵のスピード
	picDir = true;

	Life = 3;					//敵のHP　とりま３

	type = 1;					//敵のタイプ

	pic = LoadGraph("images/Variant Enemy Soldier.png");

	DispFlg = TRUE;					//敵を表示



}


void LockShootEnemy::LockShootMove() {			//撃つ敵の処理

	const int FrmMax = 10;		//アニメーションフレームの間

	const int Rate = 20;		//発射レート
	const int ReloadTime = 180;			//リロード時間　大体３秒


	if (DispFlg && CheckWindow()) {//

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
			if (BulletCnt >= Bullet_MAX - 1) ReloadCnt = 0;
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
			if (DebugMode) DrawFormatString(100, 140 + i * 30, 0x000000, "%f", Bullet[i].SpeedY);
		}

		Move();			//敵共通の関数

	}

}

//戦車の敵(上に向かって弾を飛ばす奴)
void TankEnemy::Init(int Tempx, int Tempy) {
	int SetX = Tempx * MAP_SIZE + (((Tempy / HEIGHT) * WIDTH) * WIDTH), SetY = (Tempy % HEIGHT) * MAP_SIZE;


	x = SetX;										// 敵のX座標の初期位置(マップチップの場所)
	y = SetY - (TANK_ENEMY_SIZE - MAP_SIZE);		// 敵のY座標の初期位置(マップチップの場所)

	w = TANK_ENEMY_SIZE;						//敵の横幅
	h = TANK_ENEMY_SIZE;						//敵の縦幅

	anm = 0;

	Firecnt = 0;		 //発射のカウント
	BulletCnt = 0;		//３発連続で弾を発射させる
	ReloadCnt = 0;		//リロードの時間カウント

	direct = -1;						//左向きから始める

	speed = 0;						//敵のスピード
	picDir = true;

	Life = 3;					//敵のHP　とりま３

	type = 1;					//敵のタイプ

	LoadDivGraph("images/TankEnemy.png", 2, 2, 1, TANK_ENEMY_SIZE, TANK_ENEMY_SIZE, pic);

	DispFlg = TRUE;					//敵を表示


}

void TankEnemy::TankMove() {


	const int FrmMax = 20;		//アニメーションフレームの間

	const int Rate = 40;		//発射レート
	const int ReloadTime = 240;			//リロード時間　



	if (DispFlg && CheckWindow()) {//

		//if(DirCheck)

		if (direct < 0) picDir = false;		//左向きなら
		else picDir = true;					//右向きなら



		if (++AnmCnt >= FrmMax) {				//アニメーションフレーム
			if (++anm > 1) anm = 0;
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

		}

		Move();			//敵共通の関数

	}
}


void TankEnemy::Disp() {
	if (DispFlg && CheckWindow()) {		//敵表示
		if (outtime == 0) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic[anm], true, picDir);
		}
		else if (outtime % 2 ==  1) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic[anm], true, picDir);
		}
	}
	else {				//敵非表示

	}
}

//波動砲を撃つ敵の関数定義
void RazerEnemy::Init(int Tempx, int Tempy){
	int SetX = Tempx * MAP_SIZE + (((Tempy / HEIGHT) * WIDTH) * WIDTH), SetY = (Tempy % HEIGHT) * MAP_SIZE;

	x = SetX;										// 敵のX座標の初期位置(マップチップの場所)
	y = SetY - (RAZER_ENEMY_SIZE - MAP_SIZE);		// 敵のY座標の初期位置(マップチップの場所)

	w = RAZER_ENEMY_SIZE;						//敵の横幅
	h = RAZER_ENEMY_SIZE;						//敵の縦幅

	anm = 0;

	direct = -1;						//左向きから始める

	speed = 0;						//敵のスピード
	picDir = true;

	Life = 3;					//敵のHP　とりま３

	type = 1;					//敵のタイプ

	LoadDivGraph("images/HadouhouAll.png",3,3,1, TANK_ENEMY_SIZE, TANK_ENEMY_SIZE,pic);

	//pic[2] = LoadGraph("images/Hadouhou2.png");

	DispFlg = TRUE;					//敵を表示

}

void RazerEnemy::ShotMove() {

	static int AnmCnt = 0;

	const int FrmMax = 10;		//アニメーションフレームの間

	const int ReloadTime = 300;


	if (DispFlg && CheckWindow()) {//
		if (!Bullet.DispFlg && Reload <= 0) {
			Bullet.Init(x, y + h / 2);
			Reload = ReloadTime;
		}

		Bullet.Move(direct);
		Bullet.Disp();

		if (Reload >= 0 && !Bullet.DispFlg) Reload--;

		if (Reload == ReloadTime || Reload < 30) anm = 2;
		else if(Reload < 60)anm = 1;
		else anm = 0;

		Move();			//敵共通の関数

	}
}

void RazerEnemy::Disp() {
	if (DispFlg && CheckWindow()) {		//敵表示
		if (outtime == 0) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic[anm], true, picDir);
		}
		else if (outtime % 2 == 1) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic[anm], true, picDir);
		}
	}
	else {				//敵非表示

	}
}
/**************************************************
*　敵の関数の定義
***************************************************/

void enemyInit() {			//敵の初期化処理
	SetTP = 0;
	 
	for (int y = 0; y < HEIGHT * MAP_LONG; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (g_MapChip[y][x] == 3) {		//歩く雑魚
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (g_WalkEnemy[i].DispFlg == false) {
						g_WalkEnemy[i].Init(x, y);
						g_MapChip[y][x] = 1;
						break;
					}
				}
			}
			else if (g_MapChip[y][x] == 4) {		//真っすぐ撃つ
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (!g_ShootEnemy[i].DispFlg) {
						g_ShootEnemy[i].Init(x, y);
						g_MapChip[y][x] = 1;
						break;
					}
				}
			}
			else if (g_MapChip[y][x] == 5) {		//頭狙うやつ
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (!g_LockShootEnemy[i].DispFlg) {
						g_LockShootEnemy[i].Init(x, y);
						g_MapChip[y][x] = 1;
						break;
					}
				}
			}
			else if (g_MapChip[y][x] == 6) {		//戦車
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (!g_TankEnemy[i].DispFlg) {
						g_TankEnemy[i].Init(x, y);
						g_MapChip[y][x] = 1;
						break;
					}
				}
			}
			else if (g_MapChip[y][x] == 7) {
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (!g_RazerEnemy[i].DispFlg) {
						g_RazerEnemy[i].Init(x, y);
						g_MapChip[y][x] = 1;
						break;
					}
				}
			}
			else if (g_MapChip[y][x] == 8) {			//ボス
				g_Boss.BossInit(x, y);
				break;
			}
			else if (g_MapChip[y][x] == 9) {			//ボスのテレポート先
				g_Boss.TPInit(x, y);
				break;
			}
		}
	}
	

}

void enemyDisp() {

	if (g_Boss.CheckWindow()) {
		g_Boss.Disp();
	} else {
		for (int i = 0; i < ENEMY_MAX; i++) {
			g_WalkEnemy[i].Disp();
			g_ShootEnemy[i].Disp();
			g_LockShootEnemy[i].Disp();
			g_TankEnemy[i].Disp();
			g_RazerEnemy[i].Disp();
		}
	}
	
}




void enemyMove() {
	static bool Initflg = true;
	if (Initflg) {
		enemyInit();
		Initflg = false;
	}
	if (g_Boss.CheckWindow()) {
		g_Boss.BossMove();
	}
	else {
		for (int i = 0; i < ENEMY_MAX; i++) {

			g_WalkEnemy[i].WalkMove();
			g_ShootEnemy[i].ShootMove();
			g_LockShootEnemy[i].LockShootMove();
			g_TankEnemy[i].TankMove();
			g_RazerEnemy[i].ShotMove();
		}
	}

	if (DebugMode) {
	//	DrawFormatString(100, 300, 0xff0000, "%d %d", g_Boss.x, g_Boss.y);
	}
}

bool EnemyCheckHit(int x, int y, int direct) {
	int i = 0, j = 0, k = 0, l = 0, w = 0, z = 0;		//補正値用変数
	//的の位置（左）がマップをまたいでいる
	while (x / MAP_SIZE - k >= WIDTH) {
		k += WIDTH;
		l += HEIGHT;
	}

	//敵の位置(右)がマップをまたいでいる
	if ((x + WALK_ENEMY_SIZE) / MAP_SIZE - k >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//真ん中の位置がマップをまたいでいる
	if ((x + WALK_ENEMY_SIZE / 2) / MAP_SIZE - k >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}


	if (direct == 1)			//右向きの処理
	{
		if (g_MapChip[(y) / MAP_SIZE + l + j][(x + WALK_ENEMY_SIZE) / MAP_SIZE - k - w] != 1	//右上
			|| g_MapChip[(y +(WALK_ENEMY_SIZE /2) ) / MAP_SIZE + l + j][(x + WALK_ENEMY_SIZE) / MAP_SIZE - k - w] != 1){	//右下
			return true;
		}
	}
	else {
		if (g_MapChip[(y) / MAP_SIZE + l][(x) / MAP_SIZE - k] != 1				//左上
			|| g_MapChip[(y +(WALK_ENEMY_SIZE / 2) ) / MAP_SIZE + l][(x) / MAP_SIZE - k] != 1){	//左下
 		return true;
		}

	}

	return false;
}

bool enemyInfo::CheckWindow() {

	if ((x + MapDrawPointX - MapX * MAP_SIZE > -WIDTH / 8 * MAP_SIZE)
		&& (x + MapDrawPointX - MapX * MAP_SIZE < WIDTH * MAP_SIZE + (WIDTH / 8 * MAP_SIZE))) {
		return true;
	}

	return false;
}