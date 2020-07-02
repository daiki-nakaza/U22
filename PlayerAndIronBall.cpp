#include "DxLib.h"

#include "Define.h"
#include "PlayerAndIronBall.h"

#include "Player.h"
#include "accessory.h"

/**************************************
*	�֐��̒�`
***************************************/
void IronInit(int *ironX, int *ironY, int px,int py) {

	*ironX = ( (px / MAP_SIZE) + 4 ) * MAP_SIZE ;
}

void IronHold(int* ironX, int* ironY, int px, int py) {
	*ironX = px;
	*ironY = py;
}

void IronHoldOrThrow() {

	//�v���C���[���S�������������鏈��
	if (!g_IronBall.HoldFlg && !g_IronBall.ThrowFlg		//�S���������Ă��Ȃ����S�����������Ă��Ȃ�
		&& g_NowKey & PAD_INPUT_1) {
		g_IronBall.HoldFlg = true;
	}
	else if (g_IronBall.HoldFlg && !g_IronBall.ThrowFlg	//�S���������Ă��Ă��S�����������Ă��Ȃ�
		&& g_NowKey & PAD_INPUT_2) {
		g_IronBall.HoldFlg = false;
		g_IronBall.ThrowFlg = true;
	}
}