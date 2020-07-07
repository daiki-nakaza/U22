#pragma once

#include "Define.h"

#define IRONBALL_R 24


struct partsInfo
{
	int x, y;			//�S����X���W�AY���W
	int r;			//�S���̔��a
	int direct;			//�S���̌��� (�E:1  ��:-1)
	int speed;			//�S���̃X�s�[�h

	int pic;			//�摜�p�ϐ�
	int anm;			//�A�j���[�V�����p�ϐ�
	bool picDir;			//�摜�̌���

	bool DispFlg = FALSE;		//�S���̕\���̃t���O�@����Ȃ�����
	bool HoldFlg = FALSE;		//�S���������Ă��邩
	bool ThrowFlg = FALSE;		//�������Ă��邩

	bool HitCheck();			//�n�ʂƂ̓����蔻��@�������Ă����true �������Ă��Ȃ����false

	void Init();			//�S���̏���������
	void Disp();				//�S���̕`�揈��
	void Move();			//�S���̏���
	void Throw();			//�S�������ł�������
};


//�S���̍\���̂̐錾
extern partsInfo g_IronBall;			//�S���̏����������ϐ�


/**********************************************
*�@�@�֐��̃v���g�^�C�v�錾
*********************************************/
void IronBallDisp();		//�S���̕`�揈��
void IronBallMove();		//�S���̋�������