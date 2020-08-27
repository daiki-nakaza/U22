#pragma once

#include "DxLib.h"

#define HEIGHT 22 //�P��ʂ̍���
#define WIDTH 32//�P��ʂ̕�
#define STAGE 10
#define MAP_SIZE 32//32�h�b�g
#define CHA_SIZE_X 32//32�h�b�g
#define CHA_SIZE_Y 64//64�h�b�g
#define GRAVITY 4//1,2,4,8,16,32�̃p�^�[������

#define LOCK_MAX 16

#define ENEMY_MAX 10
#define WALK_ENEMY_SIZE 64	//�G�̑傫��
#define SHOOT_ENEMY_SIZE 72
#define TANK_ENEMY_SIZE 62
#define RAZER_ENEMY_SIZE 64

#define BOSS_W 64
#define BOSS_H 96
#define TP_MAX 5			//�e���|�[�g��̐�

#define  Bullet_MAX 3

#define  Bullet_MAX 3
#define BULLET_W 20
#define BULLET_H 10


#define  BOSS_Bullet_MAX 5
#define BOSS_BULLET_W 20
#define BOSS_BULLET_H 10

#define MAP_LONG 10

/****************************************************
*�񋓑̂̐錾
****************************************************/
typedef enum MENU_MODE {
	GAME_TITLE,//�O
	GAME_MAIN,//�P
	GAME_HELP,//2
	GAME_END,//3
	GAME_MENU,//4
	GAME_INIT,//5
	GAME_CLEAR,//6
	GAME_OVER,//7

	


	END = 99
};
