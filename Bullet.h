#pragma once

#include "DxLib.h"

/**************************************************************
*		�e�ۂ̏����������\���̂̐錾
***************************************************************/

struct BulletInfo {
	int x, y;			//�e�ۂ̍��W
	int w, h;			//�e�ۂ̕��ƍ���

	bool DispFlg = FALSE;		//�\���t���O

	int direct;			//�G�̌��� (�E:1  ��:-1)
	bool picDir;			//�摜�̌���

	int Speed;	//�e�ۂ̃X�s�[�h

	void Init(const int Ex, const int Ey);			//�e�ۂ̏���������
	void Move(const int dir);			//�e�ۂ̏���
	void Disp();			//�e�ۂ̕\������

};
