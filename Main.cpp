#include"DxLib.h"
#include <math.h>

#include "GameMain.h"
#include "GameTitle.h"
#include "GameEnd.h"
#include "GameInit.h"
#include "GameHelp.h"
#include "GameMenu.h"
#include "Map.h"




/****************************************************
*�萔�̐錾
****************************************************/


/****************************************************
*�ϐ��̐錾
****************************************************/


int g_OldKey;
int g_NowKey;
int g_KeyFlg;
int g_OldKey2;
int g_NowKey2;
int g_KeyFlg2;
int g_MouseX;//�}�E�X�����W
int g_MouseY;//�}�E�X�����W


int g_GameState = GAME_MAIN;//�Q�[�����[�h



//int g_MapChip[HEIGHT * 2][WIDTH];

/***************************************
*�T�E���h�p�ϐ�
***************************************/



/*********************************************
*�֐��̃v���g�^�C�v�錾
*********************************************/


int LoadImages();//�摜�ǂݍ���
int LoadSounds();//�����ǂݍ���





/******************************************************
*�v���O�����̊J�n
******************************************************/

//�v���O������WinMain����n�܂�܂�//
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);//�E�B���h�E���[�h�ŋN��
	SetMainWindowText("");//�^�C�g����ݒ�
	SetGraphMode(1024, 700, 16);


	if (DxLib_Init() == -1) {                    //DX���C�u��������������

		return -1;								//�G���[���N�����璼���ɏI��
	}
	//�摜�ǂݍ��݊֐����Ăяo��
	if (LoadImages() == -1) {
		return -1;
	}

	//�T�E���h�ǂݍ��݊֐����Ăяo��
	if (LoadSounds() == -1) {
		return -1;
	}
	


	//DrawInit();

	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0 && g_GameState != END && !(g_KeyFlg & PAD_INPUT_START)) {

		//PlaySoundMem(g_TitleBGM, DX_PLAYTYPE_LOOP, FALSE);

		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & g_OldKey;

		g_OldKey2 = g_NowKey2;
		g_NowKey2 = GetMouseInput();
		g_KeyFlg2 = g_NowKey2 & g_OldKey2;

		//�}�E�X�̈ʒu���擾
		GetMousePoint(&g_MouseX, &g_MouseY);

		ClearDrawScreen();
		DrawBox(0, 0, 1050, 620, 0x2f4f4f, TRUE); // ��ʑS�̂���]�̐F�œh��Ԃ�
		//DrawBox(0, 0, 1050, 620, 0xffffff, TRUE); // ��ʑS�̂���]�̐F�œh��Ԃ�

		switch (g_GameState) {
		case GAME_TITLE:
			DrawGameTitle();
			break;
		case GAME_MAIN:
			DrawGameMain();
			break;
		case GAME_END:
			DrawEnd();
			break;
		case GAME_MENU:
			DrawMenu();
			break;
		case GAME_INIT:
			DrawInit();
			break;
		case GAME_CLEAR:
			DrawClear();
			break;
		case GAME_HELP:
			DrawHelp();
			break;
		}

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}



int LoadImages() {
	//�}�b�v�`�b�v
	MapTip = LoadGraph("images/kenkyu7.png");
	//�w�i
	if ((g_BackGroundImage = LoadGraph("images/haikei.png")) == -1) return -1;
	return 0;
}
int LoadSounds() {
	return 0;
}