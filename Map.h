#pragma once

#include "DxLib.h"

#include "Define.h"

/*************************************************************
*�@�@�֐��̃v���g�^�C�v�錾
**************************************************************/

void MapDisp();
void MapMove();


/*�@�ϐ��̐錾�@*/
//int g_MapChip[HEIGHT * 2][WIDTH];

extern int MapDrawPointX, MapDrawPointY;		// �O�`31�@�ʂ�ʂ铮���悤
extern int MapChipNumX, MapChipNumY;			//�E�g��p�ϐ� 0,32,64::0,22,44
extern int MapX, MapY;                    //�}�b�v�̂��A��

extern int g_MapChip[HEIGHT * 3][WIDTH];

extern int MapTip;	//�}�b�v�`�b�v�摜�ϐ�
extern int g_BackGroundImage;//�w�i�摜