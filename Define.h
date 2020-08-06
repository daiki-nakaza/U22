#pragma once

#include "DxLib.h"

#define HEIGHT 22 //�P��ʂ̍���
#define WIDTH 32//�P��ʂ̕�
#define STAGE 10
#define MAP_SIZE 32//32�h�b�g
#define CHA_SIZE_X 32//32�h�b�g
#define CHA_SIZE_Y 64//64�h�b�g
#define GRAVITY 4//1,2,4,8,16,32�̃p�^�[������

#define LOCK_MAX 12

#define ENEMY_MAX 10
#define WALK_ENEMY_SIZE 48	//�G�̑傫��
#define SHOOT_ENEMY_SIZE 48
#define  Bullet_MAX 3

#define  Bullet_MAX 3
#define BULLET_W 20
#define BULLET_H 10

#define MAP_LONG 10

/****************************************************
*�񋓑̂̐錾
****************************************************/
typedef enum MENU_MODE {
	GAME_TITLE,//�O
	GAME_MAIN,//�P
	GAME_END,//�Q
	GAME_MENU,//3
	GAME_INIT,//4
	GAME_CLEAR,//5
	GAME_HELP,//6


	END = 99
};