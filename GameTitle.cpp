#include "DxLib.h" 

#include "GameTitle.h" 
#include "Player.h" 


int g_MenuTime = 0;
int g_MenuNumber = 0;
int titleTime = 0;
int g_MenuY = 0;


void DrawGameTitle() {		//�Q�[���^�C�g���`�揈��
	//���j���[�J�[�\���ړ�����
	if (--g_MenuTime <= 0) {
		if (g_KeyFlg & PAD_INPUT_DOWN) {

			if (++g_MenuNumber > 2) {
				g_MenuNumber = 0;
			}
			g_MenuTime = 10;
		}
		if (g_KeyFlg & PAD_INPUT_UP) {
			if (--g_MenuNumber < 0) {
				g_MenuNumber = 2;
			}
			g_MenuTime = 10;
		}

	}

	//���L�[�Ń��j���[�I��
	if (--g_MenuTime <= 0) {
		if (g_KeyFlg & PAD_INPUT_A) {
			g_GameState = g_MenuNumber + 1;
			g_MenuTime = 10;
		}
	}

	//�^�C�g���摜�\��
	if (++titleTime >= 60) {
		titleTime = 0;
	}

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
	g_MenuY = g_MenuNumber * 52;

	DrawString(265, 263, "�Q�[���X�^�[�g", 0xffffff);
	DrawString(265, 315, "�Q�[���w���v", 0xffffff);
	DrawString(265, 367, "�I��", 0xffffff);

	DrawTriangle(240, 255 + g_MenuY, 260, 270 + g_MenuY,
		240, 285 + g_MenuY, GetColor(255, 0, 0), TRUE);
}