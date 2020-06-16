#include "DxLib.h"

#include "Player.h"
#include "Map.h"


//プレイヤーの位置
int PlayerX, PlayerY;              //0～画面半分まで。（プレイヤー位置）
int Map_PlayerX, Map_PlayerY;      //マップ全体のスクロール位置（マップ位置）
int OldX, OldY;	// 移動する前のプレイヤーの位置を保存する変数
int Map_OldX, Map_OldY;	// 移動する前のプレイヤーの位置を保存する変数

void PlayerInit() {

	// プレイヤーの初期位置をセット
	PlayerX = 200;
	PlayerY = 200;
	Map_PlayerX = 0;
	Map_PlayerY = 0;

}

void PlayerMove() {

	int i = 0, j = 0, w = 0, z = 0;//ローカルなので気にしないでください!あたり判定用の補正値

	////プレイヤー重力
	//PlayerY += GRAVITY;
	

	// 移動する前のプレイヤーの位置を保存
	OldX = PlayerX;
	OldY = PlayerY;
	Map_OldX = Map_PlayerX;
	Map_OldY = Map_PlayerY;
	

	// キー入力に応じてプレイヤーの座標を移動
	if (g_NowKey & PAD_INPUT_LEFT) PlayerX -= 2;
	if (g_NowKey & PAD_INPUT_RIGHT) PlayerX += 2;
	if (g_NowKey & PAD_INPUT_UP) PlayerY -= 2;
	if (g_NowKey & PAD_INPUT_DOWN) PlayerY += 2;

	
		

//	DrawFormatString(0, 0, 0x000000, "%d", PlayerY);
//	DrawFormatString(0, 20, 0x000000, "%d", Map_PlayerY);

	if (PlayerX > 500) {
		PlayerX = 500;
		Map_PlayerX += 2;
	}
	if (PlayerX < 64) {
		PlayerX = 64;
		if (Map_PlayerX > 0) {
			Map_PlayerX -= 2;
		}

	}

	// スライド用の０から３１までの値
	MapDrawPointX = -(Map_PlayerX % MAP_SIZE);
	MapDrawPointY = -(Map_PlayerY % MAP_SIZE);

	MapX = (Map_PlayerX) / MAP_SIZE;
	MapY = (Map_PlayerY) / MAP_SIZE;

	MapChipNumX = 0;
	MapChipNumY = 0;
	for (int k = 1; MapX + (PlayerX / MAP_SIZE)  >= WIDTH * k; k++) {
		MapChipNumX += WIDTH;
		MapChipNumY += HEIGHT;
	}

	//落下した場合
	if (MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) + MapChipNumY > HEIGHT) {
	}

	//プレイヤー位置がマップをまたいでいる
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) - MapChipNumX > WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//真ん中の位置がマップをまたいでいる
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX > WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}




	//// 重力が邪魔だったら消す
	//if ( g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1)
	//{
	//	PlayerY -= GRAVITY;	
	//}

	// 進入不可能なマップだった場合は移動できない
	if (g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) ) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) ) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE/2) / MAP_SIZE) - MapChipNumX - w] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1
		)
	{
		PlayerX = OldX;
		PlayerY = OldY;
		Map_PlayerX = Map_OldX;
		Map_PlayerY = Map_OldY;

	}
}

void PlayerDisp() {
	// プレイヤーの描画
	DrawBox((PlayerX), (PlayerY),
		(PlayerX)+CHA_SIZE, (PlayerY)+CHA_SIZE,
		GetColor(255, 255, 255), TRUE);//左下に当たり判定あり
}

void PlayerGravity() {
	int i = 0, j = 0, w = 0, z = 0;//ローカルなので気にしないでください!あたり判定用の補正値

	//プレイヤー重力
	PlayerY += GRAVITY;


	// 移動する前のプレイヤーの位置を保存
	OldX = PlayerX;
	OldY = PlayerY;
	Map_OldX = Map_PlayerX;
	Map_OldY = Map_PlayerY;


	// キー入力に応じてプレイヤーの座標を移動
	if (g_NowKey & PAD_INPUT_LEFT) PlayerX -= 2;
	if (g_NowKey & PAD_INPUT_RIGHT) PlayerX += 2;
	if (g_NowKey & PAD_INPUT_UP) PlayerY -= 32;
	if (g_NowKey & PAD_INPUT_DOWN) PlayerY += 2;




	//	DrawFormatString(0, 0, 0x000000, "%d", PlayerY);
	//	DrawFormatString(0, 20, 0x000000, "%d", Map_PlayerY);

	if (PlayerX > 500) {
		PlayerX = 500;
		Map_PlayerX += 2;
	}
	if (PlayerX < 64) {
		PlayerX = 64;
		if (Map_PlayerX > 0) {
			Map_PlayerX -= 2;
		}

	}

	// スライド用の０から３１までの値
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

	//落下した場合
	if (MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) + MapChipNumY > HEIGHT) {
	}

	//プレイヤー位置がマップをまたいでいる
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) - MapChipNumX > WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//真ん中の位置がマップをまたいでいる
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX > WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}




	// 重力が邪魔だったら消す
	if (g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1)
	{
		PlayerY -= GRAVITY;
	}

	// 進入不可能なマップだった場合は移動できない
	if (g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1
		)
	{
		PlayerX = OldX;
		PlayerY = OldY;
		Map_PlayerX = Map_OldX;
		Map_PlayerY = Map_OldY;

	}
}