#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"

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
	w = MAP_SIZE;						//敵の横幅
	h = MAP_SIZE;						//敵の縦幅

	direct = -1;						//左向きから始める

	speed = 4;						//敵のスピード

	DispFlg = TRUE;					//敵を表示
}

void enemyInfo::Disp() {
	int DispX, DispY;

	DispX = x - MapDrawPointX;
	DispY = y + MapDrawPointY;

	if (DispFlg) {		//敵表示
		DrawBox(x,y, x + w, y + h, 0x000000, true);
	}
	else {				//敵非表示

	}
}

void enemyInfo::WalkMove(){

	if (DispFlg) {
		if (EnemyCheckHit(g_Enemy)) {	//次のフレームの移動先を見て壁だったら
			direct *= -1;			//移動の向きを反転させる
		}

		if (g_MapChip[(y / MAP_SIZE + MapY) + 1][(x / MAP_SIZE + MapX)]) {			//１つ下のマスを見て空中だったら
			g_Enemy.y += 4;
		}

		x += direct * speed;				//移動のスピードを敵キャラに入れる

	}

}

/**************************************************
*　敵の関数の定義
***************************************************/
void enemyDisp() {
	g_Enemy.Disp();
	DrawFormatString(200, 100, 0x000000, "%d",g_Enemy.x / MAP_SIZE + MapX);
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
		//if (g_MapChip[enemy.y / MAP_SIZE + MapY][(enemy.x / MAP_SIZE) + enemy.direct + MapX] == 0) return TRUE;
		if (g_MapChip[(enemy.y + MapDrawPointY) / MAP_SIZE + MapY][((enemy.x - MapDrawPointX) / MAP_SIZE) + enemy.direct + MapX] == 0) return TRUE;
	}else{							//左向きの処理
		if (g_MapChip[(enemy.y + MapDrawPointY) / MAP_SIZE + MapY][( (enemy.x - MapDrawPointX + (enemy.direct * enemy.speed)) / MAP_SIZE) + MapX] == 0) return TRUE;
	
	/*if (g_MapChip[MapY + ((enemy.y + MapDrawPointY) / MAP_SIZE) + MapChipNumY][MapX + ((enemy.x +MapDrawPointX) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((enemy.y + MapDrawPointY + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY][MapX + ((enemy.x + MapDrawPointX) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((enemy.y + MapDrawPointY) / MAP_SIZE) + MapChipNumY][MapX + ((enemy.x + MapDrawPointX + CHA_SIZE - 1) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((enemy.y + MapDrawPointY + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY][MapX + ((enemy.x + MapDrawPointX + CHA_SIZE - 1) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((enemy.y + MapDrawPointY) / MAP_SIZE) + MapChipNumY][MapX + ((enemy.x + MapDrawPointX + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX ] != 1
		|| g_MapChip[MapY + ((enemy.y + MapDrawPointY + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY][MapX + ((enemy.x + MapDrawPointX + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX] != 1
		)
	{*/
		return false;
	}
	return false;
}