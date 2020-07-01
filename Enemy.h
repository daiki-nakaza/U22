#pragma once

#include "DxLib.h"

/**************************************************************
*		�G�̏����������\���̂̐錾
***************************************************************/
//#define 

struct enemyInfo
{
	int x, y;			//�G��X���W�AY���W
	int w, h;			//�G�̕��ƍ���
	int direct;			//�G�̌��� (�E:1  ��:-1)
	int speed;			//�G�̃X�s�[�h

	int pic[4];			//�摜�p�ϐ�
	int anm;			//�A�j���[�V�����p�ϐ�
	bool picDir;			//�摜�̌���

	bool DispFlg = FALSE;		//�G���̕\���̃t���O


	void WalkInit();			//�n�ʂ̓G�̏���������
	void Disp();				//�G�̕`�揈��
	void WalkMove();			//�n�ʂ̓G�̏���
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

