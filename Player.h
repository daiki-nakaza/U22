#pragma once

#include "DxLib.h"

/*****************************************************************
*   �ϐ��̐錾
*****************************************************************/

//�v���C���[�̈ʒu
extern int PlayerX, PlayerY;              //0�`��ʔ����܂ŁB�i�v���C���[�ʒu�j
extern int Map_PlayerX, Map_PlayerY;      //�}�b�v�S�̂̃X�N���[���ʒu�i�}�b�v�ʒu�j
extern int MapX, MapY;                    //�}�b�v�̂��A��
extern int OldX, OldY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�
extern int Map_OldX, Map_OldY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�


extern int g_OldKey;
extern int g_NowKey;
extern int g_KeyFlg;
extern int g_OldKey2;
extern int g_NowKey2;
extern int g_KeyFlg2;
extern int g_MouseX;//�}�E�X�����W
extern int g_MouseY;//�}�E�X�����W


/***************************************************************************
*          �֐��̃v���g�^�C�v�錾  
********************************************************************************/

void PlayerInit();
void PlayerMove();
void PlayerDisp();
void PlayerGravity();
