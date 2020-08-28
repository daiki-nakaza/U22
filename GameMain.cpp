#include "DxLib.h"


#include "GameMain.h"
#include "GameMenu.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "accessory.h"
#include "UI.h"

int reset = 0;

void DrawGameMain() {
	//static int i = 0;
	if (reset++ == 0) {
		Stage = 1;
		PlayerInit();
		MapChipInit();
		enemyInit();
		g_IronBall.HoldFlg = false;
		g_IronBall.ThrowFlg = false; 
		g_IronBall.Init();
		Locka.Init();
		PlaySoundMem(g_Stage1, DX_PLAYTYPE_LOOP,true); //
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


	if (g_KeyFlg & PAD_INPUT_8) {//W�L�[
		if (PoseTime <= 0) {
			g_GameState = GAME_MENU;
			PoseTime = 90;
		}
	}
	PoseTime--;
}

