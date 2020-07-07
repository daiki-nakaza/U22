#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"

#include "PlayerAndIronBall.h"

#define ENEMY_SIZE 48	//敵の大きさ

/**************************************************
*		変数の宣言
***************************************************/
enemyInfo g_Enemy;			//敵の情報を持った変数


/***************************************************
*　　敵の構造体の関数の定義
*****************************************************/
void enemyInfo::WalkInit() {                 // 敵の初期化
	x = 24 * MAP_SIZE;							 // 敵のX座標の初期位置(マップチップの場所)
	y = 14 * MAP_SIZE;								    // 敵のY座標の初期位置(マップチップの場所)
	w = ENEMY_SIZE;						//敵の横幅
	h = ENEMY_SIZE;						//敵の縦

	LoadDivGraph("images/MouseAll.png", 4, 4, 1, ENEMY_SIZE, ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//左向きから始める

	speed = 2;						//敵のスピード
	picDir = true;

	chipY = ((y + MapDrawPointY) / MAP_SIZE) + MapY;
	chipX = ((x - MapDrawPointX) / MAP_SIZE) + MapX;

	DispFlg = TRUE;					//敵を表示


}


void enemyInfo::WalkMove(){

	static int AnmCnt = 0;

	const int FrmMax = 10;		//アニメーションフレームの間



	if (DispFlg) {//
		if (g_MapChip[(y + h) / MAP_SIZE][x / MAP_SIZE] == 1) {			//１つ下のマスを見て空中だったら
			g_Enemy.y += GRAVITY;
		}

		if (EnemyCheckHit(g_Enemy)) {	//壁だったら
			direct *= -1;			//移動の向きを反転させる
		}

		if (direct < 0) picDir = false;		//左向きなら
		else picDir = true;					//右向きなら

		//x = (chipX * MAP_SIZE - MapDrawPointX) + direct * speed;				//移動のスピードを敵キャラに入れる
		x += direct * speed;

		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}

		chipY = ((y + MapDrawPointY) / MAP_SIZE) + MapY;
		chipX = ((x - MapDrawPointX) / MAP_SIZE) + MapX;

	}

}

void enemyInfo::ShootInit() {                 // 撃つ敵の初期化
	x = 24 * MAP_SIZE;							 // 敵のX座標の初期位置(マップチップの場所)
	y = 15 * MAP_SIZE;								    // 敵のY座標の初期位置(マップチップの場所)
	w = ENEMY_SIZE;						//敵の横幅
	h = ENEMY_SIZE;						//敵の縦

	LoadDivGraph("images/MouseAll.png", 4, 4, 1, ENEMY_SIZE, ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//左向きから始める

	speed = 0;						//敵のスピード
	picDir = true;

	chipY = ((y + MapDrawPointY) / MAP_SIZE) + MapY;
	chipX = ((x - MapDrawPointX) / MAP_SIZE) + MapX;

	DispFlg = TRUE;					//敵を表示


}


void enemyInfo::ShootMove() {		//撃つ敵の処理

	static int AnmCnt = 0;

	const int FrmMax = 10;		//アニメーションフレームの間



	if (DispFlg) {
		//if (EnemyCheckHit) {			//１つ下のマスを見て空中だったら
		//	g_Enemy.y += GRAVITY;
		//}

		if (EnemyCheckHit(g_Enemy)) {	//次のフレームの移動先を見て壁だったら
			direct *= -1;			//移動の向きを反転させる
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

void enemyInfo::Disp() {			//敵の表示処理

	if (DispFlg) {		//敵表示
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,	// + MapDrawPointX - MapX * MAP_SIZE
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0xff0000, true);
		//DrawRotaGraphFast2(x, y,0,0,1,0, pic[anm], true,picDir);
	}
	else {				//敵非表示

	}
	/*for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH + 1; x++) {
			DrawFormatString(x * MAP_SIZE + 16, y * MAP_SIZE + 16, 0xf0f0f0, "%d", g_MapChip[y + MapY + MapChipNumY][x + MapX + MapChipNumX]);
		}
	}*/
}
/**************************************************
*　敵の関数の定義
***************************************************/
void enemyDisp() {
	g_Enemy.Disp();
}

void enemyMove() {
	static int Initflg = true;

	if (Initflg) {
		g_Enemy.WalkInit();

		Initflg = false;
	}
	if (g_Enemy.DispFlg) {
		g_Enemy.WalkMove();
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
	//if (IronToEnemy()) return true;

	return false;
}