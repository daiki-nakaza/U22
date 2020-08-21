#pragma once

#include "DxLib.h"

#include "Enemy.h"


struct Boss : public enemyInfo
{
	int TPSpace[2][TP_MAX];		//テレポート場所の設定

	int Firecnt = 0;		 //発射のカウント
	int BulletCnt = 0;		//5発連続で弾を発射させる
	int ReloadCnt = 0;		//リロードの時間カウント

	int TPtime;				//テレポートの時間カウント

	LockBullet Lock[BOSS_Bullet_MAX];		//弾丸5発
	ChargeBullet charge[BOSS_Bullet_MAX];		//弾丸5発
	RazerBullet Razer;							//ゲロビ

	void BossInit(int Tempx, int Tempy);			//初期化処理
	void TPInit(int Tempx, int Tempy);			//初期化処理
	void BossMove();							//処理
	void Disp();								//表示	
};


/*********************************************
*変数の宣言
*******************************************/

extern Boss g_Boss;
extern int SetTP;
