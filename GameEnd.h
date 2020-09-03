#pragma once

#include "DxLib.h"

extern int g_GameOverImage;//ゲームオーバー背景
extern int g_GameClearImage;//ゲームクリア背景
extern int g_StageClearImage;//ステージクリア背景


void DrawEnd(void);

void DrawClear(void);			//ゲームクリア描画処理
void DrawGameOver(void);		//ゲームオーバー描画処理
