#include "DxLib.h"

#include "Player.h"


//�v���C���[�̈ʒu
int PlayerX, PlayerY;              //0�`��ʔ����܂ŁB�i�v���C���[�ʒu�j
int Map_PlayerX, Map_PlayerY;      //�}�b�v�S�̂̃X�N���[���ʒu�i�}�b�v�ʒu�j
int OldX, OldY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�
int Map_OldX, Map_OldY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�

void PlayerInit() {

	// �v���C���[�̏����ʒu���Z�b�g
	PlayerX = 200;
	PlayerY = 200;
	Map_PlayerX = 0;
	Map_PlayerY = 0;

}