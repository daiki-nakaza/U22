#include "DxLib.h"
#include "Math.h"

#include "Player.h"
#include "Map.h"
#include "PlayerAndIronBall.h"
#include "Enemy.h"


//プレイヤーの位置
int PlayerX, PlayerY;              //0～画面半分まで。（プレイヤー位置）
int Map_PlayerX, Map_PlayerY;      //マップ全体のスクロール位置（マップ位置）
int NewX, NewY;	// 移動する前のプレイヤーの位置を保存する変数
int Map_NewX, Map_NewY;	// 移動する前のプレイヤーの位置を保存する変数
int Jump_Flg;
int y_temp;
int y_prev;
int Down_flg;//しゃがみのフラグ

int Bectl;
int Attack;

int Player_Pic[4];
int Player_Pic_R[4];

int Player_Pic_Attack[6];
int Player_Pic_Attack_R[6];

int Player_Pic_Down;
int Player_Pic_Down_R;

int Player_Pic_Hold[4];//プレイヤーが鉄球をもって移動する画像
int Player_Pic_Hold_R[4];//逆プレイヤーが鉄球をもって移動する画像

void PlayerInit() {

	// プレイヤーの初期位置をセット
	PlayerX = 200;
	PlayerY = 200;
	Map_PlayerX = 0;
	Map_PlayerY = 0;

	Jump_Flg = false;

	Bectl = 0;//０は右向き、１は左向き
	Attack = 0;//０は攻撃可能
	Down_flg = 0;//０はしゃがんでない１はしゃがんでいる

}

void PlayerMove() {

	int i = 0, j = 0, w = 0, z = 0;//ローカルなので気にしないでください!あたり判定用の補正値
	int flg = 0;//ローカル変数で、敵との当たり判定につかっています

	//プレイヤー重力
	PlayerGravity();
	

	// 移動する前のプレイヤーの位置を保存
	NewX = PlayerX;
	NewY = PlayerY;
	Map_NewX = Map_PlayerX;
	Map_NewY = Map_PlayerY;

	//しゃがみのフラグを毎回０にする
	Down_flg = 0;
	

	// キー入力に応じてプレイヤーの座標を移動
	if (g_NowKey & PAD_INPUT_LEFT) { 
		NewX -= 2;
		if (Attack < 10 && g_IronBall.ThrowFlg == false) {
			Bectl = 1;
		}
	}
	if (g_NowKey & PAD_INPUT_RIGHT) {
		NewX += 2; 
		if (Attack < 10 && g_IronBall.ThrowFlg == false) {
			Bectl = 0;
		}
	}
	if (g_NowKey & PAD_INPUT_UP && g_IronBall.HoldFlg == false) {
		if (Jump_Flg == 0) {
			y_prev = PlayerY;
			NewY -= 16;
			Jump_Flg = 1;
		}
		else if (Jump_Flg == 3) {
			Jump_Flg = 1;
		}
	}
	if (g_NowKey & PAD_INPUT_DOWN && Jump_Flg == 0 && g_IronBall.HoldFlg == false) {
		PlayerY += 16;
		NewY += 16; 
		Down_flg = 1;
	}

	
	
	

	DrawFormatString(0, 0, 0xffffff,"%d", g_Enemy[0].Life);
		

	if (NewX > 500) {
		NewX = 500;
		Map_NewX += 2;
	}
	if (NewX < 64) {
		NewX = 64;
		if (Map_NewX > 0) {
			Map_NewX -= 2;
		}

	}

	// スライド用の０から３１までの値
	MapDrawPointX = -(Map_NewX % MAP_SIZE);
	MapDrawPointY = -(Map_NewY % MAP_SIZE);

	MapX = (Map_NewX) / MAP_SIZE;
	MapY = (Map_NewY) / MAP_SIZE;

	MapChipNumX = 0;
	MapChipNumY = 0;
	for (int k = 1; MapX + ((NewX+ (Map_NewX % MAP_SIZE)) / MAP_SIZE)  >= WIDTH * k; k++) {
		MapChipNumX += WIDTH;
		MapChipNumY += HEIGHT;
	}

	//落下した場合
	if (MapY + ((NewY + (Map_NewX % MAP_SIZE) + CHA_SIZE_Y-1) / MAP_SIZE) + MapChipNumY >= HEIGHT) {
	}

	//プレイヤー位置がマップをまたいでいる
	if (MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X-1) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//真ん中の位置がマップをまたいでいる
	if (MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}

	//敵キャラが移動する場所にいたら戻す
	for (int a = 0; a < ENEMY_MAX; a++) {
		if (g_Enemy[a].Life > 0) {
			if (g_Enemy[a].x - NewX - Map_NewX < CHA_SIZE_X 
				&& g_Enemy[a].y - NewY - Map_NewY < CHA_SIZE_Y - 1 
				&& g_Enemy[a].x - NewX - Map_NewX > 0 - g_Enemy[a].w
				&& g_Enemy[a].y - NewY - Map_NewY > 0 - g_Enemy[a].h) {
				flg = 1;
			}
		}
	}


	// 進入不可能なマップだった場合は移動できない//鉄球がある
	if (g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1												//左上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1								//左下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1						//左真ん中
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] != 1						//右上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] != 1			//右下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] != 1			//右真ん中
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] != 1						//真ん中上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] != 1		//真ん中下
		||		(g_IronBall.x - NewX - Map_NewX < CHA_SIZE_X + IRONBALL_R
			  && g_IronBall.y - NewY - Map_NewY < CHA_SIZE_Y - 1 + IRONBALL_R
			  && g_IronBall.x - NewX - Map_NewX > 0 - IRONBALL_R
			  && g_IronBall.y - NewY - Map_NewY > 0 - IRONBALL_R
			  && g_IronBall.HoldFlg == false)
		|| (pow((double)g_IronBall.x - (double)NewX - (double)Map_NewX - (double)CHA_SIZE_X / 2.0, 2.0) + pow((double)g_IronBall.y - (double)NewY - (double)Map_NewY - (double)CHA_SIZE_Y / 2.0, 2.0) > pow((double)MAP_SIZE * 9.0, 2.0))
		|| flg == 1
		)
	{
		
		MapDrawPointX = -(Map_PlayerX % MAP_SIZE);
		MapDrawPointY = -(Map_PlayerY % MAP_SIZE);

		MapX = (Map_PlayerX) / MAP_SIZE;
		MapY = (Map_PlayerY) / MAP_SIZE;

		MapChipNumX = 0;
		MapChipNumY = 0;
		for (int k = 1; MapX + (PlayerX / MAP_SIZE) >= WIDTH * k; k++) {
			MapChipNumX += WIDTH;
			MapChipNumY += HEIGHT;
		}
		
	}
	else {//移動できる
		
		PlayerX = NewX;
		PlayerY = NewY;
		Map_PlayerX = Map_NewX;
		Map_PlayerY = Map_NewY;
	}
	
	
}

void PlayerDisp() {
	static int i = 0;

	//DrawBox((PlayerX), (PlayerY),
	//	(PlayerX)+CHA_SIZE_X, (PlayerY)+CHA_SIZE_Y,
	//	GetColor(255, 255, 255), TRUE);//左下に当たり判定あり
	//DrawGraph(PlayerX, PlayerY, Player_Pic[0], false);
	// プレイヤーの描画右
	if (g_NowKey & PAD_INPUT_RIGHT && Bectl == 0 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic[i/10], true);
		if (++i >= 40) {
			i = 0;
		}
	}
	else if(Bectl == 0 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == false){
		i = 0;
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic[0], true);
	}

	// プレイヤーの描画左
	else if (g_NowKey & PAD_INPUT_LEFT && Bectl == 1 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_R[3 - i / 10], true);
		if (++i >= 40) {
			i = 0;
		}
	}
	else if (Bectl == 1 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
		i = 0;
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_R[3], true);
	}
	//プレイヤーが鉄球をもっている画像右
	else if (g_NowKey & PAD_INPUT_RIGHT && Bectl == 0 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == true) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Hold[i / 10], true);
		if (++i >= 40) {
			i = 0;
		}
	}
	else if (Bectl == 0 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == true) {
		i = 0;
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Hold[0], true);
	}

	//プレイヤーが鉄球をもっている画像右
	else if (g_NowKey & PAD_INPUT_LEFT && Bectl == 1 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == true) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Hold_R[3 - i / 10], true);
		if (++i >= 40) {
			i = 0;
		}
	}
	else if (Bectl == 1 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == true) {
		i = 0;
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Hold_R[3], true);
	}

	//攻撃用画像右
	if (Attack >= 10 && Bectl == 0 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X*2, PlayerY + CHA_SIZE_Y, Player_Pic_Attack[5 - Attack/5], true);
	}
	//攻撃用画像左
	else if (Attack >= 10 && Bectl == 1 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
		DrawExtendGraph(PlayerX - CHA_SIZE_X, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Attack_R[Attack / 5], true);
	}

	//しゃがみ画像
	if (Bectl == 0 && Attack < 10 && Down_flg == 1 && g_IronBall.HoldFlg == false) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y/4*3, Player_Pic_Down, true);
	}
	else if (Bectl == 1 && Attack < 10 && Down_flg == 1 && g_IronBall.HoldFlg == false) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y/4*3, Player_Pic_Down_R, true);
	}

}

void PlayerGravity() {
	int i = 0, j = 0, w = 0, z = 0;//ローカルなので気にしないでください!あたり判定用の補正値
	int flg = 0;//ローカル変数です

	//プレイヤー重力
	NewY = PlayerY;

	if (Jump_Flg == 0 || Jump_Flg == -1) {
		NewY += GRAVITY;
	}
	//ジャンプ処理
	else if (Jump_Flg == 4 || Jump_Flg == 6) {
		y_temp = NewY;
		NewY += (NewY - y_prev) + 2;
		y_prev = y_temp;
		Jump_Flg = 5;
	}
	else if (Jump_Flg == 2) {
		y_temp = NewY;
		NewY += (NewY - y_prev) + 1;
		y_prev = y_temp;
		//NewY -= 12;
		Jump_Flg = 3;
	}
	else if(Jump_Flg>0){
		Jump_Flg++;
	}

	// スライド用の０から３１までの値
	MapDrawPointY = -(Map_PlayerY % MAP_SIZE);

	MapY = (Map_PlayerY) / MAP_SIZE;

	MapChipNumX = 0;
	MapChipNumY = 0;
	for (int k = 1; MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) >= WIDTH * k; k++) {
		MapChipNumX += WIDTH;
		MapChipNumY += HEIGHT;
	}


	//プレイヤー位置がマップをまたいでいる(右側だけ）
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X-1) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//真ん中の位置がマップをまたいでいる
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX  >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}
	//DrawFormatString(x * MAP_SIZE + MapDrawPointX, y * MAP_SIZE + MapDrawPointY, 0xffffff, "%d %d", y + MapY + MapChipNumY, x + MapX + MapChipNumX);

	//敵キャラが移動する場所にいたら戻す
	for (int a = 0; a < ENEMY_MAX; a++) {
		if (g_Enemy[a].Life > 0) {
			if (g_Enemy[a].x - PlayerX - Map_PlayerX < CHA_SIZE_X 
				&& g_Enemy[a].y - NewY - Map_PlayerY < CHA_SIZE_Y - 1 
				&& g_Enemy[a].x - PlayerX - Map_PlayerX > 0 - g_Enemy[a].w
				&& g_Enemy[a].y - NewY - Map_PlayerY > 0 - g_Enemy[a].h) {
				flg = 1;
			}
		}
	}



	// 進入不可能なマップだった場合は重力を消す
	if (g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1						//左真ん中
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w ] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] != 1	
		)
	{
		if (Jump_Flg == -1) {
			PlayerY = (NewY / MAP_SIZE) * MAP_SIZE + CHA_SIZE_Y % MAP_SIZE;
			Jump_Flg = 0;
		}
		else if(Jump_Flg != 0) 
		{
			Jump_Flg = -1;
		}
		else if (Jump_Flg == 0) {
			PlayerY = (NewY / MAP_SIZE) * MAP_SIZE + CHA_SIZE_Y % MAP_SIZE;
		}
		
		
	}//鉄球がある場合と敵がいた場合
	else if ((g_IronBall.x - PlayerX - Map_PlayerX < CHA_SIZE_X + IRONBALL_R
		  && g_IronBall.y - NewY - Map_PlayerY < CHA_SIZE_Y - 1 + IRONBALL_R
		  && g_IronBall.x - PlayerX - Map_PlayerX > 0 - IRONBALL_R
		  && g_IronBall.y - NewY - Map_PlayerY > 0 - IRONBALL_R
		  && g_IronBall.HoldFlg == false)
		  || flg==1) {
		if (Jump_Flg == -1) {
		//	PlayerY = (NewY / MAP_SIZE) * MAP_SIZE + CHA_SIZE_Y % MAP_SIZE;
			Jump_Flg = 0;
		}
		else if (Jump_Flg != 0)
		{
			Jump_Flg = -1;
		}
	}
	else {
		if (Jump_Flg == 0) {
			Jump_Flg = -1;
		}
		PlayerY = NewY;
		
	}
}


//攻撃
void PlayerAttack() {
	if (g_NowKey & PAD_INPUT_3 && g_IronBall.HoldFlg == false) {
		if (Attack == 0) {
			Attack = 30;
		}
	}

	if(--Attack > 0){
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (g_Enemy[i].Life > 0) {					//敵のライフが０じゃないなら座標をみる
				if (Bectl == 0 && g_Enemy[i].outtime == 0) {						//右向き
					if (   g_Enemy[i].x - PlayerX - Map_PlayerX < CHA_SIZE_X * 2
						&& g_Enemy[i].x - PlayerX - Map_PlayerX > 0) {
						g_Enemy[i].Life--;
						g_Enemy[i].outtime = 30;
					}
				}else if (Bectl == 1) {						//右向き
					if (   g_Enemy[i].x - PlayerX - Map_PlayerX > 0 - CHA_SIZE_X 
						&& g_Enemy[i].x - PlayerX - Map_PlayerX < 0) {
						g_Enemy[i].Life--;
						g_Enemy[i].outtime = 30;
					}
				}
				
			}
		}
	}
	else if (Attack < 0) {
		Attack = 0;
	}
}