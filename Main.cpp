#include"DxLib.h"
#include <math.h>

#include "GameMain.h"
#include "GameTitle.h"
#include "GameEnd.h"
#include "GameInit.h"
#include "GameHelp.h"
#include "GameMenu.h"
#include "Map.h"
#include "Player.h"




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


int g_GameState = GAME_TITLE;//�Q�[�����[�h

int g_Title;
int g_GameOver;



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
	SetMainWindowText("Prisoner");//�^�C�g����ݒ�
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
	if (DebugMode) {
		g_GameState = GAME_MAIN;//�Q�[�����[�h
	}


	//DrawInit();

	SetDrawScreen(DX_SCREEN_BACK);

	PlaySoundMem(g_Title, DX_PLAYTYPE_LOOP, FALSE);

	while (ProcessMessage() == 0 && g_GameState != END && !(g_KeyFlg & PAD_INPUT_START)) {

		
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
			StopSoundMem(g_GameOver);
			DrawGameTitle();
			break;
		case GAME_MAIN:
			StopSoundMem(g_Title);
			StopSoundMem(g_GameOver);
			DrawGameMain();
			break;
		case GAME_HELP:
			DrawHelp();
			break;
		case GAME_END:
			DrawEnd();
			break;
		case GAME_MENU:
			StopSoundMem(g_Stage1);
			DrawMenu();
			break;
		case GAME_INIT:
			DrawInit();
			break;
		case GAME_CLEAR:
			DrawClear();
			break;
		case GAME_OVER:
			StopSoundMem(g_Stage1);
			StopSoundMem(g_Title);
			PlaySoundMem(g_GameOver, DX_PLAYTYPE_LOOP, FALSE);
			DrawGameOver();
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
	if ((g_BackGroundImage1 = LoadGraph("images/haikei.png")) == -1) return -1;
	if ((g_BackGroundImage2 = LoadGraph("images/haikei2.png")) == -1) return -1;
	if ((g_BackGroundImage3 = LoadGraph("images/haikei3.png")) == -1) return -1;
	if ((g_PoseImage = LoadGraph("images/pause.png")) == -1) return -1;

	//�v���C���[�摜
	LoadDivGraph("images/shujin.png", 4, 4, 1, CHA_SIZE_X, CHA_SIZE_Y, Player_Pic);
	LoadDivGraph("images/shujin2.png", 4, 4, 1, CHA_SIZE_X, CHA_SIZE_Y, Player_Pic_R);
	LoadDivGraph("images/attack.png", 6, 6, 1, CHA_SIZE_X * 2, CHA_SIZE_Y, Player_Pic_Attack);
	LoadDivGraph("images/attack2.png", 6, 6, 1, CHA_SIZE_X * 2, CHA_SIZE_Y, Player_Pic_Attack_R);
	Player_Pic_Down = LoadGraph("images/shagami.png", true);
	Player_Pic_Down_R = LoadGraph("images/shagami2.png", true);
	LoadDivGraph("images/motu.png", 4, 4, 1, CHA_SIZE_X, CHA_SIZE_Y, Player_Pic_Hold);
	LoadDivGraph("images/motu2.png", 4, 4, 1, CHA_SIZE_X, CHA_SIZE_Y, Player_Pic_Hold_R);
	Player_HP[0] = LoadGraph("images/Life bar.png", true);//�v���C���[HP�̉摜
	Player_HP[1] = LoadGraph("images/Life bar1.png", true);//�v���C���[HP�̉摜
	Player_HP[2] = LoadGraph("images/Life bar2.png", true);//�v���C���[HP�̉摜
	Player_HP[3] = LoadGraph("images/Life bar3.png", true);//�v���C���[HP�̉摜
	Player_HP[4] = LoadGraph("images/Life bar4.png", true);//�v���C���[HP�̉摜
	Player_HP[5] = LoadGraph("images/Life bar5.png", true);//�v���C���[HP�̉摜
	Player_HP[6] = LoadGraph("images/Life bar6.png", true);//�v���C���[HP�̉摜
	Player_HP[7] = LoadGraph("images/Life bar7.png", true);//�v���C���[HP�̉摜



	//�Q�[���^�C�g���w�i
	if ((g_GameTitleImage = LoadGraph("images/Title.png")) == -1) return -1;
	//�Q�[���I�[�o�[�w�i
	if ((g_GameOverImage = LoadGraph("images/GameOver.png")) == -1) return -1;
	//�N���A�p�h�A�摜
	if (( LoadDivGraph("images/Door.png",3,3,1,128,128,g_Door)) == -1) return -1;
	//�Q�[���N���A�w�i
	if ((g_GameClearImage = LoadGraph("images/GameClear.png")) == -1)return -1;


	return 0;

}
int LoadSounds() {

	g_Stage1 = LoadSoundMem("bgm,se/BGM/Stage1.mp3"); //g_Stage1�`3 g_Boss��Map.h�Ő錾���Ă�
	g_Stage2 = LoadSoundMem("bgm,se/BGM/Stage2.mp3");
	g_Stage3 = LoadSoundMem("bgm,se/BGM/Stage3.mp3");
	g_BossSound = LoadSoundMem("bgm,se/BGM/BossBattle.mp3");
	g_Title = LoadSoundMem("bgm,se/BGM/Title.mp3");
	g_GameOver = LoadSoundMem("bgm,se/BGM/GameOver.mp3");

	g_ColorL = LoadSoundMem("bgm,se/Enemy_SE/color_laser.mp3");
	g_Hadou = LoadSoundMem("bgm,se/Enemy_SE/hadou.mp3");
	g_Kakusan = LoadSoundMem("bgm,se/Enemy_SE/kakusan.mp3");
	g_Shot = LoadSoundMem("bgm,se/Enemy_SE/laser.mp3");
	g_Warp = LoadSoundMem("bgm,se/Enemy_SE/warp.mp3");

	//g_IronDamage = LoadSoundMem("bgm,se/Player_SE/iron_damage.mp3");
	g_IronSlide = LoadSoundMem("bgm,se/Player_SE/iron_slide.mp3");
	g_IronSwing = LoadSoundMem("bgm,se/Player_SE/iron_swing.mp3");
	//g_Landing = LoadSoundMem("bgm,se/Player_SE/landing.mp3"); // �g��Ȃ�����
	g_Player_Damage = LoadSoundMem("bgm,se/Player_SE/player_damage.mp3");
	g_Player_Jump = LoadSoundMem("bgm,se/Player_SE/player_jump.mp3");
	g_Sword_Damage = LoadSoundMem("bgm,se/Player_SE/sword_damage.mp3");
	g_Sword_Swing = LoadSoundMem("bgm,se/Player_SE/sword_swing.mp3");

	g_Cursor = LoadSoundMem("bgm,se/Player_SE/cursor-01.wav");
	g_Cursor2 = LoadSoundMem("bgm,se/Player_SE/cursor-01.wav");

	return 0;
}