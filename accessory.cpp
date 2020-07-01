#include "DxLib.h"

#include "accessory.h"

#include "PlayerAndIronBall.h"
#include "Map.h"

/**************************************************
*		�ϐ��̐錾
***************************************************/
partsInfo g_IronBall;			//�G�̏����������ϐ�

/*****************************************************
*		�֐��̒�`
********************************************************/
void partsInfo::Init() {                 // �S���̏�����
	IronInit(&x, &y);		//���W���v���C���[�ׂ̗ɑ��
	r = IRONBALL_R;

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, ENEMY_SIZE, ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//����������n�߂�

	speed = 2;						//�S���̃X�s�[�h
	picDir = true;

	DispFlg = TRUE;					//�S����\��


}

void partsInfo::Disp() {


	if (DispFlg) {		//�S���\��
		//DrawBox(x,y, x + w, y + h, 0x000000, true);
		//DrawRotaGraphFast2(x, y, 0, 0, 1, 0, pic, true, picDir);
		DrawCircle(x, y, r, 0x000000, true);
		//DrawFormatString(30, 30, 0x000000, "X = %d\nY = %d\nR = %d", x, y,r);
	}
	else {				//�S����\��

	}
}

void partsInfo::Move() {
	if (g_MapChip[( (y - (MAP_SIZE - IRONBALL_R)  ) / MAP_SIZE + MapY) + 1][(x / MAP_SIZE + MapX)] == 1) {			//�P���̃}�X�����ċ󒆂�������
		y += GRAVITY;
	}
	//x = ((PlayerX / MAP_SIZE) + 4) * MAP_SIZE;
	if (HoldFlg) {
		
	}


}


/***********************************************
*		�S���̊֐��̒�`
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