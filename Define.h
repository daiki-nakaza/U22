#pragma once

#include "DxLib.h"

#define HEIGHT 22 //�P��ʂ̍���
#define WIDTH 32//�P��ʂ̕�
#define STAGE 10
#define MAP_SIZE 32//32�r�b�g
#define CHA_SIZE 48//48�r�b�g
#define GRAVITY 4//1,2,4,8,16,32�̃p�^�[������

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