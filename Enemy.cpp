#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"

#include "PlayerAndIronBall.h"
#include "IronToEnemy.h"


/**************************************************
*		�ϐ��̐錾
***************************************************/
//�G���[�h�~�p�i��ŏ����܂��j
enemyInfo g_Enemy[ENEMY_MAX];

WalkEnemy g_WalkEnemy[ENEMY_MAX];					//�����G
ShootEnemy g_ShootEnemy[ENEMY_MAX];					//�^���������G
LockShootEnemy g_LockShootEnemy[ENEMY_MAX];			//�_�����G
TankEnemy g_TankEnemy[ENEMY_MAX];					//��Ԃ̓G
RazerEnemy g_RazerEnemy[ENEMY_MAX];					//�g���C�̓G

  


/***************************************************
*�@�@�G�̍\���̂̊֐��̒�`
*****************************************************/

void enemyInfo::Move() {
	/******************************************************
		*����ɏ����܂���
		******************************************************/
	if (outtime < 0) {
		outtime = 0;
	}
	if (Life <= 0) {
		DispFlg = false;
	}
	if (g_MapChip[(y + h) / MAP_SIZE][x / MAP_SIZE] == 1) {			//�����̑��������ċ󒆂�������
		y += GRAVITY;
	}
}

void enemyInfo::Disp() {			//�G�̕\������

	if (DispFlg) {		//�G�\��
		//DrawBox(x + MapDrawPointX - MapX * MAP_SIZE,
		//	y - MapDrawPointY - MapY * MAP_SIZE,
		//	(x + MapDrawPointX - MapX * MAP_SIZE) + w,
		//	(y - MapDrawPointY - MapY * MAP_SIZE) + h, 0x000000, true);
		DrawGraph(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE, pic, true);
	}
	else {				//�G��\��

	}
}



//////////////////////////////////////////////
/////////////�����G�̏���////////////////////
/////////////////////////////////////////////

void WalkEnemy::Init() {                 // �G�̏�����
	x = 24 * MAP_SIZE;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = 14 * MAP_SIZE;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	w = WALK_ENEMY_SIZE;						//�G�̉���
	h = WALK_ENEMY_SIZE;						//�G�̏c

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, WALK_ENEMY_SIZE, WALK_ENEMY_SIZE, pic);
	pic = LoadGraph("images/Zako.png");

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


void WalkEnemy::WalkMove(){

	static int AnmCnt = 0;

	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�



	if (DispFlg) {//
		

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�

		//x = (chipX * MAP_SIZE - MapDrawPointX) + direct * speed;				//�ړ��̃X�s�[�h��G�L�����ɓ����
		x += direct * speed;

		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}
		Move();			//�G���ʂ̊֐�

	}

}



////////////////////////////////////////////
//////////���G�̏���//////////////////////
/////////////////////////////////////////////

void ShootEnemy::Init() {                 // ���G�̏�����
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


void ShootEnemy::ShootMove() {		//���G�̏���

	static int AnmCnt = 0;
	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�

	const int Rate = 20;		//���˃��[�g
	const int ReloadTime = 180;			//�����[�h���ԁ@��̂R�b


	static int Firecnt = 0;		 //���˂̃J�E���g
	static int BulletCnt = 0;		//�R���A���Œe�𔭎˂�����
	static int ReloadCnt = 0;		//�����[�h�̎��ԃJ�E���g


	if (DispFlg) {//

		//if(DirCheck)

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�



		if (++AnmCnt >= FrmMax) {				//�A�j���[�V�����t���[��
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}
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

		for (int i = 0; i < Bullet_MAX; i++) {
			Bullet[i].Disp();
			Bullet[i].Move(direct);			//�e�ۂ̏���
			if (IronToBullet(Bullet[i])) {
				Bullet[i].DispFlg = false;		//�S���ɓ������Ă�����Ƃ�܏���
			}
			if (PlayerToEnemy(Bullet[i])) {
				Bullet[i].DispFlg = false;		//�S���ɓ������Ă�����Ƃ�܏���
			}
		}

		Move();			//�G���ʂ̊֐�

	}


}


////////////////////////////////////////////
//////////�_�����G�̏���//////////////////////
/////////////////////////////////////////////

//�_�����G�̏�����
void LockShootEnemy::Init() {
	x = 15 * MAP_SIZE;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = 8 * MAP_SIZE;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	w = SHOOT_ENEMY_SIZE;						//�G�̉���
	h = SHOOT_ENEMY_SIZE;						//�G�̏c

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


void LockShootEnemy::LockShootMove() {			//���G�̏���


	static int AnmCnt = 0;
	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�

	const int Rate = 20;		//���˃��[�g
	const int ReloadTime = 180;			//�����[�h���ԁ@��̂R�b


	static int Firecnt = 0;		 //���˂̃J�E���g
	static int BulletCnt = 0;		//�R���A���Œe�𔭎˂�����
	static int ReloadCnt = 0;		//�����[�h�̎��ԃJ�E���g


	if (DispFlg) {//

		//if(DirCheck)

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�



		if (++AnmCnt >= FrmMax) {				//�A�j���[�V�����t���[��
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}
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

		for (int i = 0; i < Bullet_MAX; i++) {
			Bullet[i].Disp();
			Bullet[i].Move(direct);			//�e�ۂ̏���
			if (IronToBullet(Bullet[i])) {
				Bullet[i].DispFlg = false;		//�S���ɓ������Ă�����Ƃ�܏���
			}
			if (PlayerToEnemy(Bullet[i])) {
				Bullet[i].DispFlg = false;		//�S���ɓ������Ă�����Ƃ�܏���
			}
		}

		Move();			//�G���ʂ̊֐�

	}

}

//��Ԃ̓G(��Ɍ������Ēe���΂��z)
void TankEnemy::Init() {
	x = 15 * MAP_SIZE;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = 8 * MAP_SIZE;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	w = TANK_ENEMY_SIZE;						//�G�̉���
	h = TANK_ENEMY_SIZE;						//�G�̏c��

	anm = 0;

	direct = -1;						//����������n�߂�

	speed = 0;						//�G�̃X�s�[�h
	picDir = true;

	Life = 3;					//�G��HP�@�Ƃ�܂R

	type = 1;					//�G�̃^�C�v

	AttckFlg = false;			//�U���p�̃t���O

	pic = LoadGraph("images/Enemy.Tank.png");

	DispFlg = TRUE;					//�G��\��


}

void TankEnemy::TankMove() {


	static int AnmCnt = 0;
	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�

	const int Rate = 40;		//���˃��[�g
	const int ReloadTime = 240;			//�����[�h���ԁ@


	static int Firecnt = 0;		 //���˂̃J�E���g
	static int BulletCnt = 0;		//�R���A���Œe�𔭎˂�����
	static int ReloadCnt = 0;		//�����[�h�̎��ԃJ�E���g


	if (DispFlg) {//

		//if(DirCheck)

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�



		if (++AnmCnt >= FrmMax) {				//�A�j���[�V�����t���[��
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}
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

		for (int i = 0; i < Bullet_MAX; i++) {
			Bullet[i].Disp();
			Bullet[i].Move(direct);			//�e�ۂ̏���
			if (IronToBullet(Bullet[i])) {
				Bullet[i].DispFlg = false;		//�S���ɓ������Ă�����Ƃ�܏���
			}
			if (PlayerToEnemy(Bullet[i])) {
				Bullet[i].DispFlg = false;		//�S���ɓ������Ă�����Ƃ�܏���
			}
		}

		Move();			//�G���ʂ̊֐�

	}
}

//�g���C�����G�̊֐���`
void RazerEnemy::Init(){
	x = 15 * MAP_SIZE;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = 8 * MAP_SIZE;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	w = TANK_ENEMY_SIZE;						//�G�̉���
	h = TANK_ENEMY_SIZE;						//�G�̏c��

	anm = 0;

	direct = -1;						//����������n�߂�

	speed = 0;						//�G�̃X�s�[�h
	picDir = true;

	Life = 3;					//�G��HP�@�Ƃ�܂R

	type = 1;					//�G�̃^�C�v

	AttckFlg = false;			//�U���p�̃t���O

	LoadDivGraph("images/HadouhouAll.png",3,3,1, TANK_ENEMY_SIZE, TANK_ENEMY_SIZE,pic);

	//pic[2] = LoadGraph("images/Hadouhou2.png");

	DispFlg = TRUE;					//�G��\��

}

void RazerEnemy::ShotMove() {

	static int AnmCnt = 0;

	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�



	if (DispFlg) {//


		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}
		Move();			//�G���ʂ̊֐�

	}
}

void RazerEnemy::Disp() {

	if (DispFlg) {		//�G�\��
		//DrawBox(x + MapDrawPointX - MapX * MAP_SIZE,
		//	y - MapDrawPointY - MapY * MAP_SIZE,
		//	(x + MapDrawPointX - MapX * MAP_SIZE) + w,
		//	(y - MapDrawPointY - MapY * MAP_SIZE) + h, 0x000000, true);
		DrawGraph(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE, pic[2], true);
	}
	else {				//�G��\��

	}
}
/**************************************************
*�@�G�̊֐��̒�`
***************************************************/

void enemyInit() {			//�G�̏���������

		//g_LockShootEnemy[0].Init();

}

void enemyDisp() {

	for (int i = 0; i < ENEMY_MAX; i++) {
		g_WalkEnemy[i].Disp();
		g_ShootEnemy[i].Disp();
		g_LockShootEnemy[i].Disp();
		g_TankEnemy[i].Disp();
		g_RazerEnemy[i].Disp();
	}
	
	//EnemyShoot();
}




void enemyMove() {
	static bool Initflg = true;

	if (Initflg) {
		g_RazerEnemy[0].Init();
		Initflg = false;
	}


	for (int i = 0; i < ENEMY_MAX; i++) {

		g_WalkEnemy[i].WalkMove();
		g_ShootEnemy[i].ShootMove();
		g_LockShootEnemy[i].LockShootMove();
		g_TankEnemy[i].TankMove();
		g_RazerEnemy[i].ShotMove();

		
	}	
}

bool EnemyCheckHit(WalkEnemy enemy) {
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

