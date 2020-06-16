#pragma once

#include "DxLib.h"

/**************************************************************
*		�G�̏����������\���̂̐錾
***************************************************************/

struct enemyInfo
{
	int x, y;			//�G��X���W�AY���W
	int w, h;			//�G�̕��ƍ���
	int direct;			//�G�̌��� (�E:1  ��:-1)
	int speed;			//�G�̃X�s�[�h

	bool DispFlg = FALSE;		//�G���̕\���̃t���O


	void WalkInit();
	void Disp();
	void WalkMove();
};

/**********************************************
*�@�@�֐��̃v���g�^�C�v�錾
*********************************************/
void enemyDisp();			//�G�̕`�揈��
void enemyMove();			//�G�̓���

bool EnemyCheckHit(enemyInfo enemy);		//�G���̓����蔻��`�F�b�N



/*********************************************
*�ϐ��̐錾
*******************************************/
extern enemyInfo g_Enemy;

