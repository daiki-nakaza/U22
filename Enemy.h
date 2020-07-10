#pragma once

#include "DxLib.h"

#include "Bullet.h"
#include "Define.h"



struct enemyInfo
{
	int x, y;			//敵のX座標、Y座標
	int w, h;			//敵の幅と高さ
	int direct;			//敵の向き (右:1  左:-1)
	int speed;			//敵のスピード
	int type;			//敵のタイプ
	int outtime;		//一度攻撃をもらったらしばらく無敵

	int pic;			//画像用変数
	int anm;			//アニメーション用変数
	bool picDir;			//画像の向き

	bool DispFlg = false;		//敵をの表示のフラグ
	bool AttckFlg = false;		//敵の攻撃フラグ

	int Life = 0;				//敵のライフ


	BulletInfo Bullet[Bullet_MAX];			//撃つ敵が使う弾丸大体３発ぐらいかなぁ？

	void WalkInit();			//徘徊している敵の初期化処理
	void WalkMove();			//徘徊している敵の処理

	void ShootInit();			//撃つ敵の初期化処理
	void ShootMove();			//撃つ敵の処理

	void Disp();				//敵の描画処理
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

