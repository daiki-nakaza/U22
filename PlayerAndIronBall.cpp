#include "DxLib.h"

#include "Define.h"
#include "PlayerAndIronBall.h"

#include "Player.h"
#include "accessory.h"

/**************************************
*	関数の定義
***************************************/
void IronInit(int *ironX, int *ironY, int px,int py) {

	*ironX = ( (px / MAP_SIZE) + 4 ) * MAP_SIZE ;
}

void IronHold(int* ironX, int* ironY, int px, int py) {
	*ironX = px;
	*ironY = py;
}

void IronHoldOrThrow() {

	//プレイヤーが鉄球を持つか投げる処理
	if (!g_IronBall.HoldFlg && !g_IronBall.ThrowFlg		//鉄球を持っていないかつ鉄球が投げられていない
		&& g_NowKey & PAD_INPUT_1) {
		g_IronBall.HoldFlg = true;
	}
	else if (g_IronBall.HoldFlg && !g_IronBall.ThrowFlg	//鉄球を持っていてかつ鉄球が投げられていない
		&& g_NowKey & PAD_INPUT_2) {
		g_IronBall.HoldFlg = false;
		g_IronBall.ThrowFlg = true;
	}
}