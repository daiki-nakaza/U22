#pragma once

#include "DxLib.h"

#include "Enemy.h"


struct Boss : public enemyInfo
{
	int TPSpace[2][TP_MAX];		//�e���|�[�g�ꏊ�̐ݒ�

	int Firecnt = 0;		 //���˂̃J�E���g
	int BulletCnt = 0;		//5���A���Œe�𔭎˂�����
	int ReloadCnt = 0;		//�����[�h�̎��ԃJ�E���g

	int TPtime;				//�e���|�[�g�̎��ԃJ�E���g

	LockBullet Lock[BOSS_Bullet_MAX];		//�e��5��
	ChargeBullet charge[BOSS_Bullet_MAX];		//�e��5��
	RazerBullet Razer;							//�Q���r

	void BossInit(int Tempx, int Tempy);			//����������
	void TPInit(int Tempx, int Tempy);			//����������
	void BossMove();							//����
	void Disp();								//�\��	
};


/*********************************************
*�ϐ��̐錾
*******************************************/

extern Boss g_Boss;
extern int SetTP;
