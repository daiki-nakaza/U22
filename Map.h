#pragma once

#include "DxLib.h"

#include "Define.h"

/*************************************************************
*　　関数のプロトタイプ宣言
**************************************************************/

void MapDisp();
void MapMove();


/*　変数の宣言　*/
//int g_MapChip[HEIGHT * 2][WIDTH];

extern int MapDrawPointX, MapDrawPointY;		// 
extern int MapChipNumX, MapChipNumY;			//
extern int MapX, MapY;                    //マップのｘ、ｙ

extern int g_MapChip[HEIGHT * 2][WIDTH];