#pragma once

#include "DxLib.h"
#include "Define.h"

#include "Player.h"
#include "accessory.h"

/****************************************
*		関数のプロトタイプ宣言
******************************************/
void IronInit(int* ironX, int* ironY, int px = PlayerX, int py = PlayerY);		//鉄球の初期化処理
void IronHold(int* ironX, int* ironY, int px = PlayerX, int py = PlayerY);		//鉄球を持っているときの鉄球側の処理
void IronHoldOrThrow();			
												//プレイヤーが鉄球を持つか投げる処理
bool IronToEnemy();