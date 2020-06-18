#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"

#define ENEMY_SIZE 48	//�G�̑傫��

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
	w = ENEMY_SIZE;						//�G�̉���
	h = ENEMY_SIZE;						//�G�̏c

	LoadDivGraph("images/MouseAll.png", 4, 4, 1, ENEMY_SIZE, ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//����������n�߂�

	speed = 4;						//�G�̃X�s�[�h
	picDir = true;

	DispFlg = TRUE;					//�G��\��


}

void enemyInfo::Disp() {
	int DispX, DispY;

	DispX = x - MapDrawPointX;
	DispY = y + MapDrawPointY;

	if (DispFlg) {		//�G�\��
		DrawBox(x,y, x + w, y + h, 0x000000, true);
		DrawRotaGraphFast2(x, y,0,0,1,0, pic[anm], true,picDir);
	}
	else {				//�G��\��

	}
}

void enemyInfo::WalkMove(){

	static int AnmCnt = 0;
	static int FrmMax = 15;

	if (DispFlg) {
		if (g_MapChip[(y / MAP_SIZE + MapY) + 1][(x / MAP_SIZE + MapX)]) {			//�P���̃}�X�����ċ󒆂�������
			g_Enemy.y += GRAVITY;
		}

		if (EnemyCheckHit(g_Enemy)) {	//���̃t���[���̈ړ�������ĕǂ�������
			direct *= -1;			//�ړ��̌����𔽓]������
		}
		if (direct < 0) { picDir = false; }
		else { picDir = true; }
		x += direct * speed;				//�ړ��̃X�s�[�h��G�L�����ɓ����

		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}

	}

}

/**************************************************
*�@�G�̊֐��̒�`
***************************************************/
void enemyDisp() {
	g_Enemy.Disp();
	DrawFormatString(200, 100, 0x000000, "%d",g_Enemy.x / MAP_SIZE + MapX);
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
		//���̈ړ��̏ꏊ���G�L�����̉E�[�ɕǂ��d�Ȃ�����X�s�[�h�𔽓]����
		if 
			(g_MapChip[(enemy.y + MapDrawPointY) / MAP_SIZE + MapY]
			[(((enemy.x + enemy.w - MapDrawPointX)+(enemy.direct * enemy.speed)) / MAP_SIZE) + MapX] == 0) return true;
	}
	else {							//�������̏���
		if
			(g_MapChip[(enemy.y + MapDrawPointY) / MAP_SIZE + MapY]
			[((enemy.x - MapDrawPointX + (enemy.direct * enemy.speed)) / MAP_SIZE) + MapX] == 0) return TRUE;
	}
	return false;
}