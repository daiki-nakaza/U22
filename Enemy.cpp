#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"

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
	y = 15 * MAP_SIZE;								    // 敵のY座標の初期位置(マップチップの場所)
	w = ENEMY_SIZE;						//敵の横幅
	h = ENEMY_SIZE;						//敵の縦

	LoadDivGraph("images/MouseAll.png", 4, 4, 1, ENEMY_SIZE, ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//左向きから始める

	speed = 2;						//敵のスピード
	picDir = true;

	DispFlg = TRUE;					//敵を表示


}

void enemyInfo::Disp() {

	if (DispFlg) {		//敵表示
		//DrawBox(x,y, x + w, y + h, 0x000000, true);
		DrawRotaGraphFast2(x, y,0,0,1,0, pic[anm], true,picDir);
	}
	else {				//敵非表示

	}
}

void enemyInfo::WalkMove(){

	static int AnmCnt = 0;

	const int FrmMax = 10;		//アニメーションフレームの間



	if (DispFlg) {
		if (g_MapChip[(y / MAP_SIZE + MapY) + 1][(x / MAP_SIZE + MapX)] == 1) {			//１つ下のマスを見て空中だったら
			g_Enemy.y += GRAVITY;
		}

		if (EnemyCheckHit(g_Enemy)) {	//次のフレームの移動先を見て壁だったら
			direct *= -1;			//移動の向きを反転させる
		}

		if (direct < 0) picDir = false;
		else picDir = true;

		x += direct * speed;				//移動のスピードを敵キャラに入れる

		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}

	}

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
	if (enemy.direct == 1)			//右向きの処理
	{
		//次の移動の場所が敵キャラの右端に壁が重なったらスピードを反転する
		if 
			(g_MapChip[(enemy.y + MapDrawPointY) / MAP_SIZE + MapY]
			[(((enemy.x + enemy.w - MapDrawPointX)+(enemy.direct * enemy.speed)) / MAP_SIZE) + MapX] == 0) return true;
	}
	else {							//左向きの処理
		//次の移動の場所が敵キャラの左端に壁が重なったらスピードを反転する
		if
			(g_MapChip[(enemy.y + MapDrawPointY) / MAP_SIZE + MapY]
			[((enemy.x - MapDrawPointX + (enemy.direct * enemy.speed)) / MAP_SIZE) + MapX] == 0) return true;
	}
	return false;
}