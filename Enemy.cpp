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
	y = 15 * MAP_SIZE;								    // 敵のY座標の初期位置(マップチップの場所)
	w = ENEMY_SIZE;						//敵の横幅
	h = ENEMY_SIZE;						//敵の縦

	LoadDivGraph("images/MouseAll.png", 4, 4, 1, ENEMY_SIZE, ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//左向きから始める

	speed = 1;						//敵のスピード
	picDir = true;

	chipY = ((y + MapDrawPointY) / MAP_SIZE) + MapY;
	chipX = ((x - MapDrawPointX) / MAP_SIZE) + MapX;

	DispFlg = TRUE;					//敵を表示


}

void enemyInfo::Disp() {

	if (DispFlg) {		//敵表示
		DrawBox(x,y, x + w, y + h, 0xff0000, true);
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

void enemyInfo::WalkMove(){

	static int AnmCnt = 0;

	const int FrmMax = 10;		//アニメーションフレームの間



	if (DispFlg) {
		if (g_MapChip[((y + h/2) / MAP_SIZE + MapY) + 1][(x / MAP_SIZE + MapX)] == 1) {			//１つ下のマスを見て空中だったら
			g_Enemy.y += GRAVITY;
		}

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

		chipY = ((y + MapDrawPointY) / MAP_SIZE) + MapY;
		chipX = ((x - MapDrawPointX) / MAP_SIZE) + MapX;

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
	if (enemy.picDir)			//右向きの処理
	{
		//次の移動の場所が敵キャラの右端に壁が重なったらtrueを返す
		if 
			(g_MapChip[(enemy.y + enemy.h + MapDrawPointY) / MAP_SIZE + MapY]
			[(((enemy.x + enemy.w - MapDrawPointX)+(enemy.direct * enemy.speed)) / MAP_SIZE) + MapX] == 0) return true;

	}
	else {							//左向きの処理
		//次の移動の場所が敵キャラの左端に壁が重なったらスピードを反転する
		if
			(g_MapChip[(enemy.y + enemy.h + MapDrawPointY) / MAP_SIZE + MapY]
			[((enemy.x - MapDrawPointX + (enemy.direct * enemy.speed)) / MAP_SIZE) + MapX] == 0) return true;
	}

	if (IronToEnemy()) return true;

	return false;
}