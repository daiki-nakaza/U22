#include "DxLib.h"


#include "GameMain.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"



void DrawGameMain() {
	MapDisp();			//�}�b�v�̕`��
	MapMove();			//�X�N���[���̏���

	PlayerMove();
	PlayerDisp();


	enemyDisp();		//�G�̕`�揈��
	enemyMove();		//�G�̏���
}

