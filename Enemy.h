#pragma once

#include "DxLib.h"

#define ENEMY_MAX 10

/**************************************************************
*		敵の情報を持った構造体の宣言
***************************************************************/
//#define 

struct enemyInfo
{
	int x, y;			//敵のX座標、Y座標
	int w, h;			//敵の幅と高さ
	int direct;			//敵の向き (右:1  左:-1)
	int speed;			//敵のスピード

	int pic[4];			//画像用変数
	int anm;			//アニメーション用変数
	bool picDir;			//画像の向き

	bool DispFlg = FALSE;		//敵をの表示のフラグ

	int Life = 0;				//敵のライフ

	void WalkInit();			//地面の敵の初期化処理
	void WalkMove();			//地面の敵の処理

	void ShootInit();			//撃つ敵の初期化処理
	void ShootMove();			//撃つ敵の処理

	void Disp();				//敵の描画処理
};


struct BulletInfo {
	int x, y;			//弾丸の座標
	int w, h;			//弾丸の幅と高さ

	bool DispFlg = FALSE;		//表示フラグ

	int direct;			//敵の向き (右:1  左:-1)
	bool picDir;			//画像の向き
	
	int Speed;	//弾丸のスピード

	void Init();			//弾丸の初期化処理
	void Move();			//弾丸の処理
	void Disp();			//弾丸の表示処理

};

/**********************************************
*　　関数のプロトタイプ宣言
*********************************************/
void enemyDisp();			//敵の描画処理
void enemyMove();			//敵の動き

bool EnemyCheckHit(enemyInfo enemy);		//敵側の当たり判定チェック

//void EnemyShoot();



/*********************************************
*変数の宣言
*******************************************/
extern enemyInfo g_Enemy[ENEMY_MAX];

//extern BulletInfo Bullet[]

