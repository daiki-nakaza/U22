#pragma once

#include "DxLib.h"

#include "Define.h"

/*************************************************************
*�@�@�֐��̃v���g�^�C�v�錾
**************************************************************/

void MapDisp();
void MapMove();
void MapChipInit();


/*�@�ϐ��̐錾�@*/
//int g_MapChip[HEIGHT * 2][WIDTH];

extern int MapDrawPointX, MapDrawPointY;		// �O�`31�@�ʂ�ʂ铮���悤
extern int MapChipNumX, MapChipNumY;			//�E�g��p�ϐ� 0,32,64::0,22,44
extern int MapX, MapY;                    //�}�b�v�̂��A��

extern int g_MapChip[HEIGHT * MAP_LONG][WIDTH];

extern int MapTip;	//�}�b�v�`�b�v�摜�ϐ�
extern int g_BackGroundImage1;//�w�i�摜
extern int g_BackGroundImage2;//�w�i�摜
extern int g_BackGroundImage3;//�w�i�摜
extern int g_Door[3];//�N���A�p�̃h�A�摜

extern int Stage;//�X�e�[�W�ϐ�




extern int g_Stage1; // �X�e�[�W1�̋Ȋi�[�ϐ�
extern int g_Stage2; // �X�e�[�W2�̋Ȋi�[�ϐ�
extern int g_Stage3; // �X�e�[�W3�̋Ȋi�[�ϐ�
extern int g_Title;  // �^�C�g��bgm
extern int g_GameOver; // �Q�[���I�[�o�[
extern int g_BossSound;	 // �{�X��̋Ȋi�[�ϐ�

// ���G�̌��ʉ����� //
extern int g_ColorL; // 2�F�̒e���󒆂ɑł��グ��SE�i�[�ϐ�
extern int g_Hadou;  // �g���C��SE�i�[�ϐ�
extern int g_Kakusan;// �g�U�e��SE�i�[�ϐ�
extern int g_Shot;   // �ʏ�e��SE�i�[�ϐ�(�{�X�ƎG���G)
extern int g_Warp;   // �{�X�̃��[�vSE�i�[�ϐ�
extern int g_Sword_Damage;    // ���œG��؂���SE�i�[�ϐ�

extern int g_Cursor;
extern int g_Cursor2; // �Q�[���G���h