#pragma once

#include "DxLib.h"
#include "Define.h"

#include "Player.h"
#include "accessory.h"

/****************************************
*		�֐��̃v���g�^�C�v�錾
******************************************/
void IronInit(int* ironX, int* ironY, int px = PlayerX, int py = PlayerY);		//�S���̏���������
void IronHold(int* ironX, int* ironY, int px = PlayerX, int py = PlayerY);		//�S���������Ă���Ƃ��̓S�����̏���
void IronHoldOrThrow();			
												//�v���C���[���S�������������鏈��
bool IronToEnemy();