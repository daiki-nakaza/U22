#pragma once

#include "DxLib.h"

/*****************************************************************
*   �ϐ��̐錾
*****************************************************************/

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


extern int g_OldKey;
extern int g_NowKey;
extern int g_KeyFlg;
extern int g_OldKey2;
extern int g_NowKey2;
extern int g_KeyFlg2;
extern int g_MouseX;  //�}�E�X�����W
extern int g_MouseY;  //�}�E�X�����W

extern int Player_Pic[4];//�v���C���[�ړ��̉摜
extern int Player_Pic_R[4];//�t�v���C���[�ړ��̉摜

extern int Player_Pic_Attack[6];//�v���C���[�ړ��̉摜
extern int Player_Pic_Attack_R[6];//�t�v���C���[�ړ��̉摜



/***************************************************************************
*          �֐��̃v���g�^�C�v�錾  
********************************************************************************/

void PlayerInit();
void PlayerMove();
void PlayerDisp();
void PlayerGravity();
void PlayerAttack();