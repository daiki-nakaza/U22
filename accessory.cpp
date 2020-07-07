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
		DrawCircle(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY*MAP_SIZE, r, 0x000000, true);
		DrawFormatString(30, 30, 0x000000, "Y = %d\nX = %d\n", x, x + MapDrawPointX - MapX * MAP_SIZE);
		if (HoldFlg==false)DrawFormatString(100, 30, 0x000000, "HOLD");
		if (ThrowFlg==false)DrawFormatString(100, 30, 0x000000, "THROW");
	}
	else {				//�S����\��

	}
}

void partsInfo::Move() {
	if (!HitCheck() && !ThrowFlg) y += 4;
	
	//x = ((PlayerX / MAP_SIZE) + 4) * MAP_SIZE;
	if (HoldFlg) {
		
	}
	//�v���C���[���S���𓊂��邩����
	IronHoldOrThrow();
	Throw();


}

void partsInfo::Throw(){			//�S�������ł�������
	const int InitPow = -24;
	static int Pow = InitPow;
	static int move = 1;

	//if (g_NowKey & PAD_INPUT_UP) ThrowFlg = true;

	if (HoldFlg) {
		IronHold(&x,&y);
	}

	if (ThrowFlg) {			//�������Ă��鏈��
		if (Pow++ < abs(InitPow)) {
			x += 6;
			y += Pow;
			if (HitCheck()) {
				ThrowFlg = false;
				x -= 6;
				y -= Pow;
			}
		}
		else { ThrowFlg = false; }
	}
	else { Pow = InitPow; }
}

bool partsInfo::HitCheck() {		//�n�ʂƂ̓����蔻��@�������Ă����true �������Ă��Ȃ����false
	//if (g_MapChip[((y + (MAP_SIZE - IRONBALL_R)) / MAP_SIZE + MapY) + 1][(x / MAP_SIZE + MapX)] != 1		////�P���̃}�X�����Ēn�ʂ�������
	//	&& g_MapChip[((y + (MAP_SIZE - IRONBALL_R)) / MAP_SIZE + MapY) + 1][((x - IRONBALL_R) / MAP_SIZE + MapX)] != 1
	//	&& g_MapChip[((y + (MAP_SIZE - IRONBALL_R)) / MAP_SIZE + MapY) + 1][((x + IRONBALL_R) / MAP_SIZE + MapX)] != 1
	//	
	//	&& g_MapChip[((y + (MAP_SIZE - IRONBALL_R)) / MAP_SIZE + MapY) + 1][(x / MAP_SIZE + MapX)] != 1) {
	if(g_MapChip[MapY + (y + IRONBALL_R  - MapDrawPointY) / MAP_SIZE ][MapX + (x - MapDrawPointX) / MAP_SIZE] != 1		//���S�̐^��
		|| g_MapChip[MapY + (y - IRONBALL_R - MapDrawPointY) / MAP_SIZE ][MapX + (x - IRONBALL_R - MapDrawPointX) / MAP_SIZE ] != 1	//����
		|| g_MapChip[MapY + (y - IRONBALL_R - MapDrawPointY) / MAP_SIZE ][(x + IRONBALL_R - MapDrawPointX) / MAP_SIZE + MapX] != 1	//�E��
		|| g_MapChip[MapY + (y + IRONBALL_R - MapDrawPointY) / MAP_SIZE ][(x - IRONBALL_R - MapDrawPointX) / MAP_SIZE + MapX] != 1	//����
		|| g_MapChip[MapY + (y + IRONBALL_R - MapDrawPointY) / MAP_SIZE ][(x + IRONBALL_R - MapDrawPointX) / MAP_SIZE + MapX] != 1	//�E��
		){	
		return true;
	}

	return false;
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