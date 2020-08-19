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

// ���G�̌��ʉ����� //
int g_ColorL;
int g_Hadou;  // �g���C��SE�i�[�ϐ�
int g_Kakusan;// �g�U�e��SE�i�[�ϐ�
int g_Shot;   // �ʏ�e��SE�i�[�ϐ�(�{�X�ƎG���G)
int g_Warp;   // �{�X�̃��[�vSE�i�[�ϐ�


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
}

void enemyInfo::Disp() {			//�G�̕\������

	if (DispFlg) {		//�G�\��
		DrawGraph(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE, pic, true);
	}
	else {				//�G��\��

	}
}



//////////////////////////////////////////////
/////////////�����G�̏���////////////////////
/////////////////////////////////////////////

void WalkEnemy::Init(int Tempx, int Tempy) {                 // �G�̏�����
	int SetX = Tempx * MAP_SIZE + ( ( (Tempy / HEIGHT) * WIDTH) * WIDTH) , SetY = (Tempy % HEIGHT) * MAP_SIZE;


	x = SetX;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = SetY;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

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
		if (g_MapChip[y + 1][x] == 1) y += GRAVITY;

		if (direct < 0) picDir = true;		//�������Ȃ�
		else picDir = false;					//�E�����Ȃ�

		if (CheckWindow(x)) {
			x += direct * speed;
		}
		//x = (chipX * MAP_SIZE - MapDrawPointX) + direct * speed;				//�ړ��̃X�s�[�h��G�L�����ɓ����
		

		if (EnemyCheckHit(x,y,direct))direct *= -1;

		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}
		Move();			//�G���ʂ̊֐�

	}

}

void WalkEnemy::Disp() {
	if (DispFlg) {		//�G�\��
		DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w/2, y - MapDrawPointY - MapY * MAP_SIZE + h/2, 1, 0, pic,true, picDir);
	}
	else {				//�G��\��

	}
}

////////////////////////////////////////////
//////////���G�̏���//////////////////////
/////////////////////////////////////////////

void ShootEnemy::Init(int Tempx, int Tempy) {                 // ���G�̏�����
	int SetX = Tempx * MAP_SIZE + (((Tempy / HEIGHT) * WIDTH) * WIDTH), SetY = (Tempy % HEIGHT) * MAP_SIZE;


	x = SetX;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = SetY - (SHOOT_ENEMY_SIZE - MAP_SIZE);								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

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

		/*if (Firecnt++ > Rate) {
			Bullet[BulletCnt].Init(x , y + h / 2);
			Firecnt = 0;
			if (++BulletCnt >= 3
				&& !Bullet[0].DispFlg
				&& !Bullet[1].DispFlg
				&& !Bullet[2].DispFlg) {
				BulletCnt = 0;
			}
		}*/


		if (Firecnt++ >= Rate
			&& BulletCnt < Bullet_MAX
			&& !Bullet[BulletCnt].DispFlg) {
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
			//if (IronToBullet(Bullet[i])) {
			//	Bullet[i].DispFlg = false;		//�S���ɓ������Ă�����Ƃ�܏���
			//}
			//if (PlayerToEnemy(Bullet[i])) {
			//	Bullet[i].DispFlg = false;		//�S���ɓ������Ă�����Ƃ�܏���
			//}
		}

		Move();			//�G���ʂ̊֐�

	}


}


////////////////////////////////////////////
//////////�_�����G�̏���//////////////////////
/////////////////////////////////////////////

//�_�����G�̏�����
void LockShootEnemy::Init(int Tempx, int Tempy) {
	int SetX = Tempx * MAP_SIZE + (((Tempy / HEIGHT) * WIDTH) * WIDTH), SetY = (Tempy % HEIGHT) * MAP_SIZE;


	x = SetX;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = SetY;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

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
void TankEnemy::Init(int Tempx, int Tempy) {
	x = Tempx * MAP_SIZE;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = Tempy * MAP_SIZE;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

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

		}

		Move();			//�G���ʂ̊֐�

	}
}

//�g���C�����G�̊֐���`
void RazerEnemy::Init(int Tempx, int Tempy){
	x = Tempx * MAP_SIZE;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = Tempy * MAP_SIZE;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

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
	 
	for (int y = 0; y < HEIGHT * MAP_LONG; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (g_MapChip[y][x] == 3) {		//�����G��
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (g_WalkEnemy[i].DispFlg == false) {
						g_WalkEnemy[i].Init(x, y);
						g_MapChip[y][x] = 1;
						break;
					}
				}
			}
			else if (g_MapChip[y][x] == 4) {		//�^����������
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (!g_ShootEnemy[i].DispFlg) {
						g_ShootEnemy[i].Init(x, y);
						g_MapChip[y][x] = 1;
						break;
					}
				}
			}
			else if (g_MapChip[y][x] == 5) {		//���_�����
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (!g_LockShootEnemy[i].DispFlg) {
						g_LockShootEnemy[i].Init(x, y);
						g_MapChip[y][x] = 1;
						break;
					}
				}
			}
			else if (g_MapChip[y][x] == 6) {		//���
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (!g_TankEnemy[i].DispFlg) {
						g_TankEnemy[i].Init(x, y);
						g_MapChip[y][x] = 1;
						break;
					}
				}
			}
			else if (g_MapChip[y][x] == 7) {
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (!g_RazerEnemy[i].DispFlg) {
						g_RazerEnemy[i].Init(x, y);
						g_MapChip[y][x] = 1;
						break;
					}
				}
			}
		}
	}
	

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
		enemyInit();
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

bool EnemyCheckHit(int x, int y, int direct) {
	int i = 0, j = 0, k = 0, l = 0, w = 0, z = 0;		//�␳�l�p�ϐ�
	//�I�̈ʒu�i���j���}�b�v���܂����ł���
	while (x / MAP_SIZE - k >= WIDTH) {
		k += WIDTH;
		l += HEIGHT;
	}

	//�G�̈ʒu(�E)���}�b�v���܂����ł���
	if ((x + WALK_ENEMY_SIZE) / MAP_SIZE - k >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//�^�񒆂̈ʒu���}�b�v���܂����ł���
	if ((x + WALK_ENEMY_SIZE / 2) / MAP_SIZE - k >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}


	if (direct == 1)			//�E�����̏���
	{
		if (g_MapChip[(y) / MAP_SIZE + l + j][(x + WALK_ENEMY_SIZE) / MAP_SIZE - k - w] != 1	//�E��
			&& g_MapChip[(y +(WALK_ENEMY_SIZE /2) ) / MAP_SIZE + l + j][(x + WALK_ENEMY_SIZE) / MAP_SIZE - k - w] != 1){	//�E��
			return true;
		}
	}
	else {
		if (g_MapChip[(y) / MAP_SIZE + l][(x) / MAP_SIZE - k] != 1				//����
			&& g_MapChip[(y +(WALK_ENEMY_SIZE / 2) ) / MAP_SIZE + l][(x) / MAP_SIZE - k] != 1){	//����
 		return true;
		}

	}

	return false;
}

bool CheckWindow(int x) {

	int Cx = GetPlayerX();

	if (Cx  + ( WIDTH / 2 ) * MAP_SIZE> x) return true;
	if (Cx - (WIDTH / 2) * MAP_SIZE < x) return true;

	return false;
}