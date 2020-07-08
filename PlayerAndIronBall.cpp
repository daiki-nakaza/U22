#include "DxLib.h"

#include "Define.h"
#include "PlayerAndIronBall.h"

#include "Player.h"
#include "accessory.h"
#include "Enemy.h"
#include "Map.h"

/**************************************
*	�֐��̒�`
***************************************/
void IronInit(int *ironX, int *ironY, int px,int py) {

	*ironX = ( (px / MAP_SIZE) + 4 ) * MAP_SIZE ;
}

void IronHold(int* ironX, int* ironY, int px, int py, int mpx,int mpy) {
	*ironX = px + mpx;
	*ironY = py + mpy;
}

void IronHoldOrThrow() {

	//�v���C���[���S�������������鏈��
	if (!g_IronBall.HoldFlg && !g_IronBall.ThrowFlg		//�S���������Ă��Ȃ����S�����������Ă��Ȃ�
		&& g_NowKey & PAD_INPUT_1 && Jump_Flg == 0) {
		g_IronBall.HoldFlg = true;
	}
	else if (g_IronBall.HoldFlg && !g_IronBall.ThrowFlg	//�S���������Ă��Ă��S�����������Ă��Ȃ�
		&& g_NowKey & PAD_INPUT_2) {
		g_IronBall.HoldFlg = false;
		g_IronBall.ThrowFlg = true;
	}
	if (true) {

	}
}


bool IronToEnemy() {

	if (g_Enemy.picDir) {			//�E�����̏���
		//���̈ړ��̏ꏊ���S���Ɣ���Ă�����true��Ԃ�
		if ((g_Enemy.y + g_Enemy.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
			&& (((g_Enemy.x + g_Enemy.w - MapDrawPointX) + (g_Enemy.direct * g_Enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x - g_IronBall.r) / MAP_SIZE + MapX) return true;
	}
	else {							//�������̏���
		//���̈ړ��̏ꏊ���S���Ɣ���Ă�����true��Ԃ�
		if ((g_Enemy.y + g_Enemy.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
			&& (((g_Enemy.x - MapDrawPointX) + (g_Enemy.direct * g_Enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x + g_IronBall.r) / MAP_SIZE + MapX) return true;
	}
	


		return false;
}