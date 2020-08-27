#pragma once

#include "DxLib.h"

/**************************************************************
*		�e�ۂ̏����������\���̂̐錾
***************************************************************/

struct BulletInfo {
	int x, y;			//�e�ۂ̍��W
	int w, h;			//�e�ۂ̕��ƍ���

	bool DispFlg = FALSE;		//�\���t���O

	int pic;			//�摜�p�ϐ�

	int direct;			//�G�̌��� (�E:1  ��:-1)
	bool picDir;			//�摜�̌���

	int Speed;	//�e�ۂ̃X�s�[�h

	void Disp();			//�e�ۂ̕\������

	bool CheckHitBall();		//�S���ɂ������Ă�����
	bool CheckHitPlayer();		//�v���C���[�ɂ������Ă�����

	bool CheckWindow();		//��ʂɂ��邩�ǂ���

};


//�^��������Ԓe��
struct NormalBullet : public BulletInfo 
{
	void Init(const int Ex, const int Ey);			//�e�ۂ̏���������
	void Move(const int dir);			//�e�ۂ̏���
};

//�v���C���[�̓��Ɍ������Ĕ�Ԓe��

struct LockBullet : public BulletInfo
{
	float y;			//y���W��float�^�ō�蒼��
	float SpeedY;			//�c�̃X�s�[�h


	void Disp();			//�e�ۂ̕\������
	void Init(const int Ex, const int Ey);			//�e�ۂ̏���������
	void Move(const int dir);			//�e�ۂ̏���

	bool CheckHitBall(int By);		//�S���ɂ������Ă�����
	bool CheckHitPlayer(int By);		//�v���C���[�ɂ������Ă�����

};

//��Ɍ������Ĕ�񂾂Ȃ񂽂炷��e��
struct ChargeBullet : public BulletInfo
{
	int SpeedY;			//�c�̃X�s�[�h

	int type;			//�E������

	int sequence;		//1:�c�ɔ�΂�	2:����Ɍ������Ĕ��ł���
	int anm;

	int pic[2];			//�摜�p�ϐ�
	int Cr;				//�F��ς���p�̕ϐ�(���������Ȃ�)


	void Init(const int Ex, const int Ey);			//�e�ۂ̏���������
	void Move(const int dir);			//�e�ۂ̏���
	void Disp();
};

struct RazerBullet : public BulletInfo			//�g���C
{
	const int RazerX = 37, RazerY = 23;

	int BWidth;		//���[�U�[�̒����̒���
	int pic[3];
	int EndFlg;

	void Init(const int Ex, const int Ey);			//�e�ۂ̏���������
	void Move(const int dir);			//�e�ۂ̏���
	void Disp();
};

