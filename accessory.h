#pragma once

#include "Define.h"

#define IRONBALL_R 24


struct partsInfo
{
	int x, y;			//鉄球のX座標、Y座標
	int r;			//鉄球の半径
	int direct;			//鉄球の向き (右:1  左:-1)
	int speed;			//鉄球のスピード

	int pic;			//画像用変数
	int anm;			//アニメーション用変数
	bool picDir;			//画像の向き

	bool DispFlg = FALSE;		//鉄球の表示のフラグ　いらないかも
	bool HoldFlg = FALSE;		//鉄球を持っているか
	bool ThrowFlg = FALSE;		//投げられているか

	bool HitCheck();			//地面との当たり判定　当たっていればtrue 当たっていなければfalse

	void Init();			//鉄球の初期化処理
	void Disp();				//鉄球の描画処理
	void Move();			//鉄球の処理
	void Throw();			//鉄球が飛んでいく処理
};


//鉄球の構造体の宣言
extern partsInfo g_IronBall;			//鉄球の情報を持った変数


/**********************************************
*　　関数のプロトタイプ宣言
*********************************************/
void IronBallDisp();		//鉄球の描画処理
void IronBallMove();		//鉄球の挙動処理