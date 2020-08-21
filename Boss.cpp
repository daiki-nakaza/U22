#include "DxLib.h"

#include "Boss.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Define.h"
#include "Map.h"
#include "IronToEnemy.h"

#include <time.h>


/******************************************
*****************ボス**********************
*******************************************/
Boss g_Boss;			//ボスの構造体変数

int SetTP;


void Boss::BossInit(int Tempx, int Tempy) {
	int SetX = Tempx * (MAP_SIZE)/* + (((Tempy / HEIGHT) * WIDTH) * WIDTH)*/, SetY = (Tempy % HEIGHT) * MAP_SIZE;


	x = SetX;							 // 敵のX座標の初期位置(マップチップの場所)
	y = SetY - (BOSS_H - MAP_SIZE);								    // 敵のY座標の初期位置(マップチップの場所)

	TPSpace[0][TP_MAX - 1] = SetX;								// 敵のTP先のX座標の初期位置(マップチップの場所)
	TPSpace[1][TP_MAX - 1] = SetY - (BOSS_H - MAP_SIZE);		// 敵のTP先のY座標の初期位置(マップチップの場所)

	w = BOSS_W;						//敵の横幅
	h = BOSS_H;						//敵の縦

	pic = LoadGraph("images/rasubosu.png");

	anm = 0;

	direct = -1;						//左向きから始める
	picDir = true;

	speed = 2;						//敵のスピード

	Life = 3;					//敵のHP　とりま３

	type = 0;					//敵のタイプ

	outtime = 0;				//１度攻撃をもらったら無敵


	DispFlg = TRUE;					//敵を表示
}

void Boss::TPInit(int Tempx, int Tempy) {
	int SetX = Tempx * MAP_SIZE + (((Tempy / HEIGHT) * WIDTH) * WIDTH), SetY = (Tempy % HEIGHT) * MAP_SIZE;

	TPSpace[0][SetTP] = SetX;								// 敵のTP先のX座標の初期位置(マップチップの場所)
	TPSpace[1][SetTP] = SetY - (BOSS_H - MAP_SIZE) + 3;		// 敵のTP先のY座標の初期位置(マップチップの場所)

	if (SetTP++ >= TP_MAX - 2) SetTP = TP_MAX - 2;

}


//****************ボスの動き*******************//

void Boss::BossMove() {
	Move();
}



//****************ボスの表示*******************//
void Boss::Disp() {
	if (DispFlg && CheckWindow()) {		//敵表示
		if (outtime == 0) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2,
				1, 0, pic, true, picDir);
		}
		else if (outtime % 2 == 1) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2,
				1, 0, pic, true, picDir);
		}
	}
	else {				//敵非表示

	}
}
