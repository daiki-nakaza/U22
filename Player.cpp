#include "DxLib.h"
#include "Math.h"

#include "Player.h"
#include "Map.h"
#include "PlayerAndIronBall.h"
#include "Enemy.h"
#include "IronToEnemy.h"
#include "GameMain.h"


//デバック用
bool DebugMode = false;
int zzze = 0;


//プレイヤーの位置
int PlayerX, PlayerY;              //0～画面半分まで。（プレイヤー位置）
int Map_PlayerX, Map_PlayerY;      //マップ全体のスクロール位置（マップ位置）
int NewX, NewY;	// 移動する前のプレイヤーの位置を保存する変数
int Map_NewX, Map_NewY;	// 移動する前のプレイヤーの位置を保存する変数
int Jump_Flg;
int y_temp;
int y_prev;
int Down_flg;//しゃがみのフラグ
int PlayerLife;
int Playerouttime;

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

int Player_HP[8];//プレイヤーHPの画像

int g_Sword_Swing; //剣を振るse
int g_Player_Jump; //ジャンプse
int g_Player_Damage; //敵に当たった時のse

void PlayerInit() {

	// プレイヤーの初期位置をセット
	PlayerX = 200;//200
	PlayerY = 54;//544
	Map_PlayerX = 0;
	Map_PlayerY = 0;

	PlayerLife = 7;		//ライフ
	Playerouttime = 0;

	Jump_Flg = false;

	Bectl = 0;//０は右向き、１は左向き
	Attack = 0;//０は攻撃可能
	Down_flg = 0;//０はしゃがんでない１はしゃがんでいる

}

void PlayerMove() {

	int i = 0, j = 0, w = 0, z = 0;//ローカルなので気にしないでください!あたり判定用の補正値
	int flg = 0;//ローカル変数で、敵との当たり判定につかっています
	int aoi = 0;

	if (DebugMode) {
		if (Locka.x[0] != (PlayerX + Map_PlayerX + 16)) {
			aoi = 1;
		}
	}

	//プレイヤー重力
	PlayerGravity(0);
	
	if (DebugMode) {
		if (Locka.x[0] != (PlayerX + Map_PlayerX + 16)) {
			aoi = 1;
		}
	}

	// 移動する前のプレイヤーの位置を保存
	NewX = PlayerX;
	NewY = PlayerY;
	Map_NewX = Map_PlayerX;
	Map_NewY = Map_PlayerY;

	//しゃがみのフラグを毎回０にする
	Down_flg = 0;

	if (DebugMode) {
		DrawFormatString(500, 0, 0xffffff, "%d", Locka.WI);
	}

	//ぶら下がっているフラグ
	//if (Locka.WI > 0) {
	//	Locka.HenkaX += 2;
	//	NewX += 2;
	////	Locka.WI = 0;
	//}
	//else if (Locka.WI < 0) {
	//	Locka.HenkaX -= 2;
	//	NewX -= 2;
	////	Locka.WI = 0;
	//}


	//キー入力に応じてプレイヤーの座標を移動 上
	if (g_NowKey & PAD_INPUT_UP && g_IronBall.HoldFlg == false && g_IronBall.ThrowFlg == false && !(g_NowKey & PAD_INPUT_1)) {
		if (Jump_Flg == 0) {

			PlaySoundMem(g_Player_Jump, DX_PLAYTYPE_BACK);// ジャンプ音
			y_prev = PlayerY;
			NewY -= 16;
			Locka.HenkaY -= 16;
			Jump_Flg = 1;
			PlayerGravity(1);
		}
		else if (Jump_Flg == 3) {
			Jump_Flg = 1;
		}
	}
	//  左
	if (g_NowKey & PAD_INPUT_LEFT && g_IronBall.ThrowFlg == false && !(g_NowKey & PAD_INPUT_1) && Jump_Flg != -2 && !(Locka.RD < 0 && Jump_Flg != 0)) {
		NewX -= 2;
		Locka.HenkaX -= 2;
		if (g_IronBall.HoldFlg == true) {//鉄球を持っている場合
			Locka.LenkaX -= 2;
		}

		if (Attack < 10 && g_IronBall.ThrowFlg == false) {
			Bectl = 1;
		}
		if (Locka.RD > 0) {
			Locka.RD = 0;
		}
	}
	//右
	if (g_NowKey & PAD_INPUT_RIGHT && g_IronBall.ThrowFlg == false && !(g_NowKey & PAD_INPUT_1) && Jump_Flg != -2 && !(Locka.RD > 0 && Jump_Flg != 0)) {
		NewX += 2; 
		Locka.HenkaX += 2;
		if (g_IronBall.HoldFlg == true) {//鉄球を持っている場合
			Locka.LenkaX += 2;
		}

		//攻撃しておらず、鉄球を投げていないときだけ向いている方向をかえることができる。
		if (Attack < 10 && g_IronBall.ThrowFlg == false) {
			Bectl = 0;
		}
		if (Locka.RD < 0) {
			Locka.RD = 0;
		}
	}
	
	//しゃがみ用、自由落下中はJump_Flgが-1なので、地面についているときだけ作用する
	if (g_NowKey & PAD_INPUT_DOWN && Jump_Flg == 0 && g_IronBall.HoldFlg == false && g_IronBall.ThrowFlg == false && !(g_NowKey & PAD_INPUT_1) && Attack == 0) {
	//	PlayerY += 16;
	//	NewY += 16; 
		Down_flg = 1;
	}

	//鎖の移動できるか処理
	//Locka.HenkaY = 0;
	Locka.MoveCheck();
	
	
	
	if (DebugMode) {
		DrawFormatString(0, 0, 0xffffff, "%d", Jump_Flg);
	}

	if (NewX > 500) {
		Map_NewX += NewX - 500;
		NewX = 500;
	}
	if (NewX < 64) {
		if (Map_NewX > 0) {
			Map_NewX -= 64 - NewX;
			NewX = 64;
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
		if (flg == 1) {
			break;
		}
		flg = PlayerMoveCheck(g_WalkEnemy[a]);
		if (flg == 1) {
			break;
		}
		flg = PlayerMoveCheck(g_ShootEnemy[a]);
		if (flg == 1) {
			break;
		}
		flg = PlayerMoveCheck(g_LockShootEnemy[a]);
		if (flg == 1) {
			break;
		}
		flg = PlayerMoveCheck(g_TankEnemy[a]);
		if (flg == 1) {
			break;
		}
		flg = PlayerMoveCheck(g_RazerEnemy[a]);
		if (flg == 1) {
			break;
		}
	}
	if (Playerouttime != 0) {
		flg = 0;
	}

	//鉄球の中に入った場合。//あとで書く

	//落下した場合
	if (g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 11												//左上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 11								//左下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 11						//左真ん中

		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 11						//右上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 11			//右下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 11			//右真ん中

		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] == 11						//真ん中上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] == 11		//真ん中下
		)
	{
		g_GameState = GAME_OVER;
	}

	//クリア
	if (g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 2												//左上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 2								//左下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 2						//左真ん中
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 2						//右上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 2			//右下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 2			//右真ん中
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] == 2						//真ん中上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] == 2		//真ん中下
		
		||g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 10												//左上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 10								//左下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 10						//左真ん中
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 10						//右上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 10			//右下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 10			//右真ん中
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] == 10						//真ん中上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] == 10		//真ん中下
		) 
	{
		g_GameState = GAME_CLEAR;
	}



	

	// 進入不可能なマップだった場合は移動できない//鉄球がある//鎖の長さが大丈夫かどうか
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
		//|| (pow((double)g_IronBall.x - (double)NewX - (double)Map_NewX - (double)CHA_SIZE_X / 2.0, 2.0) + pow((double)g_IronBall.y - (double)NewY - (double)Map_NewY - (double)CHA_SIZE_Y / 2.0, 2.0) > pow((double)MAP_SIZE * 9.0, 2.0))
		|| flg == 1
		|| (Locka.HenkaX != 0 || Locka.HenkaY != 0)
		)
	{
		//壁にあたって、ここにはいったなら移動した鎖を元に戻す
		//if (Locka.HenkaX == 0 && Locka.HenkaY == 0) {
			for (int i = 0; i < LOCK_MAX; i++) {
				Locka.New_x[i] = Locka.x[i];
				Locka.New_y[i] = Locka.y[i];
			}
		//}
		if (Locka.HenkaX > 0 ) {
			Locka.RD = 2;
		}
		else if (Locka.HenkaX < 0) {
			Locka.RD = -2;
		}
		
		Locka.HenkaX = 0;
		Locka.HenkaY = 0;

		if (Locka.LenkaX != 0 || Locka.LenkaY != 0) {
			g_IronBall.x -= Locka.LenkaX;
			Locka.LenkaX = 0;
			Locka.LenkaY = 0;
		}

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
		zzze = 10;
		
	}
	else {	
			PlayerX = NewX;
			PlayerY = NewY;
			Map_PlayerX = Map_NewX;
			Map_PlayerY = Map_NewY;

			Locka.LenkaX = 0;//移動成功なら、鉄球に引っ張られていても、成功ということで０にする
			Locka.LenkaY = 0;//移動成功なら、鉄球に引っ張られていても、成功ということで０にする
			zzze = 11;
	}
	Locka.Move(1);
	// 移動する前のプレイヤーの位置を保存
	NewX = PlayerX;
	NewY = PlayerY;
	Map_NewX = Map_PlayerX;
	Map_NewY = Map_PlayerY;

	if (Playerouttime-- <= 0) Playerouttime = 0;
}

void PlayerDisp() {
	static int i = 0;
	//return;
	//DrawBox((PlayerX), (PlayerY),
	//	(PlayerX)+CHA_SIZE_X, (PlayerY)+CHA_SIZE_Y,
	//	GetColor(255, 255, 255), TRUE);//左下に当たり判定あり
	//DrawGraph(PlayerX, PlayerY, Player_Pic[0], false);


	//HPの表示

	DrawExtendGraph(10, 10, 112, 42, Player_HP[7 - PlayerLife], true);



	// プレイヤーの描画右
	if (Playerouttime == 0 || Playerouttime % 2 == 1) {
		if (g_NowKey & PAD_INPUT_RIGHT && Bectl == 0 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
			DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic[i / 10], true);
			if (++i >= 40) {
				i = 0;
			}
		}
		else if (Bectl == 0 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
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
			DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X * 2, PlayerY + CHA_SIZE_Y, Player_Pic_Attack[5 - Attack / 5], true);
		}
		//攻撃用画像左
		else if (Attack >= 10 && Bectl == 1 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
			DrawExtendGraph(PlayerX - CHA_SIZE_X, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Attack_R[Attack / 5], true);
		}

		//しゃがみ画像
		if (Bectl == 0 && Attack < 10 && Down_flg == 1 && g_IronBall.HoldFlg == false) {
			DrawExtendGraph(PlayerX, PlayerY + 16, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Down, true);
		}
		else if (Bectl == 1 && Attack < 10 && Down_flg == 1 && g_IronBall.HoldFlg == false) {
			DrawExtendGraph(PlayerX, PlayerY + 16, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Down_R, true);
		}
		
	}
	if (DebugMode) {
		DrawCircle(Locka.x[0] + MapDrawPointX - MapX * MAP_SIZE, Locka.y[0] - MapDrawPointY - MapY * MAP_SIZE, 4, GetColor(252, 252, 252), true);
		DrawCircle(Locka.x[1] + MapDrawPointX - MapX * MAP_SIZE, Locka.y[1] - MapDrawPointY - MapY * MAP_SIZE, 4, GetColor(252, 50, 252), true);
		DrawCircle(g_IronBall.New_x, g_IronBall.New_y, 4, GetColor(252, 50, 252), true);

	}
	//
	/*if (Attack > 0) {
		DrawLine(PlayerX  + CHA_SIZE_X * 2 + 16, 0, PlayerX + CHA_SIZE_X * 2 + 16, 1000,true);
	}*/
	
}

void PlayerGravity(int bn) {
	int i = 0, j = 0, w = 0, z = 0;//ローカルなので気にしないでください!あたり判定用の補正値
	int flg = 0;//ローカル変数です。敵キャラが移動する場所にいるかどうかのフラグ

	if (bn == 0) {
		// 移動する前のプレイヤーの位置を保存
		NewX = PlayerX;
		NewY = PlayerY;
		Map_NewX = Map_PlayerX;
		Map_NewY = Map_PlayerY;

		//プレイヤー重力
		NewY = PlayerY;

		if (Jump_Flg == 0 || Jump_Flg == -1 || Jump_Flg == -2) {
			NewY += GRAVITY;
			if (Jump_Flg == -1 || Jump_Flg == -2) {
				Locka.HenkaY += GRAVITY;
			}

		}
		//ジャンプ処理
		else if (Jump_Flg == 4 || Jump_Flg == 6) {
			y_temp = NewY;
			Locka.HenkaY += (NewY - y_prev) + 2;
			NewY += (NewY - y_prev) + 2;
			y_prev = y_temp;
			Jump_Flg = 5;
		}
		else if (Jump_Flg == 2) {
			y_temp = NewY;
			Locka.HenkaY += (NewY - y_prev) + 1;
			NewY += (NewY - y_prev) + 1;
			y_prev = y_temp;
			//NewY -= 12;
			Jump_Flg = 3;
		}
		else if (Jump_Flg > 0) {
			Jump_Flg++;
		}
	}

	//鎖の移動処理
	Locka.MoveCheck();

	if (NewX > 500) {
		Map_NewX += NewX - 500;
		NewX = 500;
	}
	if (NewX < 64) {
		if (Map_NewX > 0) {
			Map_NewX -= 64 - NewX;
			NewX = 64;
		}

	}

	// スライド用の０から３１までの値
	MapDrawPointX = -(Map_NewX % MAP_SIZE);
	MapDrawPointY = -(Map_NewY % MAP_SIZE);

	MapX = (Map_NewX) / MAP_SIZE;
	MapY = (Map_NewY) / MAP_SIZE;

	MapChipNumX = 0;
	MapChipNumY = 0;
	for (int k = 1; MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) >= WIDTH * k; k++) {
		MapChipNumX += WIDTH;
		MapChipNumY += HEIGHT;
	}


	//プレイヤー位置がマップをまたいでいる(右側だけ）
	if (MapX + ((NewX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X-1) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//真ん中の位置がマップをまたいでいる
	if (MapX + ((NewX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX  >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}

	if (DebugMode) {
		//DrawFormatString(x * MAP_SIZE + MapDrawPointX, y * MAP_SIZE + MapDrawPointY, 0xffffff, "%d %d", y + MapY + MapChipNumY, x + MapX + MapChipNumX);
	}
	//落下した場合
	if (g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 11												//左上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 11								//左下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 11						//左真ん中

		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 11						//右上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 11			//右下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 11			//右真ん中

		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] == 11						//真ん中上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] == 11		//真ん中下
		)
	{
		g_GameState = GAME_OVER;
	}

	//クリア
	if (g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 2												//左上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 2								//左下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 2						//左真ん中
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 2						//右上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 2			//右下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 2			//右真ん中
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] == 2						//真ん中上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] == 2		//真ん中下

		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 10												//左上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 10								//左下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] == 10						//左真ん中
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 10						//右上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 10			//右下
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] == 10			//右真ん中
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] == 10						//真ん中上
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] == 10		//真ん中下
		)
	{
		g_GameState = GAME_CLEAR;
	}
	//敵キャラが移動する場所にいたら戻す
	/*for (int a = 0; a < ENEMY_MAX; a++) {
		flg = PlayerMoveCheck(g_WalkEnemy[a]);
		if (flg == 1) {
			break;
		}
		flg = PlayerMoveCheck(g_ShootEnemy[a]);
		if (flg == 1) {
			break;
		}
		flg = PlayerMoveCheck(g_LockShootEnemy[a]);
		if (flg == 1) {
			break;
		}
		flg = PlayerMoveCheck(g_TankEnemy[a]);
		if (flg == 1) {
			break;
		}
		flg = PlayerMoveCheck(g_RazerEnemy[a]);
		if (flg == 1) {
			break;
		}
	}

	if (Playerouttime != 0) {
		flg = 0;
	}*/
	flg = 0;
	

	// 進入不可能なマップだった場合は重力を消す
	if (g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1						//左真ん中
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w ] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] != 1	
		)
	{
		/*if (Jump_Flg != 0)
		{
			Jump_Flg = -1;
		}*/
		
		if (Jump_Flg == -1) {
			PlayerY = (NewY / MAP_SIZE) * MAP_SIZE + CHA_SIZE_Y % MAP_SIZE;
			Jump_Flg = 0;
			/*Locka.New_x[0] = Locka.x[0];
			Locka.New_y[0] = PlayerY + 58;*/
		}
		else if(Jump_Flg != 0) 
		{
			Jump_Flg = -1;
			for (int i = 0; i < LOCK_MAX; i++) {
				Locka.New_x[i] = Locka.x[i];
				Locka.New_y[i] = Locka.y[i];
				//			Jump_Flg = -2;//ここばぐるｘが原因
			}
		}
		else if (Jump_Flg == 0) {
			PlayerY = (NewY / MAP_SIZE) * MAP_SIZE + CHA_SIZE_Y % MAP_SIZE;
		}
		//人が地面についたときは人に一番近い鎖だけはもとに戻す
		/*Locka.New_x[0] = Locka.x[0];
		Locka.New_y[0] = Locka.y[0];*/
		zzze = 1;
		
	}//鎖の長さが大丈夫かどうか
	else if ( (Locka.HenkaX != 0 || Locka.HenkaY != 0)) 
	{
		if (Locka.HenkaX != 0 || Locka.HenkaY != 0) {
			for (int i = 0; i < LOCK_MAX; i++) {
				Locka.New_x[i] = Locka.x[i];
				Locka.New_y[i] = Locka.y[i];
	//			Jump_Flg = -2;//ここばぐるｘが原因
			}
			Jump_Flg = -2;//－２にしてるのは、ここだけ

			Locka.HenkaX = 0;
			Locka.HenkaY = 0;

			if (Locka.New_x[0] - Locka.New_x[1] > 0) {//左に移動
				Locka.WI = -1;
			}
			else if (Locka.New_x[0] - Locka.New_x[1] < 0) {
				Locka.WI = 1;
			}
			
		}
		zzze = 2;

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
		for (int i = 0; i < LOCK_MAX; i++) {
			Locka.New_x[i] = Locka.x[i];
			Locka.New_y[i] = Locka.y[i];
		//	Jump_Flg = -2;//ここばぐるｘが原因
		}
		zzze = 3;
	}
	else {
		if (Jump_Flg == 0) {
			Jump_Flg = -1;
		}
		if (Jump_Flg == -2) {
			Jump_Flg = -1;
		}
		PlayerX = NewX;
		PlayerY = NewY;
		zzze = 4;
	}

	

	Locka.HenkaY = 0;
	Locka.HenkaX = 0;
	
	Locka.Move(2);

	// 移動する前のプレイヤーの位置を保存
	NewX = PlayerX;
	NewY = PlayerY;
	Map_NewX = Map_PlayerX;
	Map_NewY = Map_PlayerY;
}


//攻撃
void PlayerAttack() {
	if (g_NowKey & PAD_INPUT_3 && g_IronBall.HoldFlg == false && Down_flg == 0) {
		if (Attack == 0) {
			PlaySoundMem(g_Sword_Swing, DX_PLAYTYPE_BACK);//剣を振る
			Attack = 30;
		}
	}

	
	if(--Attack > 0){
		//PlayerAttackCheck(g_WalkEnemy[0]);
		for (int i = 0; i < ENEMY_MAX; i++) {
			PlayerAttackCheck(&g_WalkEnemy[i]);
			PlayerAttackCheck(&g_ShootEnemy[i]);
			PlayerAttackCheck(&g_LockShootEnemy[i]);
			PlayerAttackCheck(&g_TankEnemy[i]);
			PlayerAttackCheck(&g_RazerEnemy[i]);
		}
	}

	if (Attack < 0) {
		Attack = 0;
	}
}


void PlayerDamage() {		//プレイヤーのdamage処理
	if (Playerouttime == 0) {
		PlaySoundMem(g_Player_Damage, DX_PLAYTYPE_BACK);
		PlayerLife--;
		Playerouttime = 180;
	}

	if (PlayerLife <= 0) {
		g_GameState = GAME_OVER;
		reset = 0;
	}
}