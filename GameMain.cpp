#include "DxLib.h"


#include "GameMain.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "accessory.h"
#include "UI.h"

int reset = 0;

void DrawGameMain() {
	//static int i = 0;
	if (reset++ == 0) {
		PlayerInit();
		MapChipInit();

	}
	else if (reset++ == 5) {//���C�t�ȊO�̃��Z�b�g
	}
	MapDisp();			//�}�b�v�̕`��
	MapMove();			//�X�N���[���̏���

	IronBallDisp();		//�S���̕`�揈��
	IronBallMove();		//	�S���̓����̏���

	PlayerMove();
	PlayerDisp();


	enemyDisp();		//�G�̕`�揈��
	enemyMove();		//�G�̏���

	PlayerAttack();		//�v���C���[�U��

	HUDDisp();
}

