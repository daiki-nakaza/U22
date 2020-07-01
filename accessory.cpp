#include "DxLib.h"

#include "accessory.h"

#include "PlayerAndIronBall.h"
#include "Map.h"

/**************************************************
*		変数の宣言
***************************************************/
partsInfo g_IronBall;			//敵の情報を持った変数

/*****************************************************
*		関数の定義
********************************************************/
void partsInfo::Init() {                 // 鉄球の初期化
	IronInit(&x, &y);		//座標をプレイヤーの隣に代入
	r = IRONBALL_R;

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, ENEMY_SIZE, ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//左向きから始める

	speed = 2;						//鉄球のスピード
	picDir = true;

	DispFlg = TRUE;					//鉄球を表示


}

void partsInfo::Disp() {


	if (DispFlg) {		//鉄球表示
		//DrawBox(x,y, x + w, y + h, 0x000000, true);
		//DrawRotaGraphFast2(x, y, 0, 0, 1, 0, pic, true, picDir);
		DrawCircle(x, y, r, 0x000000, true);
		//DrawFormatString(30, 30, 0x000000, "X = %d\nY = %d\nR = %d", x, y,r);
	}
	else {				//鉄球非表示

	}
}

void partsInfo::Move() {
	if (g_MapChip[( (y - (MAP_SIZE - IRONBALL_R)  ) / MAP_SIZE + MapY) + 1][(x / MAP_SIZE + MapX)] == 1) {			//１つ下のマスを見て空中だったら
		y += GRAVITY;
	}
	//x = ((PlayerX / MAP_SIZE) + 4) * MAP_SIZE;
	if (HoldFlg) {
		
	}


}


/***********************************************
*		鉄球の関数の定義
************************************************/
void IronBallDisp() {
	g_IronBall.Disp();
}



void IronBallMove() {
	static bool initflg = true;

	if (initflg) {
		g_IronBall.Init();
		initflg = false;
	}

	g_IronBall.Move();
}