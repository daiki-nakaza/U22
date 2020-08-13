#pragma once

#include "Define.h"

#define IRONBALL_R 24


struct partsInfo
{
	int x, y;			//鉄球のX座標、Y座標
	int New_x, New_y;   //鉄球の新しい座標
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
	void  HitBectl();				//現在の座標が障害物にめり込んでいるかどうか

	void Init();			//鉄球の初期化処理
	void Disp();				//鉄球の描画処理
	void Move();			//鉄球の処理
	void Throw();			//鉄球が飛んでいく処理
};


//鎖の構造体
struct Lock
{
	int x[LOCK_MAX], y[LOCK_MAX];          //鎖のｘ座標とy座標。丸が８個ある
	int New_x[LOCK_MAX], New_y[LOCK_MAX];

	int ro;                         //半径
	int HenkaX, HenkaY;				//キャラが動いたときの鎖の変化量。プラスなら右と下にマイナスなら左と上。これが０にならないとキャラが移動できない
	int LenkaX, LenkaY;				//鉄球が動いたときの鎖の変化量。
	int HI;							//引っ張られているフラグ。ー１、０、１
	int Wall[LOCK_MAX];				//鎖が壁にあたっているので、直線距離じゃなくする
	int WI;							//人がぶら下がっているフラグ。－１、０、１
	int RD;							//横移動しているときに鎖が横はいっぱいな時のフラグ。－１．０．１

	int HitCheck(int num);          //鎖の当たり判定

	void Init();             //鎖の初期化処理
	void Disp();             //鎖の描画処理
	void MoveCheck();		 //鎖が移動できるかどうか確かめる
	void Move();             //鎖の移動処理
	void Throw();            //鎖が飛んでいく処理
	void Gravity();			 //鎖の重力処理
};


//鉄球の構造体の宣言
extern partsInfo g_IronBall;			//鉄球の情報を持った変数
extern Lock Locka;						//鎖の情報を持った変数


/**********************************************
*　　関数のプロトタイプ宣言
*********************************************/
void IronBallDisp();		//鉄球の描画処理
void IronBallMove();		//鉄球の挙動処理