#pragma once

#include "DxLib.h"

#include "Define.h"

/*************************************************************
*　　関数のプロトタイプ宣言
**************************************************************/

void MapDisp();
void MapMove();
void MapChipInit();


/*　変数の宣言　*/
//int g_MapChip[HEIGHT * 2][WIDTH];

extern int MapDrawPointX, MapDrawPointY;		// ０～31　ぬるぬる動くよう
extern int MapChipNumX, MapChipNumY;			//右拡大用変数 0,32,64::0,22,44
extern int MapX, MapY;                    //マップのｘ、ｙ

extern int g_MapChip[HEIGHT * MAP_LONG][WIDTH];

extern int MapTip;	//マップチップ画像変数
extern int g_BackGroundImage1;//背景画像
extern int g_BackGroundImage2;//背景画像
extern int g_BackGroundImage3;//背景画像
extern int g_Door[3];//クリア用のドア画像

extern int Stage;//ステージ変数




extern int g_Stage1; // ステージ1の曲格納変数
extern int g_Stage2; // ステージ2の曲格納変数
extern int g_Stage3; // ステージ3の曲格納変数
extern int g_Title;  // タイトルbgm
extern int g_GameOver; // ゲームオーバー
extern int g_BossSound;	 // ボス戦の曲格納変数

// ↓敵の効果音等↓ //
extern int g_ColorL; // 2色の弾を空中に打ち上げるSE格納変数
extern int g_Hadou;  // 波動砲のSE格納変数
extern int g_Kakusan;// 拡散弾のSE格納変数
extern int g_Shot;   // 通常弾のSE格納変数(ボスと雑魚敵)
extern int g_Warp;   // ボスのワープSE格納変数
extern int g_Sword_Damage;    // 剣で敵を切ったSE格納変数

extern int g_Cursor;
extern int g_Cursor2; // ゲームエンド