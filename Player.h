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
extern int PlayerLife;		//プレイヤーのライフ
extern int Playerouttime;

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


extern int ClearTime;  //クリア制御用変数



extern int Player_Pic[4];//プレイヤー移動の画像
extern int Player_Pic_R[4];//逆プレイヤー移動の画像

extern int Player_Pic_Attack[6];//プレイヤー移動の画像
extern int Player_Pic_Attack_R[6];//逆プレイヤー移動の画像

extern int Player_Pic_Down;//プレイヤーしゃがみの画像
extern int Player_Pic_Down_R;//逆プレイヤーしゃがみの画像

extern int Player_Pic_Hold[4];//プレイヤーが鉄球をもって移動する画像
extern int Player_Pic_Hold_R[4];//逆プレイヤーが鉄球をもって移動する画像

extern int Player_HP[8];//プレイヤーHPの画像

//extern int g_IronDamage;	  // 鉄球が敵に当たったSE格納変数
extern int g_IronSlide;		  // 鉄球を引っ張るSE格納変数
extern int g_IronSwing;		  // 鉄球を投げるSE格納変数
extern int g_Landing;		  // プレイヤーが地面に着地した時のSE格納変数
extern int g_Player_Damage;   // プレイヤーが被弾したときのSE格納変数
extern int g_Player_Jump;	  // ジャンプSE格納変数
extern int g_Sword_Damage;    // 剣で敵を切ったSE格納変数
extern int g_Sword_Swing;	  // 剣を振るSE格納変数


/***************************************************************************
*          関数のプロトタイプ宣言  
********************************************************************************/

void PlayerInit();
void PlayerMove();
void PlayerDisp();
void PlayerGravity(int bn);
void PlayerAttack();
void PlayerDamage();
