#pragma once

#include "DxLib.h"

#define HEIGHT 22 //１画面の高さ
#define WIDTH 32//１画面の幅
#define STAGE 10
#define MAP_SIZE 32//32ドット
#define CHA_SIZE_X 32//32ドット
#define CHA_SIZE_Y 64//64ドット
#define GRAVITY 4//1,2,4,8,16,32のパターンあり

/****************************************************
*列挙体の宣言
****************************************************/
typedef enum MENU_MODE {
	GAME_TITLE,//０
	GAME_MAIN,//１
	GAME_END,//２
	GAME_MENU,//3
	GAME_INIT,//4
	GAME_CLEAR,//5
	GAME_HELP,//6


	END = 99
};