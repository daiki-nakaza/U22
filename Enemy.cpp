#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"

/**************************************************
*		�ϐ��̐錾
***************************************************/
enemyInfo g_Enemy;			//�G�̏����������ϐ�


/***************************************************
*�@�@�G�̍\���̂̊֐��̒�`
*****************************************************/
void enemyInfo::WalkInit() {                 // �G�̏�����
	x = 24 * MAP_SIZE;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = 15 * MAP_SIZE;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	w = MAP_SIZE;						//�G�̉���
	h = MAP_SIZE;						//�G�̏c��

	direct = -1;						//����������n�߂�

	speed = 4;						//�G�̃X�s�[�h

	DispFlg = TRUE;					//�G��\��
}

void enemyInfo::Disp() {
	if (DispFlg) {		//�G�\��
		DrawBox(x, y, x + w, y + h, 0x000000, true);
	}
	else {				//�G��\��

	}
}

void enemyInfo::WalkMove(){

	if (DispFlg) {
		if (EnemyCheckHit(g_Enemy)) {	//���̃t���[���̈ړ�������ĕǂ�������
			direct *= -1;			//�ړ��̌����𔽓]������
		}

		if (g_MapChip[(y / MAP_SIZE) + 1][(x / MAP_SIZE)]) {			//�P���̃}�X�����ċ󒆂�������
			g_Enemy.y += 4;
		}

		x += direct * speed;				//�ړ��̃X�s�[�h��G�L�����ɓ����

	}

}

/**************************************************
*�@�G�̊֐��̒�`
***************************************************/
void enemyDisp() {
	g_Enemy.Disp();
}

void enemyMove() {
	static int Initflg = true;

	if (Initflg) {
		g_Enemy.WalkInit();

		Initflg = false;
	}
	if (g_Enemy.DispFlg) {
		g_Enemy.WalkMove();
	}
}

bool EnemyCheckHit(enemyInfo enemy) {
	if (enemy.direct == 1)			//�E�����̏���
	{
		if (g_MapChip[enemy.y / MAP_SIZE][(enemy.x / MAP_SIZE) + enemy.direct] == 0) return TRUE;
	}else{							//�������̏���
		if (g_MapChip[enemy.y / MAP_SIZE][( (enemy.x + (enemy.direct * enemy.speed)) / MAP_SIZE) ] == 0) return TRUE;
	}

	return FALSE;
}