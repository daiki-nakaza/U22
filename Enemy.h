#pragma once

#include "DxLib.h"

/**************************************************************
*		敵の情報を持った構造体の宣言
***************************************************************/
//#define 

struct enemyInfo
{
	int x, y;			//敵のX座標、Y座標
	int w, h;			//敵の幅と高さ
	int chipX,chipY;	//敵のマップチップの座標
	int direct;			//敵の向き (右:1  左:-1)
	int speed;			//敵のスピード

	int pic[4];			//画像用変数
	int anm;			//アニメーション用変数
	bool picDir;			//画像の向き

	bool DispFlg = FALSE;		//敵をの表示のフラグ


	void WalkInit();			//地面の敵の初期化処理
	void Disp();				//敵の描画処理
	void WalkMove();			//地面の敵の処理
};

/**********************************************
*　　関数のプロトタイプ宣言
*********************************************/
void enemyDisp();			//敵の描画処理
void enemyMove();			//敵の動き

bool EnemyCheckHit(enemyInfo enemy);		//敵側の当たり判定チェック



/*********************************************
*変数の宣言
*******************************************/
extern enemyInfo g_Enemy;

