#include "DxLib.h"

#include "Player.h"


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