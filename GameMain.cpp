#include "DxLib.h"


#include "GameMain.h"
#include "Map.h"
#include "Enemy.h"



void DrawGameMain() {
	MapDisp();			//�}�b�v�̕`��
	MapMove();			//�X�N���[���̏���

	enemyDisp();		//�G�̕`�揈��
	enemyMove();		//�G�̏���
}

