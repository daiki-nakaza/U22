#include "DxLib.h"

#include "Define.h" 
#include "Player.h" 
#include "Map.h"
#include "GameEnd.h" 
#include "GameMain.h"
#include "GameTitle.h"
#include "accessory.h"
#include "Enemy.h"

int PoseTime = 30;

void DrawMenu() {			//�Q�[�����j���[�`�揈��

	MapDisp();
	IronBallDisp();		//�S���̕`�揈��
	PlayerDisp();
	enemyDisp();

	if (g_KeyFlg & PAD_INPUT_8) {//W�L�[
		if (PoseTime <= 0) {
			g_GameState = GAME_MAIN;
			PoseTime = 30;
			PlaySoundMem(g_Stage1, DX_PLAYTYPE_LOOP,false); //
		}
	}

	PoseTime--;
}