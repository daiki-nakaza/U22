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

extern int MapDrawPointX, MapDrawPointY;		// ０～31　ぬるぬる動くよう
extern int MapChipNumX, MapChipNumY;			//右拡大用変数 0,32,64::0,22,44
extern int MapX, MapY;                    //マップのｘ、ｙ

extern int g_MapChip[HEIGHT * 3][WIDTH];

extern int MapTip;	//マップチップ画像変数
extern int g_BackGroundImage;//背景画像