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
		DrawFormatString(30, 30, 0x000000, "Y = %d\nX = %d\n", (y + IRONBALL_R) / MAP_SIZE + MapY,(x / MAP_SIZE + MapX));
	}
	else {				//鉄球非表示

	}
}

void partsInfo::Move() {
	if (!HitCheck() && !ThrowFlg) y += 4;
	
	//x = ((PlayerX / MAP_SIZE) + 4) * MAP_SIZE;
	if (HoldFlg) {
		
	}
	Throw();


}

void partsInfo::Throw(){			//鉄球が飛んでいく処理
	const int InitPow = -16;
	static int Pow = InitPow;
	static int move = 1;

	//if (g_NowKey & PAD_INPUT_UP) ThrowFlg = true;

	if (HoldFlg) {
		IronHold(&x,&y);
	}

	if (ThrowFlg) {			//投げられている処理
		if (Pow++ < abs(InitPow)) {
			x += 8;
			y += Pow;
			if (HitCheck()) {
				ThrowFlg = false;
				x -= 8;
				y -= Pow;
			}
		}
		else { ThrowFlg = false; }
	}
	else { Pow = InitPow; }
}

bool partsInfo::HitCheck() {		//地面との当たり判定　当たっていればtrue 当たっていなければfalse
	//if (g_MapChip[((y + (MAP_SIZE - IRONBALL_R)) / MAP_SIZE + MapY) + 1][(x / MAP_SIZE + MapX)] != 1		////１つ下のマスを見て地面だったら
	//	&& g_MapChip[((y + (MAP_SIZE - IRONBALL_R)) / MAP_SIZE + MapY) + 1][((x - IRONBALL_R) / MAP_SIZE + MapX)] != 1
	//	&& g_MapChip[((y + (MAP_SIZE - IRONBALL_R)) / MAP_SIZE + MapY) + 1][((x + IRONBALL_R) / MAP_SIZE + MapX)] != 1
	//	
	//	&& g_MapChip[((y + (MAP_SIZE - IRONBALL_R)) / MAP_SIZE + MapY) + 1][(x / MAP_SIZE + MapX)] != 1) {
	if(g_MapChip[(y + IRONBALL_R  ) / MAP_SIZE + MapY][(x / MAP_SIZE + MapX)] != 1){
		return true;
	}

	return false;
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