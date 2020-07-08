#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"

#include "PlayerAndIronBall.h"
#include "IronToEnemy.h"

#define WALK_ENEMY_SIZE 48	//�G�̑傫��
#define SHOOT_ENEMY_SIZE 64
#define ENEMY_MAX 10
#define  Bullet_MAX 3

/**************************************************
*		�ϐ��̐錾
***************************************************/
enemyInfo g_Enemy[ENEMY_MAX];			//�G�̏����������ϐ�
BulletInfo Bullet;			//�e�ۂ�MAX�̐��Ԃ�z������
  


/***************************************************
*�@�@�G�̍\���̂̊֐��̒�`
*****************************************************/

//////////////////////////////////////////////
/////////////�����G�̏���////////////////////
/////////////////////////////////////////////

void enemyInfo::WalkInit() {                 // �G�̏�����
	x = 24 * MAP_SIZE;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = 14 * MAP_SIZE;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	w = WALK_ENEMY_SIZE;						//�G�̉���
	h = WALK_ENEMY_SIZE;						//�G�̏c

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, WALK_ENEMY_SIZE, WALK_ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//����������n�߂�
	picDir = true;

	speed = 2;						//�G�̃X�s�[�h

	Life = 3;					//�G��HP�@�Ƃ�܂R


	DispFlg = TRUE;					//�G��\��


}


void enemyInfo::WalkMove(){

	static int AnmCnt = 0;

	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�



	if (DispFlg) {//
		
		if (g_MapChip[(y + h) / MAP_SIZE][x / MAP_SIZE] == 1) {			//�����̑��������ċ󒆂�������
			y += GRAVITY;
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



////////////////////////////////////////////
//////////���G�̏���//////////////////////
/////////////////////////////////////////////

void enemyInfo::ShootInit() {                 // ���G�̏�����
	x = 24 * MAP_SIZE;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = 15 * MAP_SIZE;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	w = SHOOT_ENEMY_SIZE / 2;						//�G�̉���
	h = SHOOT_ENEMY_SIZE;						//�G�̏c

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, SHOOT_ENEMY_SIZE, SHOOT_ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//����������n�߂�

	speed = 0;						//�G�̃X�s�[�h
	picDir = true;

	DispFlg = TRUE;					//�G��\��


}


void enemyInfo::ShootMove() {		//���G�̏���

	static int AnmCnt = 0;
	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�



	if (DispFlg) {//
		if (g_MapChip[(y + h) / MAP_SIZE][x / MAP_SIZE] == 1) {			//�����̑��������ċ󒆂�������
			y += GRAVITY;
		}

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�


		//EnemyShoot();

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
}

//////////////////////////////////////////////
////////////�e�ۂ̊֐��̒�`///////////////////
//////////////////////////////////////////////
void BulletInfo::Init() {			//�e�ۂ̏���������
	//x = g_Enemy.x;
	//y = g_Enemy.y + (g_Enemy.h / 2);		//�G�̐^�񒆂��炢�̍�������

	Speed = 4;							//�e�ۂ̃X�s�[�h


	DispFlg = true;			//�\���t���O���I���ɂ���
}

void BulletInfo::Move() {			//�e�ۂ̏���
	if (DispFlg) {
		x += direct * Speed;

		if (x < 0 || x > WIDTH) DispFlg = false;
	}
	else {

	}
}

void BulletInfo::Disp() {			//�e�ۂ̕\������
	if (DispFlg) {
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0xff0000, true);
	}
}


/**************************************************
*�@�G�̊֐��̒�`
***************************************************/
void enemyDisp() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_Enemy[i].Disp();
	}
	
	

	//EnemyShoot();
}

void enemyMove() {
	static int Initflg = true;

	if (Initflg) {
		//g_Enemy.ShootInit();
		g_Enemy[0].WalkInit();

		Initflg = false;
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		g_Enemy[i].WalkMove();

		if (EnemyCheckHit(g_Enemy[i])) {	//�ǂ�������
			g_Enemy[i].direct *= -1;			//�ړ��̌����𔽓]������
		}
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
	if (IronToEnemy(enemy)) return true;

	return false;
}

//�G���e�ۂ��΂�����
//void EnemyShoot() {
//
//	if (g_NowKey & PAD_INPUT_DOWN
//		&& !Bullet->DispFlg) {
//		Bullet->Init();
//	}
//
//	if (Bullet->DispFlg) {
//		Bullet->Move();
//	}
//	else {
//
//	}
//
//}