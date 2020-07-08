#pragma once

#include "DxLib.h"

#define ENEMY_MAX 10

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

	int Life = 0;				//�G�̃��C�t

	void WalkInit();			//�n�ʂ̓G�̏���������
	void WalkMove();			//�n�ʂ̓G�̏���

	void ShootInit();			//���G�̏���������
	void ShootMove();			//���G�̏���

	void Disp();				//�G�̕`�揈��
};


struct BulletInfo {
	int x, y;			//�e�ۂ̍��W
	int w, h;			//�e�ۂ̕��ƍ���

	bool DispFlg = FALSE;		//�\���t���O

	int direct;			//�G�̌��� (�E:1  ��:-1)
	bool picDir;			//�摜�̌���
	
	int Speed;	//�e�ۂ̃X�s�[�h

	void Init();			//�e�ۂ̏���������
	void Move();			//�e�ۂ̏���
	void Disp();			//�e�ۂ̕\������

};

/**********************************************
*�@�@�֐��̃v���g�^�C�v�錾
*********************************************/
void enemyDisp();			//�G�̕`�揈��
void enemyMove();			//�G�̓���

bool EnemyCheckHit(enemyInfo enemy);		//�G���̓����蔻��`�F�b�N

//void EnemyShoot();



/*********************************************
*�ϐ��̐錾
*******************************************/
extern enemyInfo g_Enemy[ENEMY_MAX];

//extern BulletInfo Bullet[]

