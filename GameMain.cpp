#include "DxLib.h"


#include "GameMain.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "accessory.h"
#include "UI.h"



void DrawGameMain() {
	static int i = 0;
	if (i++ == 0) {
		PlayerInit();
	}
	MapDisp();			//�}�b�v�̕`��
	MapMove();			//�X�N���[���̏���

	PlayerMove();
	PlayerDisp();

	IronBallDisp();		//�S���̕`�揈��
	IronBallMove();		//	�S���̓����̏���


	enemyDisp();		//�G�̕`�揈��
	enemyMove();		//�G�̏���

	PlayerAttack();		//�v���C���[�U��

	HUDDisp();
}

