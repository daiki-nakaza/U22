#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"

#include "PlayerAndIronBall.h"

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
	y = 14 * MAP_SIZE;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	w = ENEMY_SIZE;						//�G�̉���
	h = ENEMY_SIZE;						//�G�̏c

	LoadDivGraph("images/MouseAll.png", 4, 4, 1, ENEMY_SIZE, ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//����������n�߂�

	speed = 2;						//�G�̃X�s�[�h
	picDir = true;

	chipY = ((y + MapDrawPointY) / MAP_SIZE) + MapY;
	chipX = ((x - MapDrawPointX) / MAP_SIZE) + MapX;

	DispFlg = TRUE;					//�G��\��


}


void enemyInfo::WalkMove(){

	static int AnmCnt = 0;

	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�



	if (DispFlg) {//
		if (g_MapChip[(y + h) / MAP_SIZE][x / MAP_SIZE] == 1) {			//�P���̃}�X�����ċ󒆂�������
			g_Enemy.y += GRAVITY;
		}

		if (EnemyCheckHit(g_Enemy)) {	//�ǂ�������
			direct *= -1;			//�ړ��̌����𔽓]������
		}

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�

		//x = (chipX * MAP_SIZE - MapDrawPointX) + direct * speed;				//�ړ��̃X�s�[�h��G�L�����ɓ����
		x += direct * speed;

		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}

		chipY = ((y + MapDrawPointY) / MAP_SIZE) + MapY;
		chipX = ((x - MapDrawPointX) / MAP_SIZE) + MapX;

	}

}

void enemyInfo::ShootInit() {                 // ���G�̏�����
	x = 24 * MAP_SIZE;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = 15 * MAP_SIZE;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	w = ENEMY_SIZE;						//�G�̉���
	h = ENEMY_SIZE;						//�G�̏c

	LoadDivGraph("images/MouseAll.png", 4, 4, 1, ENEMY_SIZE, ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//����������n�߂�

	speed = 0;						//�G�̃X�s�[�h
	picDir = true;

	chipY = ((y + MapDrawPointY) / MAP_SIZE) + MapY;
	chipX = ((x - MapDrawPointX) / MAP_SIZE) + MapX;

	DispFlg = TRUE;					//�G��\��


}


void enemyInfo::ShootMove() {		//���G�̏���

	static int AnmCnt = 0;

	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�



	if (DispFlg) {
		//if (EnemyCheckHit) {			//�P���̃}�X�����ċ󒆂�������
		//	g_Enemy.y += GRAVITY;
		//}

		if (EnemyCheckHit(g_Enemy)) {	//���̃t���[���̈ړ�������ĕǂ�������
			direct *= -1;			//�ړ��̌����𔽓]������
		}

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�

		//x = (chipX * MAP_SIZE - MapDrawPointX) + direct * speed;				//�ړ��̃X�s�[�h��G�L�����ɓ����
		x += direct * speed;

		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}


	}

}

void enemyInfo::Disp() {			//�G�̕\������

	if (DispFlg) {		//�G�\��
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,	// + MapDrawPointX - MapX * MAP_SIZE
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0xff0000, true);
		//DrawRotaGraphFast2(x, y,0,0,1,0, pic[anm], true,picDir);
	}
	else {				//�G��\��

	}
	/*for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH + 1; x++) {
			DrawFormatString(x * MAP_SIZE + 16, y * MAP_SIZE + 16, 0xf0f0f0, "%d", g_MapChip[y + MapY + MapChipNumY][x + MapX + MapChipNumX]);
		}
	}*/
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
	int i = 0, j = 0, k = 0, l = 0, w = 0, z = 0;		//�␳�l�p�ϐ�
	//�I�̈ʒu�i���j���}�b�v���܂����ł���
	while (enemy.x / MAP_SIZE - k >= WIDTH) {
		k += WIDTH;
		l += HEIGHT;
	}

	//�G�̈ʒu(�E)���}�b�v���܂����ł���
	if ((enemy.x + enemy.h) / MAP_SIZE - k >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//�^�񒆂̈ʒu���}�b�v���܂����ł���
	if ((enemy.x + enemy.h / 2) / MAP_SIZE - k >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}


	if (enemy.picDir)			//�E�����̏���
	{
		if (g_MapChip[(enemy.y) / MAP_SIZE + l + j][(enemy.x + enemy.w) / MAP_SIZE - k - w] != 1	//�E��
			|| g_MapChip[(enemy.y +( enemy.h /2) ) / MAP_SIZE + l + j][(enemy.x + enemy.w) / MAP_SIZE - k - w] != 1)	//�E��
			 {return true;}
	}
	else {
		if (g_MapChip[(enemy.y) / MAP_SIZE + l][(enemy.x) / MAP_SIZE - k] != 1				//����
			|| g_MapChip[(enemy.y +( enemy.h / 2) ) / MAP_SIZE + l][(enemy.x) / MAP_SIZE - k] != 1)	//����
		{return true;}

	}
	//if (IronToEnemy()) return true;

	return false;
}