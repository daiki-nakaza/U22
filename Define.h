#pragma once

#include "DxLib.h"

#define HEIGHT 22 //１画面の高さ
#define WIDTH 32//１画面の幅
#define STAGE 10
#define MAP_SIZE 32//32ドット
#define CHA_SIZE_X 32//32ドット
#define CHA_SIZE_Y 64//64ドット
#define GRAVITY 4//1,2,4,8,16,32のパターンあり

#define LOCK_MAX 16

#define ENEMY_MAX 10
#define WALK_ENEMY_SIZE 64	//敵の大きさ
#define SHOOT_ENEMY_SIZE 72
#define TANK_ENEMY_SIZE 62
#define RAZER_ENEMY_SIZE 64

#define BOSS_W 64
#define BOSS_H 96
#define TP_MAX 5			//テレポート先の数

#define  Bullet_MAX 3

#define  Bullet_MAX 3
#define BULLET_W 20
#define BULLET_H 10


#define  BOSS_Bullet_MAX 5
#define BOSS_BULLET_W 20
#define BOSS_BULLET_H 10

#define MAP_LONG 10

/****************************************************
*列挙体の宣言
****************************************************/
typedef enum MENU_MODE {
	GAME_TITLE,//０
	GAME_MAIN,//１
	GAME_HELP,//2
	GAME_END,//3
	GAME_MENU,//4
	GAME_INIT,//5
	GAME_CLEAR,//6
	GAME_OVER,//7

	


	END = 99
};
