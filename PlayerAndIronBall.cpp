#include "DxLib.h"

#include "Define.h"
#include "PlayerAndIronBall.h"

#include "Player.h"
#include "accessory.h"
#include "Enemy.h"
#include "Map.h"

/**************************************
*	関数の定義
***************************************/
void IronInit(int *ironX, int *ironY, int px,int py) {

	*ironX = px + LOCK_MAX * MAP_SIZE / 2;
	*ironY = py;
}

void LockInit(int* lockX, int* lockY, int px, int py) {
	for (int i = 0; i < LOCK_MAX; i++) {
		*(lockX + i) = px + ((i + 1) * MAP_SIZE / 2);
		*(lockY + i) = py;
	}
}

void IronHold(int* ironX, int* ironY, int px, int py, int mpx,int mpy) {
	*ironX = px + mpx + g_IronBall.r/3*2;
	*ironY = py + mpy - g_IronBall.r/3*2;
}


void IronHoldOrThrow() {

	//プレイヤーが鉄球を持つか投げる処理
	if (!g_IronBall.HoldFlg && !g_IronBall.ThrowFlg		//鉄球を持っていないかつ鉄球が投げられていない
		&& g_NowKey & PAD_INPUT_1 && (Jump_Flg == 0 ||  Jump_Flg == -2)
		) {

		g_IronBall.New_x = g_IronBall.x;
		g_IronBall.New_y = g_IronBall.y;//最終的なリセット

		if (abs((PlayerX + CHA_SIZE_X/2 + Map_PlayerX) - g_IronBall.x) < 57
			&& abs((PlayerY +CHA_SIZE_Y/2 + Map_PlayerY) - g_IronBall.y) < 60
			) {//プラス・マイナス鉄球がそばにある。あとでｙ座標追加する。
			g_IronBall.HoldFlg = true;
			Locka.LenkaX += (PlayerX + CHA_SIZE_X / 2 + Map_PlayerX) - g_IronBall.x;
			Locka.LenkaY += (PlayerY - 16 + Map_PlayerY) - g_IronBall.y;
		}

		else if ((PlayerX + CHA_SIZE_X / 2 + Map_PlayerX) - g_IronBall.x > 0) {//鉄球：プレイヤーの順にいる
			if (Jump_Flg == -2) {//ぶら下がっているとき鉄球をうごかすパターン
				g_IronBall.New_x += 2;
				g_IronBall.New_y -= 4;//重力のせいで鉄球が下にめり込んでいるのでなくす
				if (!g_IronBall.HitCheck()) {//正常にひけた
					g_IronBall.x += 2;
					Locka.LenkaX += 2;
				}
				else if (true) {//鉄球が横には引けない人が上なら鉄球を上に引ける。

				}
			}
			else if (Jump_Flg == 0) {//ぶら下がっていない。鎖から引く
				g_IronBall.New_x += 2;
				g_IronBall.New_y -= 4;//重力のせいで鉄球が下にめり込んでいるのでなくす
				if (!g_IronBall.HitCheck()) {//正常にひけた
					//g_IronBall.x += 2;
					Locka.HenkaX += 2;
					Locka.HI = 2;
				}
				else if (true) {//鉄球が横には引けない人が上なら鉄球を上に引ける。

				}
				/*
				g_IronBall.New_x += 2;
				g_IronBall.New_y -= 4;//重力のせいで鉄球が下にめり込んでいるのでなくす
				if (!g_IronBall.HitCheck()) {//正常にひけた
					g_IronBall.x += 2;
					Locka.LenkaX += 2;
				}
				else if (true) {//鉄球が横には引けない人が上なら鉄球を上に引ける。

				}
				*/
			}
		}
		else if ((PlayerX + CHA_SIZE_X / 2 + Map_PlayerX) - g_IronBall.x < 0) {//プレイヤー：鉄球の順にいる
			if (Jump_Flg == -2) {
				g_IronBall.New_x -= 2;
				g_IronBall.New_y -= 4;//重力のせいで鉄球が下にめり込んでいるのでなくす
				if (!g_IronBall.HitCheck()) {
					g_IronBall.x -= 2;
					Locka.LenkaX -= 2;
				}
				else if (true) {//鉄球が横には引けない人が上なら鉄球を上に引ける。

				}
			}
			else if (Jump_Flg == 0) {
				g_IronBall.New_x -= 2;
				g_IronBall.New_y -= 4;//重力のせいで鉄球が下にめり込んでいるのでなくす
				if (!g_IronBall.HitCheck()) {
					Locka.HenkaX -= 2;
					Locka.HI = -2;
				}
				else if (true) {//鉄球が横には引けない人が上なら鉄球を上に引ける。

				}
				/*g_IronBall.New_x -= 2;
				g_IronBall.New_y -= 4;//重力のせいで鉄球が下にめり込んでいるのでなくす
				if (!g_IronBall.HitCheck()) {
					g_IronBall.x -= 2;
					Locka.LenkaX -= 2;
				}
				else if (true) {//鉄球が横には引けない人が上なら鉄球を上に引ける。

				}*/
			}
		}

		g_IronBall.New_x = g_IronBall.x;
		g_IronBall.New_y = g_IronBall.y;//最終的なリセット
	}
	else if (g_IronBall.HoldFlg && !g_IronBall.ThrowFlg	//鉄球を持っていてかつ鉄球が投げられていない
		&& g_NowKey & PAD_INPUT_2) {
		g_IronBall.HoldFlg = false;
		g_IronBall.ThrowFlg = true;
	}
	if (true) {

	}
	Locka.MoveCheck();
		///*
		if (Locka.HenkaX != 0 && Locka.HI != 0) {
			g_IronBall.x += Locka.HI;
			Locka.New_x[LOCK_MAX - 1] += Locka.HI;
		}
		//*/
	Locka.HenkaY = 0;
	Locka.HenkaX = 0;
	Locka.HI = 0;
	Locka.Move();
}


//bool IronToEnemy() {
//
//	if (g_Enemy.picDir) {			//右向きの処理
//		//次の移動の場所が鉄球と被っていたらtrueを返す
//		if ((g_Enemy.y + g_Enemy.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
//			&& (((g_Enemy.x + g_Enemy.w - MapDrawPointX) + (g_Enemy.direct * g_Enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x - g_IronBall.r) / MAP_SIZE + MapX) return true;
//	}
//	else {							//左向きの処理
//		//次の移動の場所が鉄球と被っていたらtrueを返す
//		if ((g_Enemy.y + g_Enemy.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
//			&& (((g_Enemy.x - MapDrawPointX) + (g_Enemy.direct * g_Enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x + g_IronBall.r) / MAP_SIZE + MapX) return true;
//	}
//	
//
//
//		return false;
//}