#pragma once

#include "Define.h"

#define IRONBALL_R 24


struct partsInfo
{
	int x, y;			//�S����X���W�AY���W
	int New_x, New_y;   //�S���̐V�������W
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
	void  HitBectl();				//���݂̍��W����Q���ɂ߂荞��ł��邩�ǂ���

	void Init();			//�S���̏���������
	void Disp();				//�S���̕`�揈��
	void Move();			//�S���̏���
	void Throw();			//�S�������ł�������
};


//���̍\����
struct Lock
{
	int x[LOCK_MAX], y[LOCK_MAX];          //���̂����W��y���W�B�ۂ��W����
	int New_x[LOCK_MAX], New_y[LOCK_MAX];

	int ro;                         //���a
	int HenkaX, HenkaY;				//�L�������������Ƃ��̍��̕ω��ʁB�v���X�Ȃ�E�Ɖ��Ƀ}�C�i�X�Ȃ獶�Ə�B���ꂪ�O�ɂȂ�Ȃ��ƃL�������ړ��ł��Ȃ�
	int LenkaX, LenkaY;				//�S�����������Ƃ��̍��̕ω��ʁB
	int HI;							//���������Ă���t���O�B�[�P�A�O�A�P
	int Wall[LOCK_MAX];				//�����ǂɂ������Ă���̂ŁA������������Ȃ�����
	int WI;							//�l���Ԃ牺�����Ă���t���O�B�|�P�A�O�A�P
	int RD;							//���ړ����Ă���Ƃ��ɍ������͂����ς��Ȏ��̃t���O�B�|�P�D�O�D�P

	int HitCheck(int num);          //���̓����蔻��

	void Init();             //���̏���������
	void Disp();             //���̕`�揈��
	void MoveCheck();		 //�����ړ��ł��邩�ǂ����m���߂�
	void Move();             //���̈ړ�����
	void Throw();            //�������ł�������
	void Gravity();			 //���̏d�͏���
};


//�S���̍\���̂̐錾
extern partsInfo g_IronBall;			//�S���̏����������ϐ�
extern Lock Locka;						//���̏����������ϐ�


/**********************************************
*�@�@�֐��̃v���g�^�C�v�錾
*********************************************/
void IronBallDisp();		//�S���̕`�揈��
void IronBallMove();		//�S���̋�������