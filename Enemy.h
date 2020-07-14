#pragma once

#include "DxLib.h"

#include "Bullet.h"
#include "Define.h"



struct enemyInfo
{
	int x, y;			//�G��X���W�AY���W
	int w, h;			//�G�̕��ƍ���
	int direct;			//�G�̌��� (�E:1  ��:-1)
	int speed;			//�G�̃X�s�[�h
	int type;			//�G�̃^�C�v
	int outtime;		//��x�U������������炵�΂炭���G

	int pic;			//�摜�p�ϐ�
	int anm;			//�A�j���[�V�����p�ϐ�
	bool picDir;			//�摜�̌���

	bool DispFlg = false;		//�G���̕\���̃t���O
	bool AttckFlg = false;		//�G�̍U���t���O

	int Life = 0;				//�G�̃��C�t


	BulletInfo Bullet[Bullet_MAX];			//���G���g���e�ۑ�̂R�����炢���Ȃ��H

	void WalkInit();			//�p�j���Ă���G�̏���������
	void WalkMove();			//�p�j���Ă���G�̏���

	void ShootInit();			//���G�̏���������
	void ShootMove();			//���G�̏���

	void Disp();				//�G�̕`�揈��
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

