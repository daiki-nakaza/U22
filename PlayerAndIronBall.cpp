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

	*ironX = px + LOCK_MAX * MAP_SIZE / 2;
	*ironY = py;
}

void LockInit(int* lockX, int* lockY, int px, int py) {
	for (int i = 0; i < LOCK_MAX; i++) {
		*(lockX + i) = px + ((i + 1) * MAP_SIZE / 2);
		*(lockY + i) = py;
	}
}

void IronHold(int* ironX, int* ironY, int px, int py, int mpx,int mpy) {
	*ironX = px + mpx + g_IronBall.r/3*2;
	*ironY = py + mpy - g_IronBall.r/3*2;
}


void IronHoldOrThrow() {

	//�v���C���[���S�������������鏈��
	if (!g_IronBall.HoldFlg && !g_IronBall.ThrowFlg		//�S���������Ă��Ȃ����S�����������Ă��Ȃ�
		&& g_NowKey & PAD_INPUT_1 && (Jump_Flg == 0 ||  Jump_Flg == -2)
		) {

		g_IronBall.New_x = g_IronBall.x;
		g_IronBall.New_y = g_IronBall.y;//�ŏI�I�ȃ��Z�b�g

		if (abs((PlayerX + CHA_SIZE_X/2 + Map_PlayerX) - g_IronBall.x) < 57
			&& abs((PlayerY +CHA_SIZE_Y/2 + Map_PlayerY) - g_IronBall.y) < 60
			) {//�v���X�E�}�C�i�X�S�������΂ɂ���B���Ƃł����W�ǉ�����B
			g_IronBall.HoldFlg = true;
			Locka.LenkaX += (PlayerX + CHA_SIZE_X / 2 + Map_PlayerX) - g_IronBall.x;
			Locka.LenkaY += (PlayerY - 16 + Map_PlayerY) - g_IronBall.y;
		}

		else if ((PlayerX + CHA_SIZE_X / 2 + Map_PlayerX) - g_IronBall.x > 0) {//�S���F�v���C���[�̏��ɂ���
			if (Jump_Flg == -2) {//�Ԃ牺�����Ă���Ƃ��S�������������p�^�[��
				g_IronBall.New_x += 2;
				g_IronBall.New_y -= 4;//�d�͂̂����œS�������ɂ߂荞��ł���̂łȂ���
				if (!g_IronBall.HitCheck()) {//����ɂЂ���
					g_IronBall.x += 2;
					Locka.LenkaX += 2;
				}
				else if (true) {//�S�������ɂ͈����Ȃ��l����Ȃ�S������Ɉ�����B

				}
			}
			else if (Jump_Flg == 0) {//�Ԃ牺�����Ă��Ȃ��B���������
				g_IronBall.New_x += 2;
				g_IronBall.New_y -= 4;//�d�͂̂����œS�������ɂ߂荞��ł���̂łȂ���
				if (!g_IronBall.HitCheck()) {//����ɂЂ���
					//g_IronBall.x += 2;
					Locka.HenkaX += 2;
					Locka.HI = 2;
				}
				else if (true) {//�S�������ɂ͈����Ȃ��l����Ȃ�S������Ɉ�����B

				}
				/*
				g_IronBall.New_x += 2;
				g_IronBall.New_y -= 4;//�d�͂̂����œS�������ɂ߂荞��ł���̂łȂ���
				if (!g_IronBall.HitCheck()) {//����ɂЂ���
					g_IronBall.x += 2;
					Locka.LenkaX += 2;
				}
				else if (true) {//�S�������ɂ͈����Ȃ��l����Ȃ�S������Ɉ�����B

				}
				*/
			}
		}
		else if ((PlayerX + CHA_SIZE_X / 2 + Map_PlayerX) - g_IronBall.x < 0) {//�v���C���[�F�S���̏��ɂ���
			if (Jump_Flg == -2) {
				g_IronBall.New_x -= 2;
				g_IronBall.New_y -= 4;//�d�͂̂����œS�������ɂ߂荞��ł���̂łȂ���
				if (!g_IronBall.HitCheck()) {
					g_IronBall.x -= 2;
					Locka.LenkaX -= 2;
				}
				else if (true) {//�S�������ɂ͈����Ȃ��l����Ȃ�S������Ɉ�����B

				}
			}
			else if (Jump_Flg == 0) {
				g_IronBall.New_x -= 2;
				g_IronBall.New_y -= 4;//�d�͂̂����œS�������ɂ߂荞��ł���̂łȂ���
				if (!g_IronBall.HitCheck()) {
					Locka.HenkaX -= 2;
					Locka.HI = -2;
				}
				else if (true) {//�S�������ɂ͈����Ȃ��l����Ȃ�S������Ɉ�����B

				}
				/*g_IronBall.New_x -= 2;
				g_IronBall.New_y -= 4;//�d�͂̂����œS�������ɂ߂荞��ł���̂łȂ���
				if (!g_IronBall.HitCheck()) {
					g_IronBall.x -= 2;
					Locka.LenkaX -= 2;
				}
				else if (true) {//�S�������ɂ͈����Ȃ��l����Ȃ�S������Ɉ�����B

				}*/
			}
		}

		g_IronBall.New_x = g_IronBall.x;
		g_IronBall.New_y = g_IronBall.y;//�ŏI�I�ȃ��Z�b�g
	}
	else if (g_IronBall.HoldFlg && !g_IronBall.ThrowFlg	//�S���������Ă��Ă��S�����������Ă��Ȃ�
		&& g_NowKey & PAD_INPUT_2) {
		g_IronBall.HoldFlg = false;
		g_IronBall.ThrowFlg = true;
	}
	if (true) {

	}
	Locka.MoveCheck();
		///*
		if (Locka.HenkaX != 0 && Locka.HI != 0) {
			g_IronBall.x += Locka.HI;
			Locka.New_x[LOCK_MAX - 1] += Locka.HI;
		}
		//*/
	Locka.HenkaY = 0;
	Locka.HenkaX = 0;
	Locka.HI = 0;
	Locka.Move();
}


//bool IronToEnemy() {
//
//	if (g_Enemy.picDir) {			//�E�����̏���
//		//���̈ړ��̏ꏊ���S���Ɣ���Ă�����true��Ԃ�
//		if ((g_Enemy.y + g_Enemy.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
//			&& (((g_Enemy.x + g_Enemy.w - MapDrawPointX) + (g_Enemy.direct * g_Enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x - g_IronBall.r) / MAP_SIZE + MapX) return true;
//	}
//	else {							//�������̏���
//		//���̈ړ��̏ꏊ���S���Ɣ���Ă�����true��Ԃ�
//		if ((g_Enemy.y + g_Enemy.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
//			&& (((g_Enemy.x - MapDrawPointX) + (g_Enemy.direct * g_Enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x + g_IronBall.r) / MAP_SIZE + MapX) return true;
//	}
//	
//
//
//		return false;
//}