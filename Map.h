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

extern int MapDrawPointX, MapDrawPointY;		// 
extern int MapChipNumX, MapChipNumY;			//
extern int MapX, MapY;                    //�}�b�v�̂��A��

extern int g_MapChip[HEIGHT * 2][WIDTH];