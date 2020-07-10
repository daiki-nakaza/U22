#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"

#include "PlayerAndIronBall.h"
#include "IronToEnemy.h"


/**************************************************
*		�ϐ��̐錾
***************************************************/
enemyInfo g_Enemy[ENEMY_MAX];			//�G�̏����������ϐ�
  


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

	AttckFlg = false;

	speed = 2;						//�G�̃X�s�[�h

	Life = 3;					//�G��HP�@�Ƃ�܂R

	type = 0;					//�G�̃^�C�v

	outtime = 0;				//�P�x�U������������疳�G


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
	w = SHOOT_ENEMY_SIZE;						//�G�̉���
	h = SHOOT_ENEMY_SIZE;						//�G�̏c

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, SHOOT_ENEMY_SIZE, SHOOT_ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//����������n�߂�

	speed = 0;						//�G�̃X�s�[�h
	picDir = true;

	Life = 3;					//�G��HP�@�Ƃ�܂R

	type = 1;					//�G�̃^�C�v

	AttckFlg = false;			//�U���p�̃t���O

	pic = LoadGraph("images/teki.png");

	DispFlg = TRUE;					//�G��\��


}


void enemyInfo::ShootMove() {		//���G�̏���

	static int AnmCnt = 0;
	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�

	const int Rate = 20;		//���˃��[�g
	const int ReloadTime = 180;			//�����[�h���ԁ@��̂R�b


	static int Firecnt = 0;		 //���˂̃J�E���g
	static int BulletCnt = 0;		//�R���A���Œe�𔭎˂�����
	static int ReloadCnt = 0;		//�����[�h�̎��ԃJ�E���g


	if (DispFlg) {//
		if (g_MapChip[(y + h) / MAP_SIZE][x / MAP_SIZE] == 1) {			//�����̑��������ċ󒆂�������
			y += GRAVITY;
		}
		else {
			AttckFlg = true;
		}

		//if(DirCheck)

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�



		if (++AnmCnt >= FrmMax) {				//�A�j���[�V�����t���[��
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}
		if (AttckFlg) {
			if (Firecnt++ >= Rate
				&& BulletCnt < Bullet_MAX) {
				Bullet[BulletCnt].Init(x, y + h / 2);			//�e���΂��Ԋu
				BulletCnt++;
				Firecnt = 0;
			}

			if (!Bullet[0].DispFlg
				&& !Bullet[1].DispFlg
				&& !Bullet[2].DispFlg
				&& ReloadCnt > ReloadTime) {
				BulletCnt = 0;		//�e�̕\���t���O�����ׂ�off�Ȃ猂�Ă�悤�ɂȂ�
				ReloadCnt = 0;
			}
			if (ReloadCnt++ <= ReloadTime) {}
		}
		for (int i = 0; i < Bullet_MAX; i++) {
			Bullet[i].Disp();
			Bullet[i].Move(direct);
			if (IronToEnemy(Bullet[i])) {
				Bullet[i].DispFlg = false;		//�S���ɓ������Ă�����Ƃ�܏���
			}
		}

	}
	else {
		for (int i = 0; i < Bullet_MAX; i++) {
			Bullet[i].DispFlg = false;
		}
	}



	

}

void enemyInfo::Disp() {			//�G�̕\������

	if (DispFlg) {		//�G�\��
		//DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,	// + MapDrawPointX - MapX * MAP_SIZE
		//	x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0xff0000, true);
		//DrawRotaGraphFast2(x, y,0,0,1,0, pic[anm], true,picDir);
		DrawGraph(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE, pic, true);
	}
	else {				//�G��\��

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
		g_Enemy[0].ShootInit();
		//g_Enemy[0].WalkInit();

		Initflg = false;
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		switch (g_Enemy[i].type)
		{
		case 0:
			g_Enemy[i].WalkMove();
			break;
		case 1:
			g_Enemy[i].ShootMove();
			break;
		}

		if (g_Enemy[0].DispFlg)DrawFormatString(30, 60, 0x000000, "�U�����Ă܂�", true);

		if (EnemyCheckHit(g_Enemy[i])
			|| IronToEnemy(g_Enemy[i]) ) {	//�ǂ�������
			g_Enemy[i].direct *= -1;			//�ړ��̌����𔽓]������
		}

		/******************************************************
		*����ɏ����܂���
		******************************************************/
		if (--g_Enemy[i].outtime < 0) {
			g_Enemy[i].outtime = 0;
		}
		if (g_Enemy[i].Life <= 0) {
			g_Enemy[i].DispFlg = false;
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

	return false;
}

