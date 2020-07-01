#include "DxLib.h"

#include "Player.h"
#include "Map.h"


//プレイヤーの位置
int PlayerX, PlayerY;              //0～画面半分まで。（プレイヤー位置）
int Map_PlayerX, Map_PlayerY;      //マップ全体のスクロール位置（マップ位置）
int NewX, NewY;	// 移動する前のプレイヤーの位置を保存する変数
int Map_NewX, Map_NewY;	// 移動する前のプレイヤーの位置を保存する変数
int Jump_Flg;
int y_temp;
int y_prev;

void PlayerInit() {

	// プレイヤーの初期位置をセット
	PlayerX = 200;
	PlayerY = 200;
	Map_PlayerX = 0;
	Map_PlayerY = 0;

	Jump_Flg = false;

}

void PlayerMove() {

	int i = 0, j = 0, w = 0, z = 0;//ローカルなので気にしないでください!あたり判定用の補正値

	//プレイヤー重力
	PlayerGravity();
	

	// 移動する前のプレイヤーの位置を保存
	NewX = PlayerX;
	NewY = PlayerY;
	Map_NewX = Map_PlayerX;
	Map_NewY = Map_PlayerY;
	

	// キー入力に応じてプレイヤーの座標を移動
	if (g_NowKey & PAD_INPUT_LEFT) NewX -= 2;
	if (g_NowKey & PAD_INPUT_RIGHT) NewX += 2;
	if (g_NowKey & PAD_INPUT_UP) {
		if (Jump_Flg == 0) {
			y_prev = PlayerY;
			NewY -= 16;
			Jump_Flg = 1;
		}
		else if (Jump_Flg == 3) {
			Jump_Flg = 1;
		}
	}
	if (g_NowKey & PAD_INPUT_DOWN) NewY += 2;

	
	
	

	DrawFormatString(0, 0, 0xffffff,"%d", Jump_Flg);
		

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
	if (MapY + ((NewY + (Map_NewX % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) + MapChipNumY >= HEIGHT) {
	}

	//プレイヤー位置がマップをまたいでいる
	if (MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//真ん中の位置がマップをまたいでいる
	if (MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}


	// 進入不可能なマップだった場合は移動できない
	if (g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) ) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) ) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE/2) / MAP_SIZE) - MapChipNumX - w] != 1
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1
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
	// プレイヤーの描画
	DrawBox((PlayerX), (PlayerY),
		(PlayerX)+CHA_SIZE, (PlayerY)+CHA_SIZE,
		GetColor(255, 255, 255), TRUE);//左下に当たり判定あり
}

void PlayerGravity() {
	int i = 0, j = 0, w = 0, z = 0;//ローカルなので気にしないでください!あたり判定用の補正値

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
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//真ん中の位置がマップをまたいでいる
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX  >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}
	//DrawFormatString(x * MAP_SIZE + MapDrawPointX, y * MAP_SIZE + MapDrawPointY, 0xffffff, "%d %d", y + MapY + MapChipNumY, x + MapX + MapChipNumX);





	// 進入不可能なマップだった場合は重力を消す
	if (g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w ] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1
		)
	{
		if (Jump_Flg == -1) {
			PlayerY = (NewY / MAP_SIZE) * MAP_SIZE + CHA_SIZE % MAP_SIZE;
			Jump_Flg = 0;
			//(MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY) * 32;
		}
		else if(Jump_Flg != 0) 
		{
			Jump_Flg = -1;
		}
		
		
	}
	else {
		PlayerY = NewY;
		
	}
}