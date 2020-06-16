#pragma once

#include "DxLib.h"

/*****************************************************************
*   変数の宣言
*****************************************************************/

//プレイヤーの位置
extern int PlayerX, PlayerY;              //0～画面半分まで。（プレイヤー位置）
extern int Map_PlayerX, Map_PlayerY;      //マップ全体のスクロール位置（マップ位置）
extern int MapX, MapY;                    //マップのｘ、ｙ
extern int OldX, OldY;	// 移動する前のプレイヤーの位置を保存する変数
extern int Map_OldX, Map_OldY;	// 移動する前のプレイヤーの位置を保存する変数


extern int g_OldKey;
extern int g_NowKey;
extern int g_KeyFlg;
extern int g_OldKey2;
extern int g_NowKey2;
extern int g_KeyFlg2;
extern int g_MouseX;//マウスｘ座標
extern int g_MouseY;//マウスｙ座標


/***************************************************************************
*          関数のプロトタイプ宣言  
********************************************************************************/

void PlayerInit();
void PlayerMove();
void PlayerDisp();
void PlayerGravity();
