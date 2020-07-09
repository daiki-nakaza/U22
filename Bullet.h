#pragma once

#include "DxLib.h"

/**************************************************************
*		弾丸の情報を持った構造体の宣言
***************************************************************/

struct BulletInfo {
	int x, y;			//弾丸の座標
	int w, h;			//弾丸の幅と高さ

	bool DispFlg = FALSE;		//表示フラグ

	int direct;			//敵の向き (右:1  左:-1)
	bool picDir;			//画像の向き

	int Speed;	//弾丸のスピード

	void Init(const int Ex, const int Ey);			//弾丸の初期化処理
	void Move(const int dir);			//弾丸の処理
	void Disp();			//弾丸の表示処理

};
