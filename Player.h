#pragma once

#include "DxLib.h"

/*****************************************************************
*   変数の宣言
*****************************************************************/

extern bool DebugMode;//デバック用		true：デバック中			false：提出用

//プレイヤーの位置
extern int PlayerX, PlayerY;              //0～画面半分まで。（プレイヤー位置）
extern int Map_PlayerX, Map_PlayerY;      //マップ全体のスクロール位置（マップ位置）
extern int MapX, MapY;                    //マップのｘ、ｙ
extern int NewX, NewY;	// 移動する前のプレイヤーの位置を保存する変数
extern int Map_NewX, Map_NewY;	// 移動する前のプレイヤーの位置を保存する変数

extern int Bectl;		//プレイヤーの向き
extern int Attack;		//プレイヤーの攻撃用

extern int Jump_Flg;  //ジャンプ用変数 8ずつずれるのを５回繰り返す
extern int y_temp;
extern int y_prev;

extern int y_prev;//しゃがみのフラグ


extern int g_OldKey;
extern int g_NowKey;
extern int g_KeyFlg;
extern int g_OldKey2;
extern int g_NowKey2;
extern int g_KeyFlg2;
extern int g_MouseX;  //マウスｘ座標
extern int g_MouseY;  //マウスｙ座標

extern int g_GameState;  //ゲームモード


extern int Player_Pic[4];//プレイヤー移動の画像
extern int Player_Pic_R[4];//逆プレイヤー移動の画像

extern int Player_Pic_Attack[6];//プレイヤー移動の画像
extern int Player_Pic_Attack_R[6];//逆プレイヤー移動の画像

extern int Player_Pic_Down;//プレイヤーしゃがみの画像
extern int Player_Pic_Down_R;//逆プレイヤーしゃがみの画像

extern int Player_Pic_Hold[4];//プレイヤーが鉄球をもって移動する画像
extern int Player_Pic_Hold_R[4];//逆プレイヤーが鉄球をもって移動する画像



/***************************************************************************
*          関数のプロトタイプ宣言  
********************************************************************************/

void PlayerInit();
void PlayerMove();
void PlayerDisp();
void PlayerGravity();
void PlayerAttack();
