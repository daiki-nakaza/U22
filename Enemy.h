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
	int type;			//敵のタイプ//一度攻撃をもらったらしばらく無敵
	int outtime;		

	int pic;			//画像用変数
	int anm;			//アニメーション用変数
	bool picDir;			//画像の向き

	bool DispFlg = false;		//敵をの表示のフラグ
	bool AttckFlg = false;		//敵の攻撃フラグ

	int Life = 0;				//敵のライフ


	void Disp();				//敵の描画処理
	void Move();
};


//歩く敵の構造体
struct WalkEnemy : public enemyInfo
{
	void Init(int Ec);			//徘徊している敵の初期化処理
	void WalkMove();			//徘徊している敵の処理
};


//まっすぐ撃つ敵の構造体
struct ShootEnemy : public enemyInfo
{
	NormalBullet Bullet[Bullet_MAX];			//真っすぐ撃つ敵が使う弾丸３発

	void Init();			//撃つ敵の初期化処理
	void ShootMove();			//撃つ敵の処理

};


//狙い撃つ敵の構造体
struct LockShootEnemy : public enemyInfo
{

	LockBullet Bullet[Bullet_MAX];			//弾丸3発

	void Init();			//狙い撃つ敵の初期化処理
	void LockShootMove();			//撃つ敵の処理

};

//戦車の敵(上に向かって弾を飛ばす奴)
struct TankEnemy : public enemyInfo
{
	ChargeBullet Bullet[Bullet_MAX];		//弾丸3発

	void Init();			//戦車の初期化処理
	void TankMove();		//戦車の処理
};

struct RazerEnemy : public enemyInfo
{
	RazerBullet Bullet;			//波動砲変数

	int pic[3];

	void Init();
	void ShotMove();
	void Disp();
};


/**********************************************
*　　関数のプロトタイプ宣言
*********************************************/
void enemyDisp();			//敵の描画処理
void enemyMove();			//敵の動き
void enemyInit();			//敵の初期化処理

bool EnemyCheckHit(int x,int y,int direct);		//敵側の当たり判定チェック
bool CheckWindow(int x);							//ウィンドウの中にいるかどうか 入っていたらtrue

//void EnemyShoot();



/*********************************************
*変数の宣言
*******************************************/

//エラー防止用（後で消します）
extern enemyInfo g_Enemy[ENEMY_MAX];


extern WalkEnemy g_WalkEnemy[ENEMY_MAX];			//歩く敵
extern ShootEnemy g_ShootEnemy[ENEMY_MAX];			//真っすぐ撃つ敵
extern LockShootEnemy g_LockShootEnemy[ENEMY_MAX];			//狙い撃つ敵
extern TankEnemy g_TankEnemy[ENEMY_MAX];			//赤と緑の弾丸を撃つ敵
extern RazerEnemy g_RazerEnemy[ENEMY_MAX];					//波動砲の敵

//extern BulletInfo Bullet[]

