#include "DxLib.h"

#include "Define.h" 
#include "Player.h" 
#include "Map.h"
#include "GameEnd.h" 
#include "GameTitle.h"
#include "accessory.h"

int g_OvreY = 0;
int g_OverNumber = 0;
int g_OverTime = 0;

int g_GameOverImage;
int g_GameClearImage;

int ClearTime = 0;


void DrawEnd() {			//
	static int WaitTime = 0;

	//�^�C�g���摜�\��
	//DrawGraph(0, 0, g_TitleImage, FALSE);

	SetFontSize(24);
	DrawString(360, 480 - 24, "Thank you for Playing", 0xffffff, 0);

	//�^�C���̉��Z�������I���i3�b��j
	if (++WaitTime > 180) {
		g_GameState = END;
	}
}


void DrawClear(void) {				//�Q�[���N���A�`�揈��
	if (ClearTime > 60) {
		DrawGraph(0, 0, g_GameClearImage, FALSE);

		//���j���[�J�[�\���ړ�����
		if (--g_OverTime <= 0) {
			if (g_KeyFlg & PAD_INPUT_DOWN) {

				if (++g_OverNumber > 1) {
					g_OverNumber = 0;
				}
				g_OverTime = 10;
			}
			if (g_KeyFlg & PAD_INPUT_UP) {
				if (--g_OverNumber < 0) {
					g_OverNumber = 1;
				}
				g_OverTime = 10;
			}

		}

		//���L�[�Ń��j���[�I��
		if (--g_OverTime <= 0) {
			if (g_KeyFlg & PAD_INPUT_A) {
				if (g_OverNumber == 1) {
					g_GameState = 0;
					ClearTime = 0;
				}
				else {
					g_GameState = 0;
					ClearTime = 0;
				}

				g_MenuTime = 20;
			}
		}

		//���j���[�J�[�\���i�O�p�`�j�̕\��
		g_OvreY = g_OverNumber * 130;

		/*DrawString(265, 263, "�Q�[���X�^�[�g", 0xffffff);
		DrawString(265, 315, "�Q�[���w���v", 0xffffff);
		DrawString(265, 367, "�I��", 0xffffff);*/

		DrawTriangle(40, 335 + g_OvreY, 80, 370 + g_OvreY,
			40, 405 + g_OvreY, GetColor(255, 0, 0), TRUE);
		DrawFormatString(0, 0, 0xffffff, "mouseX = %d   Y = %d", g_MouseX, g_MouseY);

	}
	else if (ClearTime <= 60) {
		MapDisp();
		IronBallDisp();		//�S���̕`�揈��
		PlayerDisp();
		ClearTime++;
	}
	
}


void DrawGameOver(void) {			//�Q�[���I�[�o�[�`�揈��
	DrawGraph(0, 0, g_GameOverImage, FALSE);

	//���j���[�J�[�\���ړ�����
	if (--g_OverTime <= 0) {
		if (g_KeyFlg & PAD_INPUT_DOWN) {

			if (++g_OverNumber > 1) {
				g_OverNumber = 0;
			}
			g_OverTime = 10;
		}
		if (g_KeyFlg & PAD_INPUT_UP) {
			if (--g_OverNumber < 0) {
				g_OverNumber = 1;
			}
			g_OverTime = 10;
		}

	}

	//���L�[�Ń��j���[�I��
	if (--g_OverTime <= 0) {
		if (g_KeyFlg & PAD_INPUT_A) {
			if (g_OverNumber == 1) {
				g_GameState = GAME_END;
			}
			else {
				g_GameState = 0;

			}
			
			g_MenuTime = 20;
		}
	}
	
	//�^�C�g���摜�\��
	/*if (++titleTime >= 60) {
		titleTime = 0;
	}*/

	/*if (titleTime < 30) {
		if (g_MenuNumber == 0) {
			DrawGraph(0, 0, g_Title5Image, FALSE);
		}
		else if (g_MenuNumber == 1) {
			DrawGraph(0, 0, g_Title7Image, FALSE);
		}
	}
	else if (titleTime < 60) {
		if (g_MenuNumber == 0) {
			DrawGraph(0, 0, g_Title6Image, FALSE);
		}
		else if (g_MenuNumber == 1) {
			DrawGraph(0, 0, g_Title8Image, FALSE);
		}

	}*/

	//���j���[�J�[�\���i�O�p�`�j�̕\��
	g_OvreY = g_OverNumber * 130;

	/*DrawString(265, 263, "�Q�[���X�^�[�g", 0xffffff);
	DrawString(265, 315, "�Q�[���w���v", 0xffffff);
	DrawString(265, 367, "�I��", 0xffffff);*/

	DrawTriangle(60, 365 + g_OvreY, 80, 400 + g_OvreY,
		60, 435 + g_OvreY, GetColor(255, 0, 0), TRUE);
	DrawFormatString(0, 0, 0xffffff, "mouseX = %d   Y = %d", g_MouseX, g_MouseY);
}