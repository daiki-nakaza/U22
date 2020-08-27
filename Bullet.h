#pragma once

#include "DxLib.h"

/**************************************************************
*		弾丸の情報を持った構造体の宣言
***************************************************************/

struct BulletInfo {
	int x, y;			//弾丸の座標
	int w, h;			//弾丸の幅と高さ

	bool DispFlg = FALSE;		//表示フラグ

	int pic;			//画像用変数

	int direct;			//敵の向き (右:1  左:-1)
	bool picDir;			//画像の向き

	int Speed;	//弾丸のスピード

	void Disp();			//弾丸の表示処理

	bool CheckHitBall();		//鉄球にあたっていたら
	bool CheckHitPlayer();		//プレイヤーにあたっていたら

	bool CheckWindow();		//画面にいるかどうか

};


//真っすぐ飛ぶ弾丸
struct NormalBullet : public BulletInfo 
{
	void Init(const int Ex, const int Ey);			//弾丸の初期化処理
	void Move(const int dir);			//弾丸の処理
};

//プレイヤーの頭に向かって飛ぶ弾丸

struct LockBullet : public BulletInfo
{
	float y;			//y座標をfloat型で作り直す
	float SpeedY;			//縦のスピード


	void Disp();			//弾丸の表示処理
	void Init(const int Ex, const int Ey);			//弾丸の初期化処理
	void Move(const int dir);			//弾丸の処理

	bool CheckHitBall(int By);		//鉄球にあたっていたら
	bool CheckHitPlayer(int By);		//プレイヤーにあたっていたら

};

//上に向かって飛んだなんたらする弾丸
struct ChargeBullet : public BulletInfo
{
	int SpeedY;			//縦のスピード

	int type;			//右か左に

	int sequence;		//1:縦に飛ばす	2:相手に向かって飛んでいく
	int anm;

	int pic[2];			//画像用変数
	int Cr;				//色を変える用の変数(今だけかなぁ)


	void Init(const int Ex, const int Ey);			//弾丸の初期化処理
	void Move(const int dir);			//弾丸の処理
	void Disp();
};

struct RazerBullet : public BulletInfo			//波動砲
{
	const int RazerX = 37, RazerY = 23;

	int BWidth;		//レーザーの長さの調整
	int pic[3];
	int EndFlg;

	void Init(const int Ex, const int Ey);			//弾丸の初期化処理
	void Move(const int dir);			//弾丸の処理
	void Disp();
};

