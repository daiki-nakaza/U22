#pragma once

#include "DxLib.h"

/*****************************************************************
*   �ϐ��̐錾
*****************************************************************/

extern bool DebugMode;//�f�o�b�N�p		true�F�f�o�b�N��			false�F��o�p

//�v���C���[�̈ʒu
extern int PlayerX, PlayerY;              //0�`��ʔ����܂ŁB�i�v���C���[�ʒu�j
extern int Map_PlayerX, Map_PlayerY;      //�}�b�v�S�̂̃X�N���[���ʒu�i�}�b�v�ʒu�j
extern int MapX, MapY;                    //�}�b�v�̂��A��
extern int NewX, NewY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�
extern int Map_NewX, Map_NewY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�

extern int Bectl;		//�v���C���[�̌���
extern int Attack;		//�v���C���[�̍U���p

extern int Jump_Flg;  //�W�����v�p�ϐ� 8�������̂��T��J��Ԃ�
extern int y_temp;
extern int y_prev;
extern int PlayerLife;		//�v���C���[�̃��C�t
extern int Playerouttime;

extern int y_prev;//���Ⴊ�݂̃t���O


extern int g_OldKey;
extern int g_NowKey;
extern int g_KeyFlg;
extern int g_OldKey2;
extern int g_NowKey2;
extern int g_KeyFlg2;
extern int g_MouseX;  //�}�E�X�����W
extern int g_MouseY;  //�}�E�X�����W

extern int g_GameState;  //�Q�[�����[�h


extern int ClearTime;  //�N���A����p�ϐ�



extern int Player_Pic[4];//�v���C���[�ړ��̉摜
extern int Player_Pic_R[4];//�t�v���C���[�ړ��̉摜

extern int Player_Pic_Attack[6];//�v���C���[�ړ��̉摜
extern int Player_Pic_Attack_R[6];//�t�v���C���[�ړ��̉摜

extern int Player_Pic_Down;//�v���C���[���Ⴊ�݂̉摜
extern int Player_Pic_Down_R;//�t�v���C���[���Ⴊ�݂̉摜

extern int Player_Pic_Hold[4];//�v���C���[���S���������Ĉړ�����摜
extern int Player_Pic_Hold_R[4];//�t�v���C���[���S���������Ĉړ�����摜

extern int Player_HP[8];//�v���C���[HP�̉摜

//extern int g_IronDamage;	  // �S�����G�ɓ�������SE�i�[�ϐ�
extern int g_IronSlide;		  // �S������������SE�i�[�ϐ�
extern int g_IronSwing;		  // �S���𓊂���SE�i�[�ϐ�
extern int g_Landing;		  // �v���C���[���n�ʂɒ��n��������SE�i�[�ϐ�
extern int g_Player_Damage;   // �v���C���[����e�����Ƃ���SE�i�[�ϐ�
extern int g_Player_Jump;	  // �W�����vSE�i�[�ϐ�
extern int g_Sword_Damage;    // ���œG��؂���SE�i�[�ϐ�
extern int g_Sword_Swing;	  // ����U��SE�i�[�ϐ�


/***************************************************************************
*          �֐��̃v���g�^�C�v�錾  
********************************************************************************/

void PlayerInit();
void PlayerMove();
void PlayerDisp();
void PlayerGravity(int bn);
void PlayerAttack();
void PlayerDamage();
