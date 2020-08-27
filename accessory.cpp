#include "DxLib.h"
#include "Math.h"

#include "accessory.h"

#include "PlayerAndIronBall.h"
#include "Map.h"

/**************************************************
*		変数の宣言
***************************************************/
partsInfo g_IronBall;			//鉄球の情報を持った変数
Lock Locka;						//鎖の情報を持った変数

/*****************************************************
*		関数の定義
********************************************************/

//初期化処
void partsInfo::Init() {                 // 鉄球の初期化
	x = 0;
	y = 0;
	New_x = 0;
	New_y = 0;
	IronInit(&x, &y);		//座標をプレイヤーの隣に代入
	New_x = x;
	New_y = y;

	r = IRONBALL_R;

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, ENEMY_SIZE, ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//左向きから始める

	speed = 2;						//鉄球のスピード
	picDir = true;

	DispFlg = TRUE;					//鉄球を表示


}

void Lock::Init() {
	LockInit(&x[0], &y[0]);
	for (int i = 0; i < LOCK_MAX; i++) {
		New_x[i] = x[i];
		New_y[i] = y[i];
		Wall[i] = 0;
	}

	ro = 4;

	HenkaX = 0;		//人の変化量
	HenkaY = 0;		//人の変化量

	LenkaX = 0;		//鉄球の変化量
	LenkaY = 0;		//鉄球の変化量

	HI = 0;//引っ張られているフラグ
	WI = 0;//ぶら下がっているフラグ
	RD = 0;//縦に上がるフラグ

}

//描画処理
void partsInfo::Disp() {


	if (DispFlg) {		//鉄球表示
		//DrawBox(x,y, x + w, y + h, 0x000000, true);
		//DrawRotaGraphFast2(x, y, 0, 0, 1, 0, pic, true, picDir);
	//	DrawCircle(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE, MAP_SIZE * 9, 0xffffff, true);
		DrawCircle(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE, r, 0x000000, true);
		if (DebugMode) {
			DrawFormatString(30, 90, 0x000000, "Y = %d\nX = %d\n", /*Locka.x[LOCK_MAX-1]*/Locka.y[0], PlayerY);
			if (HoldFlg)DrawFormatString(100, 30, 0x000000, "HOLD");
			if (ThrowFlg)DrawFormatString(100, 30, 0x000000, "THROW");
		}
	}
	else {				//鉄球非表示

	}
}

void Lock::Disp() {
	for (int i = 0; i < LOCK_MAX; i++) {
		DrawCircle(x[i] + MapDrawPointX - MapX * MAP_SIZE, y[i] - MapDrawPointY - MapY * MAP_SIZE, ro, GetColor(252 - i*30,i*30,0), true);
	}
	if (DebugMode) {
		DrawFormatString(30, 30, 0x000000, "Y = %d\nX = %d\n", x[0] + MapDrawPointX - MapX * MAP_SIZE, PlayerX + 16);
	}
}

//移動できるかどうか確かめる
void Lock::MoveCheck() {
	int ox, oy;//ローカル変数、鎖１つずつの差を示している
	bool Gr = true;//ローカル変数、HenkaYのところで使用。すべての鎖が地面についているならHenkaYをなくす。
	int FP = 0;//鎖を引っ張ったとき用HenkaYのところで数字をかえる。HenkaXのところで使用
	int EL = 0;//ローカル変数、HenkaXのところで使用
	//HenkaY = 0;
	//LenkaY = 0;
	for (int i = 0; i < LOCK_MAX; i++) {
		New_x[i] = x[i];
		New_y[i] = y[i];
	}

	//移動量なしなら終わり
	if (HenkaX == 0 && HenkaY == 0 && LenkaX == 0 && LenkaY == 0) {
		return;
	}
	if (DebugMode) {
		if (g_IronBall.HoldFlg == true) {
			/*HenkaX = 0;
			HenkaY = 0;*/
		}
	}
		
	/////////////////////////////////////////////////////////////////////////////////////////////
	if (g_IronBall.ThrowFlg == true) {
		//ｘ座標の変化
		//プラスなので右に移動している。
		if (LenkaX > 0) {
			int nn = 0;
			int EnY = 0;//鎖が上下に移動したなら、その１個後の鎖も上下に移動させる
			int EnY2 = 0;
			for (int i = LOCK_MAX - 1; i > 0; i--) {
				//変化量なしならブレイク
				if (LenkaX == 0) {
					break;
				}
				if ((PlayerX + 16 + Map_PlayerX) - New_x[i] <= 0) {
					continue;
				}

				//１個前の鎖が上下に移動したら移動
				EnY2 = EnY;
				while (EnY > 0) {
					New_y[i]++;
					EnY--;
					if (HitCheck(i) == true) {//
						New_y[i]--;
						if (New_x[i] - New_x[i + 1] >= 0) {
							New_x[i]--;
							if (HitCheck(i) == true) {//
								New_x[i]++;
							}
						}
					}
				}
				while (EnY < 0) {
					New_y[i]--;
					EnY++;
					if (HitCheck(i) == true) {//
						New_y[i]++;
						if (New_x[i] - New_x[i + 1] >= 0) {
							New_x[i]--;
							if (HitCheck(i) == true) {//
								New_x[i]++;
							}
						}
					}
				}
				EnY = EnY2;

				//座標移動
				for (int j = 0; LenkaX > j; j++) {
					if ((PlayerX + 16 + Map_PlayerX) - New_x[i] <= 0) {
						break;
					}
					New_x[i]++;
					nn = 1;
		//			LenkaX--;
					if (HitCheck(i) == true) {//壁に当たっているので上に上昇させる
						nn = 0;
						New_x[i]--;
						if (i != LOCK_MAX - 1
							&& New_y[i] - New_y[i + 1] > 0) {
							New_y[i]--;//上に上昇
							EnY--;
							if (HitCheck(i) == true) {//
								New_y[i]++;
								EnY++;
								if (New_x[i] - New_x[i + 1] >= 0) {
									New_x[i]--;
									if (HitCheck(i) == true) {//
										New_x[i]++;
									}
								}
							}
						}
						else if (i != LOCK_MAX - 1 && New_y[i] - New_y[i + 1] < 0) {
							New_y[i]++;//
							EnY++;
							if (HitCheck(i) == true) {//
								New_y[i]--;
								EnY--;
								if (New_x[i] - New_x[i + 1] >= 0) {
									New_x[i]--;
									if (HitCheck(i) == true) {//
										New_x[i]++;
									}
								}
							}
						}
						//	EL++;
					}
					
				}

				while (i != LOCK_MAX - 1
					&& New_x[i + 1] - New_x[i] >= 0
					&& pow((double)New_x[i + 1] - (double)New_x[i], 2.0) + pow((double)New_y[i + 1] - (double)New_y[i], 2.0) >= pow(IRONBALL_R, 2.0)
					) {
					New_x[i]++;
					nn = 1;

					if (HitCheck(i) == true) {//壁に当たっているので上に上昇させる
						nn = 0;
						New_x[i]--;
						if (i != LOCK_MAX - 1
							&& New_y[i] - New_y[i + 1] > 0) {
							New_y[i]--;//
							EnY--;
						}
						else if (i != LOCK_MAX - 1
							&& New_y[i] - New_y[i + 1] < 0) {
							New_y[i]++;//
							EnY++;
						}
						//	EL++;
					}
				}
			}
		}
		//マイナスなので左に移動している。
		else if (LenkaX < 0) {
		int nn = 0;
		int EnY = 0;//鎖が上下に移動したなら、その１個後の鎖も上下に移動させる
		int EnY2 = 0;
			for (int i = LOCK_MAX - 1; i > 0; i--) {

				//変化量なしならブレイク
				if (LenkaX == 0) {
					break;
				}
				if ((PlayerX + 16 + Map_PlayerX) - New_x[i] >= 0) {
					continue;
				}

				EnY2 = EnY;//すべてを保存
			//１個前の鎖が上下に移動したら移動
				while (EnY > 0) {
					New_y[i]++;
					EnY--;
					if (HitCheck(i) == true) {//
						New_y[i]--;
					}
				}
				while (EnY < 0) {
					New_y[i]--;
					EnY++;
					if (HitCheck(i) == true) {//
						New_y[i]++;
					}
				}
				EnY = EnY2;
				

				//座標移動
				for (int j = 0; LenkaX < j;j--) {
					if ((PlayerX + 16 + Map_PlayerX) - New_x[i] >= 0) {
						break;
					}
					New_x[i]--;
					nn = 1;
					if (HitCheck(i) == true) {//壁に当たっているので上に上昇させる
						New_x[i]++;
						nn = 0;
						if (i != LOCK_MAX - 1
							&& New_y[i] - New_y[i + 1] > 0) {
							New_y[i]--;//
							EnY--;
						}
						else if (i != LOCK_MAX - 1
							&& New_y[i] - New_y[i + 1] < 0) {
							New_y[i]++;//
							EnY++;
						}
					}
				}

				while (i != LOCK_MAX - 1
					&& New_x[i] - New_x[i + 1] >= 0
					&& pow((double)New_x[i] - (double)New_x[i + 1], 2.0) + pow((double)New_y[i] - (double)New_y[i + 1], 2.0) >= pow(IRONBALL_R, 2.0)

					) {
					New_x[i]--;
					nn = 1;

					if (HitCheck(i) == true) {//壁に当たっているので上に上昇させる
						New_x[i]++;
						nn = 0;
						if (i != LOCK_MAX - 1
							&& New_y[i] - New_y[i + 1] > 0) {
							New_y[i]--;//
							EnY--;
						}
						else if (i != LOCK_MAX - 1
							&& New_y[i] - New_y[i + 1] < 0) {
							New_y[i]++;//
							EnY++;
						}
					}

				}
			}
		}

		////移動成功。あと当たりチェックもする
		//if (LenkaX == 0) {

		//}//移動失敗。人のほうを動かす。エラーするかも
		//else {
		//	NewX += LenkaX;
		//	HenkaX += LenkaX;
		//}
	}
////////////////////////////////////////////////////////////////////////////////////////////////
	/*********************************
	*鉄球が移動したときの変化
	*********************************/
	//y座標の変化
	//マイナスなら。上にいく。プラスもある
	if (LenkaY < 0) {
		for (int i = LOCK_MAX - 1; i > 0; i--) {
			//変化量なしならブレイク
			if (LenkaY == 0) {
				break;
			}
			//鎖の差を図る
		//	oy = /*abs(x[i] - x[i + 1])*/  New_y[i + 1] - New_y[i];
			//座標移動
			while (LenkaY < 0) {
				New_y[i]--;
				//oy++;
				LenkaY++;
				if (HitCheck(i) == true) {//壁に当たっているので左か右に移動させる。ここ考えるべき
					New_y[i]++;//ここかえる
					//if (x[i] - x[i + 1] >= 0) {
					//	New_x[i]++;
					//	//HenkaX++;
					//}
					//else if (x[i] - x[i + 1] < 0) {
					//	New_x[i]--;
					//	//HenkaX--;
					//}

				}
			}

			while (i != LOCK_MAX - 1
				&& New_y[i] - New_y[i + 1] >= 0
				&& pow((double)New_x[i] - (double)New_x[i + 1], 2.0) + pow((double)New_y[i] - (double)New_y[i + 1], 2.0) >= pow(IRONBALL_R, 2.0)
				) {
				New_y[i]--;
				//oy++;
				//HenkaY++;
				if (HitCheck(i) == true) {//壁に当たっているので左か右に移動させる。ここ考えるべき
					New_y[i]++;//ここかえる
					//if (x[i] - x[i + 1] >= 0) {
					//	New_x[i]++;
					//	//HenkaX++;
					//}
					//else if (x[i] - x[i + 1] < 0) {
					//	New_x[i]--;
					//	//HenkaX--;
					//}

				}

			}

			if (New_y[i - 1] - New_y[i] >= 0
				&& pow((double)New_x[i - 1] - (double)New_x[i], 2.0) + pow((double)New_y[i - 1] - (double)New_y[i], 2.0) >= pow(IRONBALL_R, 2.0)
				) {
				oy = (int)(pow((double)New_x[i - 1] - (double)New_x[i], 2.0) + pow((double)New_y[i - 1] - (double)New_y[i], 2.0));
				if (oy >= pow(IRONBALL_R, 2.0)) {
					LenkaY -= (int)sqrt(oy) - (IRONBALL_R - 1);
				}

			}
		}
	}
	else if (LenkaY > 0) {
		static int zo[LOCK_MAX];//重力と似たような処理をするため
		for (int r = 0; r < LenkaY; r++) {

		//	New_y[0]++;
			zo[0] = 4;
			//壁にあたっていない。キャラからそこまではなれていない
			//if (HitCheck(0) == false /*&& (New_y[0] - (NewY + Map_PlayerY)) < (CHA_SIZE_Y - 8)*/) {
			//	zo[0] = 5;
			//}
			///*else if (HitCheck(0) == false) {

			//}*/
			//else {
			//	New_y[0]--;
			//	zo[0] = 0;
			//}




			//最後の方の鎖
			New_y[LOCK_MAX - 1]++;
			if (HitCheck(0) == false && (New_y[LOCK_MAX - 1] - g_IronBall.y) < 0) {
			}
			else {
				New_y[LOCK_MAX - 1]--;
			}


			//すべてに重力を加えてその後、引いていく
			for (int i = 1; i < LOCK_MAX - 1; i++) {
				New_y[i]++;
				zo[i] = 4;
			}

			//4：完璧に落ちた。2：壁に引っかかっているがまあ大丈夫。0：鎖の長さで引っかかっているので不可
			for (int i = LOCK_MAX - 2; i >= 0; i--) {
				if (New_y[i] - New_y[i + 1] > 0 && sqrt(((double)New_y[i] - New_y[i + 1]) * ((double)New_y[i] - New_y[i + 1]) + ((double)New_x[i] - New_x[i + 1]) * ((double)New_x[i] - New_x[i + 1])) >= IRONBALL_R) {
					if (zo[i] == 4) {
						New_y[i]--;
						zo[i] = 0;
					}
					else if (zo[i] == 2) {
						zo[i] = 0;
					}
				}
				else if (HitCheck(i) == true) {
					//if (zo[i] == 4) {
					New_y[i]--;
					zo[i] = 2;
					for (int j = i + 1; j <= LOCK_MAX - 2; j++) {
						if (zo[j] != 0) {
							break;
						}
						zo[j] = 2;
					}
					//}
				}
			}

			//人についてる鎖が落ちたときとおらない。（ジャンプフラグー２のときもありうる）
			for (int i = 1; i < LOCK_MAX - 1; i++) {
				if (/*zo[0] == 5*/Jump_Flg == -2 && zo[i - 1] != 2) {
					continue;
				}
				if (New_y[i] - New_y[i - 1] > 0 && sqrt(((double)New_y[i] - New_y[i - 1]) * ((double)New_y[i] - New_y[i - 1]) + ((double)New_x[i] - New_x[i - 1]) * ((double)New_x[i] - New_x[i - 1])) >= IRONBALL_R) {
					if (/*zo[0] == 5*/Jump_Flg == -2 && zo[i] == 4) {
						New_y[i]--;
						zo[i] = 2;
						continue;
					}
					if (zo[i] == 4) {
						New_y[i]--;
						zo[i] = 0;
					}
					else if (zo[i] == 2) {
						zo[i] = 0;
					}
				}
				else if (HitCheck(i) == true) {
					if (zo[i] == 4) {
						New_y[i]--;
						zo[i] = 2;
					}
				}
			}

			//2回目とおる
			for (int i = LOCK_MAX - 2; i >= 0; i--) {
				if (New_y[i] - New_y[i + 1] > 0 && sqrt(((double)New_y[i] - New_y[i + 1]) * ((double)New_y[i] - New_y[i + 1]) + ((double)New_x[i] - New_x[i + 1]) * ((double)New_x[i] - New_x[i + 1])) >= IRONBALL_R) {
					if (zo[i] == 4) {
						New_y[i]--;
						zo[i] = 0;
					}
					else if (zo[i] == 2) {
						zo[i] = 0;
					}
				}
				else if (HitCheck(i) == true) {
					if (zo[i] == 4) {
						New_y[i]--;
						zo[i] = 2;
						for (int j = i + 1; j <= LOCK_MAX - 2; j++) {
							if (zo[j] != 0) {
								break;
							}
							zo[j] = 2;
						}
					}
				}
			}

			for (int i = 1; i < LOCK_MAX - 1; i++) {
				if (New_y[LOCK_MAX - 1] > New_y[0]) {
					if (New_y[LOCK_MAX - 1] < New_y[i]) {
						if (zo[i] == 4) {
							New_y[i]--;
							zo[i] = 0;
						}
					}

				}else if (New_y[LOCK_MAX - 1] < New_y[0]) {
					if (New_y[0] < New_y[i]) {
						if (zo[i] == 4) {
							New_y[i]--;
							zo[i] = 0;
						}
					}
				}
			}
		}


		//チェック。すべてが鎖の長さで引っかかっていたらHenkaYをそのままにする。０と１を比べる。
		for (int i = 0; i < LOCK_MAX - 1; i++) {
			if (i == 0 && New_y[i] - New_y[i + 1] > 0 && sqrt(((double)New_y[i] - New_y[i + 1]) * ((double)New_y[i] - New_y[i + 1]) + ((double)New_x[i] - New_x[i + 1]) * ((double)New_x[i] - New_x[i + 1])) >= IRONBALL_R) {
				FP = 1;
				continue;
			}
			if (zo[i] == 4 || zo[i] == 5) {
				LenkaY = 0;
				break;
			}
			if (zo[i] == 2) {
				FP = 1;
				continue;
			}
			Gr = false;
		}

		//もしすべての鎖が地面についていたらHenkaYを０にする。いらんかも
		if (Gr == true) {
			LenkaY = 0;
		}

		/**/
	//	for (int i = LOCK_MAX - 1; i > 0; i--) {
	//		//変化量なしならブレイク
	//		if (LenkaY == 0) {
	//			break;
	//		}
	//		//鎖の差を図る
	////		oy = New_y[i] - New_y[i - 1];
	//		//座標移動
	//		while (LenkaY > 0) {
	//			New_y[i]++;
	//			oy++;
	//			LenkaY--;
	//			if (HitCheck(i) == true) {//壁に当たっているので左か右に移動させる
	//				New_y[i]--;//ここかえる
	//				//if (x[i] - x[i + 1] >= 0) {
	//				//	New_x[i]++;
	//				//	//HenkaX++;
	//				//}
	//				//else if (x[i] - x[i + 1] < 0) {
	//				//	New_x[i]--;
	//				//	//HenkaX--;
	//				//}

	//			}
	//		}

	//		if (oy >= IRONBALL_R) {//オーバーした長さ分を変化量に戻す
	//			LenkaY += oy - IRONBALL_R;
	//		}

	//	}
	}



	//縦移動成功
	if (LenkaY == 0) {

	}
	//移動失敗
	else {
		int ch = 0;
	//	NewY += LenkaY;
		//HenkaY += LenkaY;
		ch = -1;
	}

	LenkaY = 0;

/////////////////////////////////////////////////////////////////////////////////////////////
	//ｘ座標の変化
	//プラスなので右に移動している。
	if (LenkaX > 0) {
		int nn = 0;
		int EnY = 0;//鎖が上下に移動したなら、その１個後の鎖も上下に移動させる
		int EnY2 = 0;
		for (int i = LOCK_MAX - 1; i > 0; i--) {
			//変化量なしならブレイク
			if (LenkaX == 0) {
				break;
			}


			//１個前の鎖が上下に移動したら移動
			EnY2 = EnY;
			while (EnY > 0) {
				New_y[i]++;
				EnY--;
				if (HitCheck(i) == true) {//
					New_y[i]--;
					if (New_x[i] - New_x[i + 1] >= 0) {
						New_x[i]--;
						if (HitCheck(i) == true) {//
							New_x[i]++;
						}
					}
				}
			}
			while (EnY < 0) {
				New_y[i]--;
				EnY++;
				if (HitCheck(i) == true) {//
					New_y[i]++;
					if (New_x[i] - New_x[i + 1] >= 0) {
						New_x[i]--;
						if (HitCheck(i) == true) {//
							New_x[i]++;
						}
					}
				}
			}
			EnY = EnY2;

			//座標移動
			while (LenkaX > 0) {
				New_x[i]++;
				nn = 1;
				//	ox ++;
				LenkaX--;
				if (HitCheck(i) == true) {//壁に当たっているので上に上昇させる
					//if (WI == 0) {
					nn = 0;
					New_x[i]--;
					if (i != LOCK_MAX - 1
						&& New_y[i] - New_y[i + 1] > 0) {
						New_y[i]--;//上に上昇
						EnY--;
						if (HitCheck(i) == true) {//
							New_y[i]++;
							EnY++;
							if (New_x[i] - New_x[i + 1] >= 0) {
								New_x[i]--;
								if (HitCheck(i) == true) {//
									New_x[i]++;
								}
							}
						}
					}
					else if (i != LOCK_MAX - 1 && New_y[i] - New_y[i + 1] < 0) {
						New_y[i]++;//
						EnY++;
						if (HitCheck(i) == true) {//
							New_y[i]--;
							EnY--;
							if (New_x[i] - New_x[i + 1] >= 0) {
								New_x[i]--;
								if (HitCheck(i) == true) {//
									New_x[i]++;
								}
							}
						}
					}

					//}
					
					//	EL++;
				}
				//else if (i != 0 && New_x[i] - New_x[i - 1] >= 0 && HI == 0) {//壁にあたっていない前の鎖より右に行きすぎ

				//	if (i != 0
				//		&& New_y[i] - New_y[i - 1] > 0) {
				//		New_y[i]--;//
				//		EnY--;
				//	}
				//	else if (i != 0
				//		&& New_y[i] - New_y[i - 1] < 0) {
				//		New_y[i]++;//
				//		EnY++;
				//	}
				//	if (nn == 1) {
				//		New_x[i]--;
				//	}
				//	New_x[i]--;
				//}

				//if (RD > 0 && i != 0) {

				//	if (fabs((double)sin(radian) * (double)IRONBALL_R) - 1 > (double)New_y[i - 1] - (double)New_y[i]) {
				//		New_y[i]--;
				//		y[i]--;
				//		if (nn == 1) {
				//			New_x[i]--;
				//		}

				//	}

				//}
			}

			while (i != LOCK_MAX - 1
				&& New_x[i + 1] - New_x[i] >= 0
				&& pow((double)New_x[i + 1] - (double)New_x[i], 2.0) + pow((double)New_y[i + 1] - (double)New_y[i], 2.0) >= pow(IRONBALL_R, 2.0)
				) {
				New_x[i]++;
				nn = 1;
				//	ox ++;
	//			HenkaX--;
				if (HitCheck(i) == true) {//壁に当たっているので上に上昇させる
				//	if (WI == 0) {
					nn = 0;
					New_x[i]--;
						if (i != LOCK_MAX - 1
							&& New_y[i] - New_y[i + 1] > 0) {
							New_y[i]--;//
							EnY--;
						}
						else if (i != LOCK_MAX - 1
							&& New_y[i] - New_y[i + 1] < 0) {
							New_y[i]++;//
							EnY++;
						}
					//}
					
					//	EL++;
				}
				//else if (i != 0 && New_x[i] - New_x[i - 1] >= 0 && HI == 0) {//壁にあたっていない前の鎖より右に行きすぎ

				//	if (i != 0
				//		&& New_y[i] - New_y[i - 1] > 0) {
				//		New_y[i]--;//
				//		EnY--;
				//	}
				//	else if (i != 0
				//		&& New_y[i] - New_y[i - 1] < 0) {
				//		New_y[i]++;//
				//		EnY++;
				//	}
				//	if (nn == 1) {
				//		New_x[i]--;
				//	}
				//	New_x[i]--;
				//}



				/*if (RD > 0 && i != 0) {

					if (fabs((double)sin(radian) * (double)IRONBALL_R) - 1 > (double)New_y[i - 1] - (double)New_y[i]) {
						New_y[i]--;
						y[i]--;
						if (nn == 1) {
							New_x[i]--;
						}

					}

				}*/
			}


			if (New_x[i] - New_x[i - 1] >= 0
				&& pow((double)New_x[i] - (double)New_x[i - 1], 2.0) + pow((double)New_y[i] - (double)New_y[i - 1], 2.0) >= pow(IRONBALL_R, 2.0)
				) {
				ox = (int)(pow((double)New_x[i] - (double)New_x[i - 1], 2.0) + pow((double)New_y[i] - (double)New_y[i - 1], 2.0));
				if (ox >= pow(IRONBALL_R, 2.0)) {
					LenkaX += (int)sqrt(ox) - (IRONBALL_R - 1);
				}

			}
		}
	}
	//マイナスなので左に移動している。
	else if (LenkaX < 0) {
		int nn = 0;
		int EnY = 0;//鎖が上下に移動したなら、その１個後の鎖も上下に移動させる
		int EnY2 = 0;
		for (int i = LOCK_MAX - 1; i > 0; i--) {

			//変化量なしならブレイク
			if (LenkaX == 0) {
				break;
			}

			EnY2 = EnY;//すべてを保存
			//１個前の鎖が上下に移動したら移動
			while (EnY > 0) {
				New_y[i]++;
				EnY--;
				if (HitCheck(i) == true) {//
					New_y[i]--;
				}
			}
			while (EnY < 0) {
				New_y[i]--;
				EnY++;
				if (HitCheck(i) == true) {//
					New_y[i]++;
				}
			}
			EnY = EnY2;

			//座標移動
			while (LenkaX < 0) {
				New_x[i]--;
				nn = 1;
				//	ox++;
				LenkaX++;
				if (HitCheck(i) == true) {//壁に当たっているので上に上昇させる
					if (i != LOCK_MAX - 1
						&& New_y[i] - New_y[i + 1] > 0) {
						New_y[i]--;//
						EnY--;
					}
					else if (i != LOCK_MAX - 1
						&& New_y[i] - New_y[i + 1] < 0) {
						New_y[i]++;//
						EnY++;
					}
					New_x[i]++;
					nn = 0;
					//EL++;
				}

				//else if (i != 0 && New_x[i] - New_x[i - 1] <= 0 && HI == 0) {//壁にあたっていない前の鎖より左にいきすぎ
				//	if (i != 0
				//		&& New_y[i] - New_y[i - 1] > 0) {
				//		New_y[i]--;//
				//		EnY--;
				//	}
				//	else if (i != 0
				//		&& New_y[i] - New_y[i - 1] < 0) {
				//		New_y[i]++;//
				//		EnY++;
				//	}
				//	if (nn == 1) {
				//		New_x[i]++;
				//	}
				//	New_x[i]++;
				//}



				/*if (RD < 0 && i != 0) {

					if (fabs((double)sin(radian) * (double)IRONBALL_R) - 1 > (double)New_y[i - 1] - (double)New_y[i]
						&& (fabs((double)sin(radian) * (double)IRONBALL_R) - 1.0) * ((double)i + 1.0) >= (double)New_y[0] - (double)New_y[i]) {
						New_y[i]--;
						y[i]--;
						if (nn == 1) {
							New_x[i]++;
						}
					}


				}*/

			}

			while (i != LOCK_MAX - 1
				&& New_x[i] - New_x[i + 1] >= 0
				&& pow((double)New_x[i] - (double)New_x[i + 1], 2.0) + pow((double)New_y[i] - (double)New_y[i + 1], 2.0) >= pow(IRONBALL_R, 2.0)

				) {
				New_x[i]--;
				nn = 1;
				//	ox++;
				//HenkaX++;
				if (HitCheck(i) == true) {//壁に当たっているので上に上昇させる
					if (i != LOCK_MAX - 1
						&& New_y[i] - New_y[i + 1] > 0) {
						New_y[i]--;//
						EnY--;
					}
					else if (i != LOCK_MAX - 1
						&& New_y[i] - New_y[i + 1] < 0) {
						New_y[i]++;//
						EnY++;
					}
					New_x[i]++;
					nn = 0;
					//EL++;
				}
				//else if (i != 0 && New_x[i] - New_x[i - 1] <= 0 && HI == 0) {//壁にあたっていない前の鎖より左にいきすぎ
				//	if (i != 0
				//		&& New_y[i] - New_y[i - 1] > 0) {
				//		New_y[i]--;//
				//		EnY--;
				//	}
				//	else if (i != 0
				//		&& New_y[i] - New_y[i - 1] < 0) {
				//		New_y[i]++;//
				//		EnY++;
				//	}
				//	if (nn == 1) {
				//		New_x[i]++;
				//	}
				//	New_x[i]++;
				//}

				/*if (RD < 0 && i != 0) {

					if (fabs((double)sin(radian) * (double)IRONBALL_R) - 1 > (double)New_y[i - 1] - (double)New_y[i]
						&& (fabs((double)sin(radian) * (double)IRONBALL_R) - 1.0) * ((double)i + 1.0) >= (double)New_y[0] - (double)New_y[i]) {
						New_y[i]--;
						y[i]--;
						if (nn == 1) {
							New_x[i]++;
						}
					}


				}*/

			}


			//HenkaX += EL;
			//EL = 0;

			if (New_x[i - 1] - New_x[i] >= 0
				&& pow((double)New_x[i - 1] - (double)New_x[i], 2.0) + pow((double)New_y[i - 1] - (double)New_y[i], 2.0) >= pow(IRONBALL_R, 2.0)
				) {
				ox = (int)(pow((double)New_x[i - 1] - (double)New_x[i], 2.0) + pow((double)New_y[i - 1] - (double)New_y[i], 2.0));
				if (ox >= pow(IRONBALL_R, 2.0)) {
					LenkaX -= (int)sqrt(ox) - (IRONBALL_R - 1);
				}

			}
			/**/
			

			//ox = New_x[i - 1] - New_x[i];							//鎖の差を図る

			//while (LenkaX < 0) {
			//	New_x[i]--;
			//	ox++;
			//	LenkaX++;
			//	if (HitCheck(i) == true) {//壁に当たっているので左か右に移動させる
			//		New_x[i]++;

			//		/*いらない
			//		New_y[i]++;//ここかえる
			//		if (x[i] - x[i + 1] >= 0) {
			//			New_x[i]++;
			//			//HenkaX++;
			//		}
			//		else if (x[i] - x[i + 1] < 0) {
			//			New_x[i]--;
			//			//HenkaX--;
			//		}
			//		*/

			//	}
			//}


			////オーバーした分を戻す
			//if (ox > IRONBALL_R) {
			//	LenkaX -= ox - IRONBALL_R;
			//}
		}
	}

	//移動成功。あと当たりチェックもする
	if (LenkaX == 0) {

	}//移動失敗。人のほうを動かす。エラーするかも
	else {
		int ch = 0;
		/*NewX += LenkaX;
		HenkaX += LenkaX;*/
		ch = -1;
	}
	LenkaX = 0;
	LenkaY = 0;

/////////////////////////////////////////////////////////////////////////////////////////


	static int zo[LOCK_MAX];//重力と似たような処理をするため
	/*********************************
	*人が移動したときの変化
	*********************************/
	//y座標の変化
	//マイナス。上にいく
	if (HenkaY < 0) {
		for (int i = 0; i < LOCK_MAX - 1; i++) {
			//変化量なしならブレイク
			if (HenkaY == 0) {
				break;
			}
			//鎖の差を図る
		//	oy = /*abs(x[i] - x[i + 1])*/  New_y[i + 1] - New_y[i];
			//座標移動
			while (HenkaY < 0) {
				New_y[i]--;
				//oy++;
				HenkaY++;
				if (HitCheck(i) == true) {//壁に当たっているので左か右に移動させる。ここ考えるべき
					New_y[i]++;//ここかえる
					//if (x[i] - x[i + 1] >= 0) {
					//	New_x[i]++;
					//	//HenkaX++;
					//}
					//else if (x[i] - x[i + 1] < 0) {
					//	New_x[i]--;
					//	//HenkaX--;
					//}
					
				}
			}

			while (i != 0
				&& New_y[i] - New_y[i - 1] >= 0
				&& pow((double)New_x[i] - (double)New_x[i - 1], 2.0) + pow((double)New_y[i] - (double)New_y[i - 1], 2.0) >= pow(IRONBALL_R, 2.0)
				) {
				New_y[i]--;
				//oy++;
			//	HenkaY++;
				if (HitCheck(i) == true) {//壁に当たっているので左か右に移動させる。ここ考えるべき
					New_y[i]++;//ここかえる
					//if (x[i] - x[i + 1] >= 0) {
					//	New_x[i]++;
					//	//HenkaX++;
					//}
					//else if (x[i] - x[i + 1] < 0) {
					//	New_x[i]--;
					//	//HenkaX--;
					//}

				}

			}

			if (New_y[i + 1] - New_y[i] >= 0
				&& pow((double)New_x[i + 1] - (double)New_x[i], 2.0) + pow((double)New_y[i + 1] - (double)New_y[i], 2.0) >= pow(IRONBALL_R, 2.0)
				) {
				oy = (int)(pow((double)New_x[i + 1] - (double)New_x[i], 2.0) + pow((double)New_y[i + 1] - (double)New_y[i], 2.0));
				if (oy >= pow(IRONBALL_R, 2.0)) {
					HenkaY -= (int)sqrt(oy) - (IRONBALL_R - 1);
				}

			}

			//if (New_y[i + 1] - New_y[i] >= 0 
			//	&& New_y[i + 1] - New_y[i] >= IRONBALL_R) {//オーバーした長さ分を変化量に戻す//直線距離にする
			//	HenkaY -= New_y[i + 1] - New_y[i] - IRONBALL_R;
			//}

		}
		//if(i==LOCK_MAX - 2){
		//HenkaY = 0;

	}
	else if (HenkaY > 0) {//ひとが落ちていく場合

		
		if (RD != 0) {
			for (int i = 0; i < LOCK_MAX - 1; i++) {
				//変化量なしならブレイク
				if (HenkaY == 0) {
					break;
				}
				//鎖の差を図る
			//	oy = /*abs(x[i] - x[i + 1])*/  New_y[i + 1] - New_y[i];
				//座標移動
				while (HenkaY > 0) {
					New_y[i]++;
					//oy++;
					HenkaY--;
					if (HitCheck(i) == true) {//壁に当たっているので左か右に移動させる。ここ考えるべき
						New_y[i]--;//ここかえる
						//if (x[i] - x[i + 1] >= 0) {
						//	New_x[i]++;
						//	//HenkaX++;
						//}
						//else if (x[i] - x[i + 1] < 0) {
						//	New_x[i]--;
						//	//HenkaX--;
						//}

					}else if (i != 0
						&& New_y[i] - New_y[i - 1] >= 0
						&& pow((double)New_x[i] - (double)New_x[i - 1], 2.0) + pow((double)New_y[i] - (double)New_y[i - 1], 2.0) >= pow(IRONBALL_R, 2.0)
						) {

						New_y[i]--;//
					}
				}

				while (i != 0
					&& New_y[i - 1] - New_y[i] >= 0
					&& pow((double)New_x[i - 1] - (double)New_x[i], 2.0) + pow((double)New_y[i - 1] - (double)New_y[i], 2.0) >= pow(IRONBALL_R, 2.0)
					) {
					New_y[i]++;
					//oy++;
				//	HenkaY++;
					if (HitCheck(i) == true) {//壁に当たっているので左か右に移動させる。ここ考えるべき
						New_y[i]--;//ここかえる
						//if (x[i] - x[i + 1] >= 0) {
						//	New_x[i]++;
						//	//HenkaX++;
						//}
						//else if (x[i] - x[i + 1] < 0) {
						//	New_x[i]--;
						//	//HenkaX--;
						//}

					}

				}

				if (New_y[i] - New_y[i + 1] >= 0
					&& pow((double)New_x[i] - (double)New_x[i + 1], 2.0) + pow((double)New_y[i] - (double)New_y[i + 1], 2.0) >= pow(IRONBALL_R, 2.0)
					) {
					oy = (int)(pow((double)New_x[i] - (double)New_x[i + 1], 2.0) + pow((double)New_y[i] - (double)New_y[i + 1], 2.0));
					if (oy >= pow(IRONBALL_R, 2.0)) {
						HenkaY += (int)sqrt(oy) - (IRONBALL_R - 1);
					}

				}
			}
		}
		else {

			for (int r = 0; r < HenkaY; r++) {

				New_y[0]++;
				zo[0] = 4;
				//壁にあたっていない。キャラからそこまではなれていない
				if (HitCheck(0) == false /*&& (New_y[0] - (NewY + Map_PlayerY)) < (CHA_SIZE_Y - 8)*/) {
					zo[0] = 5;
				}
				/*else if (HitCheck(0) == false) {

				}*/
				else {
					New_y[0]--;
					zo[0] = 0;
				}




				//最後の方の鎖
				New_y[LOCK_MAX - 1]++;
				if (HitCheck(0) == false && (New_y[LOCK_MAX - 1] - g_IronBall.y) < 0) {
				}
				else {
					New_y[LOCK_MAX - 1]--;
				}


				//すべてに重力を加えてその後、引いていく
				for (int i = 1; i < LOCK_MAX - 1; i++) {
					New_y[i]++;
					zo[i] = 4;
				}

				//4：完璧に落ちた。2：壁に引っかかっているがまあ大丈夫。0：鎖の長さで引っかかっているので不可
				for (int i = LOCK_MAX - 2; i >= 0; i--) {
					if (New_y[i] - New_y[i + 1] > 0 && sqrt(((double)New_y[i] - New_y[i + 1]) * ((double)New_y[i] - New_y[i + 1]) + ((double)New_x[i] - New_x[i + 1]) * ((double)New_x[i] - New_x[i + 1])) >= IRONBALL_R) {
						if (zo[i] == 4) {
							New_y[i]--;
							zo[i] = 0;
						}
						else if (zo[i] == 2) {
							zo[i] = 0;
						}
					}
					else if (HitCheck(i) == true) {
						//if (zo[i] == 4) {
						New_y[i]--;
						zo[i] = 2;
						for (int j = i + 1; j <= LOCK_MAX - 2; j++) {
							if (zo[j] != 0) {
								break;
							}
							zo[j] = 2;
						}
						//}
					}
				}

				//人についてる鎖が落ちたときとおらない。（ジャンプフラグー２のときもありうる）
				for (int i = 1; i < LOCK_MAX - 1; i++) {
					if (/*zo[0] == 5*/Jump_Flg == -2 && zo[i - 1] != 2) {
						continue;
					}
					if (New_y[i] - New_y[i - 1] > 0 && sqrt(((double)New_y[i] - New_y[i - 1]) * ((double)New_y[i] - New_y[i - 1]) + ((double)New_x[i] - New_x[i - 1]) * ((double)New_x[i] - New_x[i - 1])) >= IRONBALL_R) {
						if (/*zo[0] == 5*/Jump_Flg == -2 && zo[i] == 4) {
							New_y[i]--;
							zo[i] = 2;
							continue;
						}
						if (zo[i] == 4) {
							New_y[i]--;
							zo[i] = 0;
						}
						else if (zo[i] == 2) {
							zo[i] = 0;
						}
					}
					else if (HitCheck(i) == true) {
						if (zo[i] == 4) {
							New_y[i]--;
							zo[i] = 2;
						}
					}
				}

				//2回目とおる
				for (int i = LOCK_MAX - 2; i >= 0; i--) {
					if (New_y[i] - New_y[i + 1] > 0 && sqrt(((double)New_y[i] - New_y[i + 1]) * ((double)New_y[i] - New_y[i + 1]) + ((double)New_x[i] - New_x[i + 1]) * ((double)New_x[i] - New_x[i + 1])) >= IRONBALL_R) {
						if (zo[i] == 4) {
							New_y[i]--;
							zo[i] = 0;
						}
						else if (zo[i] == 2) {
							zo[i] = 0;
						}
					}
					else if (HitCheck(i) == true) {
						if (zo[i] == 4) {
							New_y[i]--;
							zo[i] = 2;
							for (int j = i + 1; j <= LOCK_MAX - 2; j++) {
								if (zo[j] != 0) {
									break;
								}
								zo[j] = 2;
							}
						}
					}
				}
			}


			//チェック。すべてが鎖の長さで引っかかっていたらHenkaYをそのままにする。０と１を比べる。
			for (int i = 0; i < LOCK_MAX - 1; i++) {
				if (i == 0 && New_y[i] - New_y[i + 1] > 0 && sqrt(((double)New_y[i] - New_y[i + 1]) * ((double)New_y[i] - New_y[i + 1]) + ((double)New_x[i] - New_x[i + 1]) * ((double)New_x[i] - New_x[i + 1])) >= IRONBALL_R) {
					FP = 1;
					continue;
				}
				if (zo[i] == 4 || zo[i] == 5) {
					HenkaY = 0;
					break;
				}
				if (zo[i] == 2) {
					FP = 1;
					continue;
				}
				Gr = false;
			}

			//もしすべての鎖が地面についていたらHenkaYを０にする。いらんかも
			if (Gr == true) {
				HenkaY = 0;
			}



			//ひっぱられる
			if (HenkaY != 0 && Jump_Flg == -2/*false*/) {
				//	for(int i=LOCK_MAX)
				for (int i = 1; i < LOCK_MAX - 1; i++) {
					if (PlayerX + Map_PlayerX - New_x[i] > 0) {//鎖：人の順
						if (FP == 1) {
							//地面についているか主人公が落ちれた
							HenkaX += HenkaY;
							HenkaY = 0;
						}
						else {
							//鎖の長さがいっぱいいっぱいなのでひっぱられる
							HenkaX -= HenkaY;
							HenkaY = 0;
						}

						//	FP = 1;
							//HenkaY = 0;
						break;
					}
					else if (PlayerX + Map_PlayerX - New_x[i] < 0) {//人：鎖の順	
						if (FP == 1) {
							//地面についているか主人公が落ちれた
							HenkaX -= HenkaY;
							HenkaY = 0;
						}
						else {
							//鎖の長さがいっぱいいっぱいなのでひっぱられる
							HenkaX += HenkaY;
							HenkaY = 0;
						}
						//	HenkaX += HenkaY;
						//	FP = 1;
							//HenkaY = 0;
						break;
					}
				}
			}
		}
	}
	
	//HenkaY = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	double radian = atan2((double)NewY + (double)CHA_SIZE_Y - g_IronBall.New_y + 4.0, ((double)NewX + (double)Map_NewX + (double)CHA_SIZE_X/2) - ((double)g_IronBall.New_x + (double)MapDrawPointX - (double)MapX * (double)MAP_SIZE));
	int nn = 0;


	//ｘ座標の変化
	//プラスなので右に移動している。
	if (HenkaX > 0) {
		int EnY = 0;//鎖が上下に移動したなら、その１個後の鎖も上下に移動させる
		int EnY2 = 0;

		for (int i = 0; i < LOCK_MAX - 1; i++) {
			//変化量なしならブレイク
			if (HenkaX == 0) {
				break;
			}
			if (HI != 0 && (PlayerX + 16 + Map_PlayerX) - New_x[i] <= 0) {
				Cheat(i);
				continue;
			}
			if (FP != 0 && (PlayerX + 16 + Map_PlayerX) - (New_x[i] + HenkaX) <= 0) {
				continue;
			}
		//	if (FP == 1 && (g_IronBall.x) - New_x[i] <= 0) {
		//		FP = 0;
		//		HenkaX = 0;
		//		break;
		//	}

		//	ox = (New_x[i] - New_x[i + 1]); //+ //abs(New_y[i] - New_y[i + 1]);	//鎖の差を図る

			//１個前の鎖が上下に移動したら移動
			EnY2 = EnY;
			while (EnY > 0) {
				New_y[i]++;
				EnY--;
				if (HitCheck(i) == true) {//
					New_y[i]--;
					if (New_x[i] - New_x[i - 1] >= 0) {
						New_x[i]--;
						if (HitCheck(i) == true) {//
							New_x[i]++;
						}
					}
				}
			}
			while (EnY < 0) {
				New_y[i]--;
				EnY++;
				if (HitCheck(i) == true) {//
					New_y[i]++;
					if (New_x[i] - New_x[i - 1] >= 0) {
						New_x[i]--;
						if (HitCheck(i) == true) {//
							New_x[i]++;
						}
					}
				}
			}
			EnY = EnY2;

			//座標移動
			while (HenkaX > 0) {
				New_x[i]++;
				nn = 1;
			//	ox ++;
				HenkaX--;
				if (HitCheck(i) == true ) {//壁に当たっているので上に上昇させる
					if (WI == 0) {
						if (i != 0
							&& New_y[i] - New_y[i - 1] > 0) {
							New_y[i]--;//上に上昇
							EnY--;
							if (HitCheck(i) == true) {//
								New_y[i]++;
								EnY++;
								if (New_x[i] - New_x[i - 1] >= 0) {
									New_x[i]--;
									if (HitCheck(i) == true) {//
										New_x[i]++;
									}
								}
							}
						}
						else if (i != 0 && New_y[i] - New_y[i - 1] < 0) {
							New_y[i]++;//
							 EnY++;
							if (HitCheck(i) == true) {//
								New_y[i]--;
								EnY--;
								if (New_x[i] - New_x[i - 1] >= 0) {
									New_x[i]--;
									if (HitCheck(i) == true) {//
										New_x[i]++;
									}
								}
							}
						}
						
					}
					nn = 0;
					New_x[i]--;
				//	EL++;
				}
				else if (i != 0 && New_x[i] - New_x[i - 1] >= 0 && HI == 0) {//壁にあたっていない前の鎖より右に行きすぎ

					if (i != 0
						&& New_y[i] - New_y[i - 1] > 0) {
						New_y[i]--;//
						EnY--;
					}
					else if (i != 0
						&& New_y[i] - New_y[i - 1] < 0) {
						New_y[i]++;//
						EnY++;
					}
					if (nn == 1) {
						New_x[i]--;
					}
					New_x[i]--;
				}

				if (RD > 0 && i != 0) {
					
					if (fabs((double)sin(radian) * (double)IRONBALL_R) -1 > (double)New_y[i - 1] - (double)New_y[i]) {
						New_y[i]--;
						y[i]--;
						if (nn == 1) {
							New_x[i]--;
						}
						
					}
					
				}
			}
			
			while (i != 0
				&& New_x[i - 1] - New_x[i] >= 0
				&& pow((double)New_x[i - 1] - (double)New_x[i], 2.0) + pow((double)New_y[i - 1] - (double)New_y[i], 2.0) >= pow(IRONBALL_R, 2.0)
				) {
				New_x[i]++;
				nn = 1;
				//	ox ++;
	//			HenkaX--;
				if (HitCheck(i) == true) {//壁に当たっているので上に上昇させる
					if (WI == 0) {
						if (i != 0
							&& New_y[i] - New_y[i - 1] > 0) {
							New_y[i]--;//
							EnY--;
						}
						else if (i != 0
							&& New_y[i] - New_y[i - 1] < 0) {
							New_y[i]++;//
							EnY++;
						}
					}
					nn = 0;
					New_x[i]--;
					//	EL++;
				}
				else if (i != 0 && New_x[i] - New_x[i - 1] >= 0 && HI == 0) {//壁にあたっていない前の鎖より右に行きすぎ

					if (i != 0
						&& New_y[i] - New_y[i - 1] > 0) {
						New_y[i]--;//
						EnY--;
					}
					else if (i != 0
						&& New_y[i] - New_y[i - 1] < 0) {
						New_y[i]++;//
						EnY++;
					}
					if (nn == 1) {
						New_x[i]--;
					}
					New_x[i]--;
				}
				


				if (RD > 0 && i != 0) {

					if (fabs((double)sin(radian) * (double)IRONBALL_R) - 1 > (double)New_y[i - 1] - (double)New_y[i]) {
						New_y[i]--;
						y[i]--;
						if (nn == 1) {
							New_x[i]--;
						}

					}

				}
			}
			

			//HenkaX += EL;			//
			//EL = 0;

			//if (ox >= IRONBALL_R) {//オーバーした長さ分を変化量に戻す

			//		HenkaX += ox - IRONBALL_R;
			//	
			//}
			//(New_x[i] - New_x[i + 1])
			if (New_x[i] - New_x[i + 1] >= 0
					&& pow((double)New_x[i] - (double)New_x[i + 1], 2.0) + pow((double)New_y[i] - (double)New_y[i + 1], 2.0) >= pow(IRONBALL_R, 2.0)
				) {
				ox = (int)(pow((double)New_x[i] - (double)New_x[i + 1], 2.0) + pow((double)New_y[i] - (double)New_y[i + 1], 2.0));
				if (ox >= pow(IRONBALL_R, 2.0)) {
					HenkaX += (int)sqrt(ox) - (IRONBALL_R - 1);
				}

			}
			if (WI > 0 && i < LOCK_MAX - 2) {
				
				if (New_y[i+1] - New_y[i + 2] > 5) {
					HenkaX += 2;
				}
				else {
					WI = 0;
				}
			}
			
		}
		/*if (RD > 0) {
			RD = 0;
		}*/
	}
	//マイナスなので左に移動している。
	else if (HenkaX < 0) {
	int EnY = 0;//鎖が上下に移動したなら、その１個後の鎖も上下に移動させる
	int EnY2 = 0;//
		for (int i = 0; i < LOCK_MAX - 1; i++) {
			//変化量なしならブレイク
			if (HenkaX == 0) {
				break;
			}
			if (HI != 0 && (PlayerX + 16 + Map_PlayerX) - New_x[i] >= 0) {
				Cheat(i);
				continue;
			}
			if (FP != 0 && (PlayerX + 16 + Map_PlayerX) - (New_x[i] + HenkaX) >= 0) {
				continue;
			}
		//	if (FP != 0 && (g_IronBall.New_x) - New_x[i] >= 0) {
	//			FP = 0;
	//			continue;
	//		}

		//	ox = New_x[i + 1] - New_x[i];// + abs(New_y[i] - New_y[i + 1]);		//鎖の差を図る


			EnY2 = EnY;//すべてを保存
			//１個前の鎖が上下に移動したら移動
			while (EnY > 0) {
				New_y[i]++;
				EnY--;
				if (HitCheck(i) == true) {//
					New_y[i]--;
				}
			}
			while (EnY < 0) {
				New_y[i]--;
				EnY++;
				if (HitCheck(i) == true) {//
					New_y[i]++;
				}
			}
			EnY = EnY2;

			//座標移動
			while (HenkaX < 0) {
				New_x[i]--;
				nn = 1;
			//	ox++;
				HenkaX++;
				if (HitCheck(i) == true ) {//壁に当たっているので上に上昇させる
					if (i != 0
						&& New_y[i] - New_y[i - 1] > 0) {
						New_y[i]--;//
						EnY--;
					}
					else if (i != 0
						&& New_y[i] - New_y[i - 1] < 0) {
						New_y[i]++;//
						EnY++;
					}
					New_x[i]++;
					nn = 0;
					//EL++;
				}

				else if (i != 0 && New_x[i] - New_x[i - 1] <= 0 && HI == 0) {//壁にあたっていない前の鎖より左にいきすぎ
					if (i != 0
						&& New_y[i] - New_y[i - 1] > 0) {
						New_y[i]--;//
						EnY--;
					}
					else if (i != 0
						&& New_y[i] - New_y[i - 1] < 0) {
						New_y[i]++;//
						EnY++;
					}
					if (nn == 1) {
						New_x[i]++;
					}
					New_x[i]++;
				}

				

				if (RD < 0 && i != 0) {
					
					if (fabs((double)sin(radian) * (double)IRONBALL_R)-1 > (double)New_y[i - 1] - (double)New_y[i]
						&& (fabs((double)sin(radian) * (double)IRONBALL_R) - 1.0) * ((double)i + 1.0) >= (double)New_y[0] - (double)New_y[i]) {
						New_y[i]--;
						y[i]--;
						if (nn == 1) {
							New_x[i]++;
						}
					}
					
					
				}
				
			}

			while (i != 0
				&& New_x[i] - New_x[i - 1] >= 0
				&& pow((double)New_x[i] - (double)New_x[i - 1], 2.0) + pow((double)New_y[i] - (double)New_y[i - 1], 2.0) >= pow(IRONBALL_R, 2.0)

				) {
				New_x[i]--;
				nn = 1;
				//	ox++;
				//HenkaX++;
				if (HitCheck(i) == true) {//壁に当たっているので上に上昇させる
					if (i != 0
						&& New_y[i] - New_y[i - 1] > 0) {
						New_y[i]--;//
						EnY--;
					}
					else if (i != 0
						&& New_y[i] - New_y[i - 1] < 0) {
						New_y[i]++;//
						EnY++;
					}
					New_x[i]++;
					nn = 0;
					//EL++;
				}
				else if (i != 0 && New_x[i] - New_x[i - 1] <= 0 && HI == 0) {//壁にあたっていない前の鎖より左にいきすぎ
					if (i != 0
						&& New_y[i] - New_y[i - 1] > 0) {
						New_y[i]--;//
						EnY--;
					}
					else if (i != 0
						&& New_y[i] - New_y[i - 1] < 0) {
						New_y[i]++;//
						EnY++;
					}
					if (nn == 1) {
						New_x[i]++;
					}
					New_x[i]++;
				}

				if (RD < 0 && i != 0) {

					if (fabs((double)sin(radian) * (double)IRONBALL_R) - 1 > (double)New_y[i - 1] - (double)New_y[i]
						&& (fabs((double)sin(radian) * (double)IRONBALL_R) - 1.0) * ((double)i + 1.0) >= (double)New_y[0] - (double)New_y[i]) {
						New_y[i]--;
						y[i]--;
						if (nn == 1) {
							New_x[i]++;
						}
					}


				}
				
			}
			

			//HenkaX += EL;
			//EL = 0;

			if (New_x[i + 1] - New_x[i] >= 0
				&& pow((double)New_x[i + 1] - (double)New_x[i], 2.0) + pow((double)New_y[i + 1] - (double)New_y[i], 2.0) >= pow(IRONBALL_R, 2.0)
				) {
				ox = (int)(pow((double)New_x[i + 1] - (double)New_x[i], 2.0) + pow((double)New_y[i + 1] - (double)New_y[i], 2.0));
				if (ox >= pow(IRONBALL_R, 2.0)) {
					HenkaX -= (int)sqrt(ox) - (IRONBALL_R - 1);
				}
				
			}

			if (WI < 0 && i < LOCK_MAX - 2) {
				//HenkaX = 0;
				if (New_y[i+1] - New_y[i + 2] > 5) {
					HenkaX -= 2;
				}
				else {
					WI = 0;
				}
				
				
			}
		}
		
	}
	//if (HenkaY != 0) {
	//	x[0]++;
	//	x[0]--;
	//	for (int i = 0; i < LOCK_MAX - 1; i++) {
	//		//	New_x[i] += (-HenkaX);
	//		New_x[i] = x[i];
	//		New_y[i] = y[i];
	//	}
	//}
	if (HenkaX == 0 && HenkaY == 0) {
		for (int i = 0; i < LOCK_MAX - 1; i++) {
			if (New_x[i + 1] - New_x[i] >= 0
				&& pow((double)New_x[i + 1] - (double)New_x[i], 2.0) + pow((double)New_y[i + 1] - (double)New_y[i], 2.0) > pow(IRONBALL_R, 2.0)) {
				HenkaX = -1;
				break;
			}
			if (New_x[i] - New_x[i + 1] >= 0
				&& pow((double)New_x[i] - (double)New_x[i + 1], 2.0) + pow((double)New_y[i] - (double)New_y[i + 1], 2.0) > pow(IRONBALL_R, 2.0)) {
				HenkaX = 1;
				break;
			}
		}
	}

	//移動成功。あと当たりチェックもする
	if (HenkaX == 0) {
		
	}//移動失敗。
	else if(HI == 0){
		for (int i = 0; i < LOCK_MAX - 1; i++) {
		//	New_x[i] += (-HenkaX);
			New_x[i] = x[i];
			New_y[i] = y[i];
		}
	}
	
}

//移動処理
void partsInfo::Move() {
	

	//if (!ThrowFlg)y += 4;
	New_x = x;
	New_y = y;
	if (!HitCheck() && !ThrowFlg && !HoldFlg) {
		y += 4;
		Locka.LenkaY += 4;
	}
	

	if (!HoldFlg && !ThrowFlg) {
		HitBectl();
		if (DebugMode) {
			DrawFormatString(100, 100, 0x000000, "true");
		}
	}
	
	
	//x = ((PlayerX / MAP_SIZE) + 4) * MAP_SIZE;
	if (HoldFlg) {
		
	}
	//プレイヤーが鉄球を投げるか持つか
	IronHoldOrThrow();
	Throw();
	
	

}


void Lock::Move(int eeee) {
	
	int eee = 0;
	for (int i = 0; i < LOCK_MAX - 1; i++) {
		if (New_x[i + 1] - New_x[i] >= 0
			&& pow((double)New_x[i + 1] - (double)New_x[i], 2.0) + pow((double)New_y[i + 1] - (double)New_y[i], 2.0) > pow(IRONBALL_R, 2.0)) {
			eee = -1;
			break;
		}
		if (New_x[i] - New_x[i + 1] >= 0
			&& pow((double)New_x[i] - (double)New_x[i + 1], 2.0) + pow((double)New_y[i] - (double)New_y[i + 1], 2.0) > pow(IRONBALL_R, 2.0)) {
			eee = 1;
			break;
		}
	}

	for (int i = 0; i < LOCK_MAX; i++) {
		x[i] = New_x[i];
		y[i] = New_y[i];
	}

	
}


//投げる処理
void partsInfo::Throw(){			//鉄球が飛んでいく処理
	const int InitPow = -20;
	static int Pow = InitPow;
	static int move = 1;

	//if (g_NowKey & PAD_INPUT_UP) ThrowFlg = true;

	if (HoldFlg) {
		IronHold(&x,&y);
	}

	if (ThrowFlg && Bectl == 0) {			//投げられている処理右
		New_x = x;
		New_y = y;
		Pow++;
		New_x += 6;
		New_y += Pow;
		if (HitCheck()) {
		//	ThrowFlg = false;
			
			if (Pow < 0) {
				Pow = 0;
			}
			else {
				//下降だけさせても大丈夫ならする
				New_x = x;
				if (!HitCheck()) {
					//x = New_x;
					y = New_y;
				}
			}
			
		}
		else {
			x = New_x;
			y = New_y;
			Locka.LenkaX += 6;
			Locka.LenkaY += Pow;
		}
	}else if(ThrowFlg && Bectl == 1){		//投げられている処理左
		New_x = x;
		New_y = y;
		Pow++;
		New_x -= 6;
		New_y += Pow;
		if (HitCheck()) {
			//	ThrowFlg = false;

			if (Pow < 0) {
				Pow = 0;
			}
			else {
				//下降だけさせても大丈夫ならする
				New_x = x;
				if (!HitCheck()) {
					x = New_x;
					y = New_y;
				}
			}
			
			
		}
		else {
			x = New_x;
			y = New_y;
			Locka.LenkaX -= 6;
			Locka.LenkaY += Pow;
		}
	}
	else { Pow = InitPow; }

	New_x = x;
	New_y = y;//最終的なリセット
}


void Lock::Throw() {

}



//当たり判定
bool partsInfo::HitCheck() {		//地面との当たり判定　当たっていればtrue 当たっていなければfalse。動いた後の座標をみるところ
	 int i=0, j=0, k=0, l=0, w=0, z=0;//ローカル変数
	//鉄球の位置（左）がマップをまたいでいる
	while ((New_x - IRONBALL_R)/MAP_SIZE - k >= WIDTH) {
		k += WIDTH;
		l += HEIGHT;
	}
	//鉄球の位置（右）がマップをまたいでいる
	if ((New_x + IRONBALL_R)/MAP_SIZE - k>= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//真ん中の位置がマップをまたいでいる
	if (New_x/MAP_SIZE - k >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}
	
	//投げているときに壁にあたったら投げるのをやめる。ThrowFlgを変えるところ
	if (g_MapChip[(New_y + IRONBALL_R) / MAP_SIZE + l + z][New_x / MAP_SIZE - k - w] != 1		//中心の真下
		//|| g_MapChip[(New_y - IRONBALL_R + 10) / MAP_SIZE + l][(New_x - IRONBALL_R) / MAP_SIZE - k] != 1	//左上 + 10
		//|| g_MapChip[(New_y - IRONBALL_R + 10) / MAP_SIZE + l + j][(New_x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//右上 + 10
		|| g_MapChip[(New_y ) / MAP_SIZE + l][(New_x - IRONBALL_R) / MAP_SIZE - k] != 1	//左真ん中
		|| g_MapChip[(New_y ) / MAP_SIZE + l + j][(New_x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//右真ん中
		|| g_MapChip[(New_y + IRONBALL_R) / MAP_SIZE + l][(New_x - IRONBALL_R) / MAP_SIZE - k] != 1	//左下
		|| g_MapChip[(New_y + IRONBALL_R) / MAP_SIZE + l + j][(New_x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//右下
		) {
		
		ThrowFlg = false;
	}


	if(g_MapChip[ (New_y - IRONBALL_R  ) / MAP_SIZE + l + z][New_x  / MAP_SIZE - k - w] != 1		//中心の真上
		||g_MapChip[(New_y + IRONBALL_R) / MAP_SIZE + l + z][New_x / MAP_SIZE - k - w] != 1		//中心の真下
		|| g_MapChip[ (New_y - IRONBALL_R ) / MAP_SIZE + l][(New_x - IRONBALL_R ) / MAP_SIZE - k] != 1	//左上
		|| g_MapChip[ (New_y - IRONBALL_R ) / MAP_SIZE + l + j][(New_x + IRONBALL_R ) / MAP_SIZE - k - i] != 1	//右上
		|| g_MapChip[ (New_y + IRONBALL_R ) / MAP_SIZE + l][(New_x - IRONBALL_R ) / MAP_SIZE - k] != 1	//左下
		|| g_MapChip[ (New_y + IRONBALL_R ) / MAP_SIZE + l + j][(New_x + IRONBALL_R ) / MAP_SIZE - k - i] != 1	//右下
		){	
		return true;
	}

	return false;
}


//右左どちらにあたっているかどうか。現在の座標をみるところ
void  partsInfo::HitBectl() {
	int i = 0, j = 0, k = 0, l = 0, w = 0, z = 0;//ローカル変数
	//鉄球の位置（左）がマップをまたいでいる
	while ((x - IRONBALL_R) / MAP_SIZE - k >= WIDTH) {
		k += WIDTH;
		l += HEIGHT;
	}
	//鉄球の位置（右）がマップをまたいでいる
	if ((x + IRONBALL_R) / MAP_SIZE - k >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//真ん中の位置がマップをまたいでいる
	if (x / MAP_SIZE - k >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}


	//現在の上座標をみる
	if (g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l][(x - IRONBALL_R) / MAP_SIZE - k] != 1	//左上
		|| g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l + j][(x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//右上
		|| g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l + z][x / MAP_SIZE - k - w] != 1)		//中心の真上
	{
		//ｙなのでマップで一個下をみても大丈夫なはず。そこが壁じゃなければｙ座標をそこに移す
		if (g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l + 1][(x - IRONBALL_R) / MAP_SIZE - k] != 1	//左上
			|| g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l + j + 1][(x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//右上
			|| g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l + z + 1][x / MAP_SIZE - k - w] != 1)
		{
		}
		else {
			y = ((y - IRONBALL_R) / MAP_SIZE + 1) * MAP_SIZE + IRONBALL_R + 1;
		}
	}




	//現在の左座標が壁に埋もれているならば座標を一個右にする
	if (g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l][(x - IRONBALL_R) / MAP_SIZE - k] != 1	//左上
		|| g_MapChip[(y + IRONBALL_R - 4) / MAP_SIZE + l ][(x - IRONBALL_R) / MAP_SIZE - k] != 1	//左下-4
		) {
		Locka.LenkaX +=  (((x - IRONBALL_R) / MAP_SIZE + 1) * MAP_SIZE + IRONBALL_R) - x;
		x = ((x - IRONBALL_R) / MAP_SIZE + 1) * MAP_SIZE + IRONBALL_R;
		Locka.MoveCheck();
		Locka.Move(4);
		//return;
	}
	//現在の右座標が壁に埋もれているならば座標を一個左にする
	if (g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l + j][(x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//右上
		|| g_MapChip[(y + IRONBALL_R - 4) / MAP_SIZE + l + j][(x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//右下-4
		) {
		Locka.LenkaX +=  (((x + IRONBALL_R) / MAP_SIZE) * MAP_SIZE - IRONBALL_R - 1) - x;
		x = ((x + IRONBALL_R) / MAP_SIZE) * MAP_SIZE - IRONBALL_R - 1;
		Locka.MoveCheck();
		Locka.Move(5);
		//return;
	}

	//New_x = x;
	//New_y = y;//最終的なリセットこれでnew_Xが触れる
	return ;
}


int Lock::HitCheck(int num) {
	int i = 0, j = 0, k = 0, l = 0, w = 0, z = 0;//ローカル変数

	//鎖の位置（左）がマップをまたいでいる
	while ((New_x[num] - ro) / MAP_SIZE - k >= WIDTH) {
		k += WIDTH;
		l += HEIGHT;
	}
	//鉄球の位置（右）がマップをまたいでいる
	if ((New_x[num] + ro) / MAP_SIZE - k >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//真ん中の位置がマップをまたいでいる
	if (New_x[num] / MAP_SIZE - k >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}


	if (g_MapChip[(New_y[num] - ro) / MAP_SIZE + l + z][New_x[num] / MAP_SIZE - k - w] != 1		//中心の真上
		|| g_MapChip[(New_y[num] + ro) / MAP_SIZE + l + z][New_x[num] / MAP_SIZE - k - w] != 1		//中心の真下
		|| g_MapChip[(New_y[num] - ro) / MAP_SIZE + l][(New_x[num] - ro) / MAP_SIZE - k] != 1	//左上
		|| g_MapChip[(New_y[num] - ro) / MAP_SIZE + l + j][(New_x[num] + ro) / MAP_SIZE - k - i] != 1	//右上
		|| g_MapChip[(New_y[num] + ro) / MAP_SIZE + l][(New_x[num] - ro) / MAP_SIZE - k] != 1	//左下
		|| g_MapChip[(New_y[num] + ro) / MAP_SIZE + l + j][(New_x[num] + ro) / MAP_SIZE - k - i] != 1	//右下
		) {
		return true;
	}

	return false;

	//return 0;
}


void Lock::Gravity() {
	static int zo[LOCK_MAX];//
	

	for (int i = 0; i < LOCK_MAX; i++) {
		x[i] = New_x[i];
		y[i] = New_y[i];
	}

	if (!g_IronBall.ThrowFlg && Jump_Flg == 0 && RD == 0 && !g_IronBall.HoldFlg) {//鉄球を投げてないとき、持っていないとき重力を鎖に加える.
													//それと鎖の長さの制約も加えるべき
		New_y[0] += 4;
		if (HitCheck(0) == false && (y[0] - (PlayerY + Map_PlayerY)) < (CHA_SIZE_Y - 8)) {
			y[0] += 4;
		}
		New_y[0] = y[0];

		//最後の方の鎖
		New_y[LOCK_MAX - 1] += 4;
		if (HitCheck(0) == false && (y[LOCK_MAX - 1] - g_IronBall.y) < 0) {
			y[LOCK_MAX - 1] += 4;
		}
		New_y[LOCK_MAX - 1] = y[LOCK_MAX - 1];

		//すべてに重力を加えてその後、引いていく
		for (int i = 1; i < LOCK_MAX - 1; i++) {
			New_y[i] += 4;
			zo[i] = 4;
			if(Wall[i] >= 1){
				Wall[i]--;
			}
		}

		//もし１個左右が壁なら//直線距離じゃなくする
		for (int i = 1; i < LOCK_MAX - 1; i++) {
			New_y[i] += 2;

			New_x[i] += 2;
			if (zo[i] == 4 && HitCheck(i) == true ) {
				/*New_y[i] -= 4;
				zo[i] = 0;*/
				Wall[i] = 0;
			}
			New_x[i] -= 4;
			if (zo[i] == 4 && HitCheck(i) == true) {
				/*New_y[i] -= 4;
				zo[i] = 0;*/
				Wall[i] = 0;
			}
			New_x[i] += 2;

			New_y[i] -= 2;
		}


		for (int i = LOCK_MAX - 2; i >= 1; i--) {
			if (Wall[i] == 0) {//壁に当たっていないので一応ななめの直線距離を調べる。//２乗の中身が＋であるここでは高さｙが重要
				if (HitCheck(i) == true 
					|| (New_y[i] - New_y[i + 1] > 16  &&  pow((double)New_y[i] - (double)New_y[i + 1] , 2.0) + pow((double)New_x[i] - (double)New_x[i + 1], 2.0) >= pow((double)IRONBALL_R, 2.0))
					) {
					if (zo[i] == 4) {
						New_y[i] -= 4;
						zo[i] = 0;
					}
				}
			}
			else if (Wall[i] >= 1) {//鎖が壁に当たっているので縦＋横
				if (HitCheck(i) == true || (New_y[i] - New_y[i + 1]) + abs(New_x[i] - New_x[i + 1])  >= IRONBALL_R) {
					if (zo[i] == 4) {
						New_y[i] -= 4;
						zo[i] = 0;
					}
				}
			}
		}
		
		for (int i = 1; i < LOCK_MAX - 1; i++) {
			if (Wall[i] == 0) {
				if (HitCheck(i) == true 
					|| (New_y[i] - New_y[i - 1] > 16 && pow((double)New_y[i] - (double)New_y[i - 1], 2.0) + pow((double)New_x[i] - (double)New_x[i - 1], 2.0) >= pow((double)IRONBALL_R , 2.0)))
				{
					if (zo[i] == 4) {
						New_y[i] -= 4;
						zo[i] = 0;
					}
				}
			}
			else if (Wall[i] >= 1) {
				if (HitCheck(i) == true || New_y[i] - New_y[i - 1] + abs(New_y[i] - New_y[i - 1]) >= IRONBALL_R) {
					if (zo[i] == 4) {
						New_y[i] -= 4;
						zo[i] = 0;
					}
				}
			}
		}

		//２回目とおる
		for (int i = LOCK_MAX - 2; i >= 1; i--) {
			if (Wall[i] == 0) {//壁に当たっていないので一応ななめの直線距離を調べる。//２乗の中身が＋であるここでは高さｙが重要
				if (HitCheck(i) == true
					|| (New_y[i] - New_y[i + 1] > 0 && pow((double)New_y[i] - (double)New_y[i + 1], 2.0) + pow((double)New_x[i] - (double)New_x[i + 1], 2.0) >= pow((double)IRONBALL_R, 2.0))
					) {
					if (zo[i] == 4) {
						New_y[i] -= 4;
						zo[i] = 0;
					}
				}
			}
			else if (Wall[i] >= 1) {//鎖が壁に当たっているので縦＋横
				if (HitCheck(i) == true || (New_y[i] - New_y[i + 1]) + abs(New_x[i] - New_x[i + 1]) >= IRONBALL_R) {
					if (zo[i] == 4) {
						New_y[i] -= 4;
						zo[i] = 0;
					}
				}
			}
		}

		for (int i = 1; i < LOCK_MAX - 1; i++) {
			if (Wall[i] == 0) {
				if (HitCheck(i) == true
					|| (New_y[i] - New_y[i - 1] > 0 && pow((double)New_y[i] - (double)New_y[i - 1], 2.0) + pow((double)New_x[i] - (double)New_x[i - 1], 2.0) >= pow((double)IRONBALL_R, 2.0)))
				{
					if (zo[i] == 4) {
						New_y[i] -= 4;
						zo[i] = 0;
					}
				}
			}
			else if (Wall[i] >= 1) {
				if (HitCheck(i) == true || New_y[i] - New_y[i - 1] + abs(New_y[i] - New_y[i - 1]) >= IRONBALL_R) {
					if (zo[i] == 4) {
						New_y[i] -= 4;
						zo[i] = 0;
					}
				}
			}
		}

	}

	for (int i = 0; i < LOCK_MAX - 1; i++) {
		int tu = 0;
		if (New_x[i + 1] - New_x[i] >= 0
			&& pow((double)New_x[i + 1] - (double)New_x[i], 2.0) + pow((double)New_y[i + 1] - (double)New_y[i], 2.0) > pow(IRONBALL_R, 2.0)) {
			tu = -1;
			break;
		}
		if (New_x[i] - New_x[i + 1] >= 0
			&& pow((double)New_x[i] - (double)New_x[i + 1], 2.0) + pow((double)New_y[i] - (double)New_y[i + 1], 2.0) > pow(IRONBALL_R, 2.0)) {
		tu = 1;
			break;
		}
	}

	for (int i = 0; i < LOCK_MAX; i++) {
		x[i] = New_x[i];
		y[i] = New_y[i];
	}
}


void Lock::Cheat(int jn) {
	for (int i = 0; i < jn ; i++) {
		if (i == 0) {
			x[i] = PlayerX + Map_PlayerX + 16;
			y[i] = PlayerY + 58;
			New_x[i] = PlayerX + Map_PlayerX + 16;
			New_y[i] = PlayerY + 58;
		}
		else if (i == LOCK_MAX - 1) {
			x[i] = PlayerX + Map_PlayerX + 16;
			y[i] = g_IronBall.y;
			New_x[i] = PlayerX + Map_PlayerX + 16;
			New_y[i] = g_IronBall.y;
		}
		else {
			x[i] = PlayerX + Map_PlayerX + 16;
			y[i] = PlayerY + 58 - ((PlayerY + 58) - g_IronBall.y)/(LOCK_MAX - 1)* i;
			New_x[i] = PlayerX + Map_PlayerX + 16;
			New_y[i] = PlayerY + 58 - ((PlayerY + 58) - g_IronBall.y) / (LOCK_MAX - 1) * i;
		}
	}
}


/***********************************************
*		鉄球の関数の定義
************************************************/
void IronBallDisp() {
	g_IronBall.Disp();
	Locka.Disp();
}



void IronBallMove() {
	static bool initflg = true;

	if (initflg) {
		g_IronBall.Init();
		Locka.Init();
		initflg = false;
	}

	Locka.Gravity();
	g_IronBall.Move();
	Locka.Move(6);
	if (g_IronBall.HoldFlg == true) {
		Locka.Cheat(LOCK_MAX);
	}
}