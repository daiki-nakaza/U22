#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"
#include "accessory.h"
#include "Boss.h"

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
	if (CheckHitPlayer() && Attack > 0 && outtime == 0) {		//�v���C���[���U�����Ă�����
		outtime = 60;
		if (Life-- <= 0)DispFlg = false;
	}
	else {		//�v���C���[�̗̑͂����炷

	}
	if (outtime > 0) {
		if (outtime-- < 0) outtime = 0;
	}
	if (Life <= 0) {
		DispFlg = false;
	}
}

void enemyInfo::Disp() {			//�G�̕\������
	if (DispFlg && CheckWindow()) {		//�G�\��
		if (outtime == 0) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic, true, picDir);
		}
		else if (outtime % 2 == 1) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic, true, picDir);
		}
	}
	else {				//�G��\��

	}
}

bool enemyInfo::CheckHitBall() {
	if (y - MapDrawPointY - MapY * MAP_SIZE < (g_IronBall.y + MapDrawPointY - MapY * MAP_SIZE) + g_IronBall.r
		&& y + h - MapDrawPointY - MapY * MAP_SIZE >(g_IronBall.y + MapDrawPointY - MapY * MAP_SIZE) - g_IronBall.r) {
		if ((x + MapDrawPointX - MapX * MAP_SIZE) < ((g_IronBall.x + MapDrawPointX - MapX * MAP_SIZE) + g_IronBall.r)
			&& (x + w + MapDrawPointX - MapX * MAP_SIZE) > ((g_IronBall.x + MapDrawPointX - MapX * MAP_SIZE) - g_IronBall.r)) {
			return true;
		}
	}
	return false;
}


bool enemyInfo::CheckHitPlayer() {

	if (y - MapDrawPointY - MapY * MAP_SIZE < PlayerY + CHA_SIZE_Y
		&& y + h - MapDrawPointY - MapY * MAP_SIZE > PlayerY) {
		if (x + MapDrawPointX - MapX * MAP_SIZE < (PlayerX + CHA_SIZE_X)
			&& x + w + MapDrawPointX - MapX * MAP_SIZE >(PlayerX)) {
			return true;
		}
	}
	return false;
}
//////////////////////////////////////////////
/////////////�����G�̏���////////////////////
/////////////////////////////////////////////

void WalkEnemy::Init(int Tempx, int Tempy) {                 // �G�̏�����
	int SetX = Tempx * MAP_SIZE + ( ( (Tempy / HEIGHT) * WIDTH) * WIDTH) , SetY = (Tempy % HEIGHT) * MAP_SIZE;


	x = SetX;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = SetY - (WALK_ENEMY_SIZE - MAP_SIZE) + 3;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

	w = WALK_ENEMY_SIZE;						//�G�̉���
	h = WALK_ENEMY_SIZE;						//�G�̏c

	LoadDivGraph("images/ZakoWalk.png", 4, 4, 1, WALK_ENEMY_SIZE, WALK_ENEMY_SIZE, pic);
	//pic = LoadGraph("images/Zako.png");

	anm = 0;

	direct = -1;						//����������n�߂�
	picDir = true;


	speed = 2;						//�G�̃X�s�[�h

	Life = 3;					//�G��HP�@�Ƃ�܂R

	type = 0;					//�G�̃^�C�v

	outtime = 0;				//�P�x�U������������疳�G


	DispFlg = TRUE;					//�G��\��


}


void WalkEnemy::WalkMove(){
	NewDir = direct;
	NewX = x;

	const int FrmMax = 20;		//�A�j���[�V�����t���[���̊�

	int Enemy_MapX, Enemy_MapY;		//�}�b�v�`�b�v��̍��W�����

	Enemy_MapX = (x % (WIDTH * MAP_SIZE) ) / MAP_SIZE;
	Enemy_MapY = ( ( (y + h) / MAP_SIZE) + (x / (WIDTH * MAP_SIZE) ) * HEIGHT);

	if (DispFlg && CheckWindow()) {//
		if (g_MapChip[Enemy_MapY][Enemy_MapX] == 1) y += GRAVITY;

		if (direct < 0) picDir = true;		//�������Ȃ�
		else picDir = false;					//�E�����Ȃ�

		x += direct * speed;

		if (EnemyCheckHit(x, y, direct)) {
			if (x % 32 <= 16) {
				direct *= -1;
				x -= x % 32;
			}
			else {
				direct *= -1;
				x += x % 32;
			}
		}
		Move();			//�G���ʂ̊֐�	


		if (CheckHitPlayer() 
			&& outtime == 0
			&& Playerouttime == 0) {		//�ǂ����������̏�ԂŎG���I�ƂԂ�������
			direct *= -1; 
			PlayerDamage();
		}


		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}

		if (CheckHitBall()) {
			direct *= -1;
			if ((x + MapDrawPointX - MapX * MAP_SIZE) - (g_IronBall.x + MapDrawPointX - MapX * MAP_SIZE) < 0) {
				x -= x % 32;
			}
			else {
				x += x % 32;
			}
		}
	}

}

void WalkEnemy::Disp() { 
	if (DispFlg && CheckWindow()) {		//�G�\��
		if (outtime == 0) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic[anm], true, picDir);
		}
		else if (outtime % 2 ==  1) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic[anm], true, picDir);
		}
	}
	else {				//�G��\��

	}
}

////////////////////////////////////////////
//////////���G�̏���//////////////////////
/////////////////////////////////////////////

void ShootEnemy::Init(int Tempx, int Tempy) {                 // ���G�̏�����
	int SetX = Tempx * MAP_SIZE + (((Tempy / HEIGHT) * WIDTH) * WIDTH), SetY = (Tempy % HEIGHT) * MAP_SIZE;


	x = SetX ;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = SetY - (SHOOT_ENEMY_SIZE - MAP_SIZE);								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

	w = SHOOT_ENEMY_SIZE;						//�G�̉���
	h = SHOOT_ENEMY_SIZE;						//�G�̏c

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, SHOOT_ENEMY_SIZE, SHOOT_ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//����������n�߂�

	Firecnt = 0;		 //���˂̃J�E���g
	BulletCnt = 0;		//�R���A���Œe�𔭎˂�����
	ReloadCnt = 0;		//�����[�h�̎��ԃJ�E���g

	speed = 0;						//�G�̃X�s�[�h
	picDir = true;

	Life = 3;					//�G��HP�@�Ƃ�܂R

	type = 1;					//�G�̃^�C�v

	pic = LoadGraph("images/Enemy Soldier.png");

	DispFlg = TRUE;					//�G��\��


}


void ShootEnemy::ShootMove() {		//���G�̏���

	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�

	const int Rate = 20;		//���˃��[�g
	const int ReloadTime = 180;			//�����[�h���ԁ@��̂R�b




	if (DispFlg && CheckWindow()) {//

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�


		if (Firecnt++ >= Rate
			&& BulletCnt < Bullet_MAX
			&& !Bullet[BulletCnt].DispFlg) {
			Bullet[BulletCnt].Init(x, y + h / 2);			//�e���΂��Ԋu
			BulletCnt++;
			Firecnt = 0;
			if (BulletCnt >= Bullet_MAX - 1) ReloadCnt = 0;
		}

		if (!Bullet[0].DispFlg
			&& !Bullet[1].DispFlg
			&& !Bullet[2].DispFlg
			&& ReloadCnt++ > ReloadTime) {
			BulletCnt = 0;		//�e�̕\���t���O�����ׂ�off�Ȃ猂�Ă�悤�ɂȂ�

		}

		for (int i = 0; i < Bullet_MAX; i++) {
			Bullet[i].Disp();
			Bullet[i].Move(direct);			//�e�ۂ̏���

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


	x = SetX;										// �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = SetY - (SHOOT_ENEMY_SIZE - MAP_SIZE);		// �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

	w = SHOOT_ENEMY_SIZE;						//�G�̉���
	h = SHOOT_ENEMY_SIZE;						//�G�̏c

	anm = 0;

	Firecnt = 0;		 //���˂̃J�E���g
	BulletCnt = 0;		//�R���A���Œe�𔭎˂�����
	ReloadCnt = 0;		//�����[�h�̎��ԃJ�E���g

	direct = -1;						//����������n�߂�

	speed = 0;						//�G�̃X�s�[�h
	picDir = true;

	Life = 3;					//�G��HP�@�Ƃ�܂R

	type = 1;					//�G�̃^�C�v

	pic = LoadGraph("images/Variant Enemy Soldier.png");

	DispFlg = TRUE;					//�G��\��



}


void LockShootEnemy::LockShootMove() {			//���G�̏���

	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�

	const int Rate = 20;		//���˃��[�g
	const int ReloadTime = 180;			//�����[�h���ԁ@��̂R�b


	if (DispFlg && CheckWindow()) {//

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
			if (BulletCnt >= Bullet_MAX - 1) ReloadCnt = 0;
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
			if (DebugMode) DrawFormatString(100, 140 + i * 30, 0x000000, "%f", Bullet[i].SpeedY);
		}

		Move();			//�G���ʂ̊֐�

	}

}

//��Ԃ̓G(��Ɍ������Ēe���΂��z)
void TankEnemy::Init(int Tempx, int Tempy) {
	int SetX = Tempx * MAP_SIZE + (((Tempy / HEIGHT) * WIDTH) * WIDTH), SetY = (Tempy % HEIGHT) * MAP_SIZE;


	x = SetX;										// �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = SetY - (TANK_ENEMY_SIZE - MAP_SIZE);		// �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

	w = TANK_ENEMY_SIZE;						//�G�̉���
	h = TANK_ENEMY_SIZE;						//�G�̏c��

	anm = 0;

	Firecnt = 0;		 //���˂̃J�E���g
	BulletCnt = 0;		//�R���A���Œe�𔭎˂�����
	ReloadCnt = 0;		//�����[�h�̎��ԃJ�E���g

	direct = -1;						//����������n�߂�

	speed = 0;						//�G�̃X�s�[�h
	picDir = true;

	Life = 3;					//�G��HP�@�Ƃ�܂R

	type = 1;					//�G�̃^�C�v

	LoadDivGraph("images/TankEnemy.png", 2, 2, 1, TANK_ENEMY_SIZE, TANK_ENEMY_SIZE, pic);

	DispFlg = TRUE;					//�G��\��


}

void TankEnemy::TankMove() {


	const int FrmMax = 20;		//�A�j���[�V�����t���[���̊�

	const int Rate = 40;		//���˃��[�g
	const int ReloadTime = 240;			//�����[�h���ԁ@



	if (DispFlg && CheckWindow()) {//

		//if(DirCheck)

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�



		if (++AnmCnt >= FrmMax) {				//�A�j���[�V�����t���[��
			if (++anm > 1) anm = 0;
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


void TankEnemy::Disp() {
	if (DispFlg && CheckWindow()) {		//�G�\��
		if (outtime == 0) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic[anm], true, picDir);
		}
		else if (outtime % 2 ==  1) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic[anm], true, picDir);
		}
	}
	else {				//�G��\��

	}
}

//�g���C�����G�̊֐���`
void RazerEnemy::Init(int Tempx, int Tempy){
	int SetX = Tempx * MAP_SIZE + (((Tempy / HEIGHT) * WIDTH) * WIDTH), SetY = (Tempy % HEIGHT) * MAP_SIZE;

	x = SetX;										// �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = SetY - (RAZER_ENEMY_SIZE - MAP_SIZE);		// �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

	w = RAZER_ENEMY_SIZE;						//�G�̉���
	h = RAZER_ENEMY_SIZE;						//�G�̏c��

	anm = 0;

	direct = -1;						//����������n�߂�

	speed = 0;						//�G�̃X�s�[�h
	picDir = true;

	Life = 3;					//�G��HP�@�Ƃ�܂R

	type = 1;					//�G�̃^�C�v

	LoadDivGraph("images/HadouhouAll.png",3,3,1, TANK_ENEMY_SIZE, TANK_ENEMY_SIZE,pic);

	//pic[2] = LoadGraph("images/Hadouhou2.png");

	DispFlg = TRUE;					//�G��\��

}

void RazerEnemy::ShotMove() {

	static int AnmCnt = 0;

	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�

	const int ReloadTime = 300;


	if (DispFlg && CheckWindow()) {//
		if (!Bullet.DispFlg && Reload <= 0) {
			Bullet.Init(x, y + h / 2);
			Reload = ReloadTime;
		}

		Bullet.Move(direct);
		Bullet.Disp();

		if (Reload >= 0 && !Bullet.DispFlg) Reload--;

		if (Reload == ReloadTime || Reload < 30) anm = 2;
		else if(Reload < 60)anm = 1;
		else anm = 0;

		Move();			//�G���ʂ̊֐�

	}
}

void RazerEnemy::Disp() {
	if (DispFlg && CheckWindow()) {		//�G�\��
		if (outtime == 0) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic[anm], true, picDir);
		}
		else if (outtime % 2 == 1) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2, 1, 0, pic[anm], true, picDir);
		}
	}
	else {				//�G��\��

	}
}
/**************************************************
*�@�G�̊֐��̒�`
***************************************************/

void enemyInit() {			//�G�̏���������
	SetTP = 0;
	 
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
			else if (g_MapChip[y][x] == 8) {			//�{�X
				g_Boss.BossInit(x, y);
				break;
			}
			else if (g_MapChip[y][x] == 9) {			//�{�X�̃e���|�[�g��
				g_Boss.TPInit(x, y);
				break;
			}
		}
	}
	

}

void enemyDisp() {

	if (g_Boss.CheckWindow()) {
		g_Boss.Disp();
	} else {
		for (int i = 0; i < ENEMY_MAX; i++) {
			g_WalkEnemy[i].Disp();
			g_ShootEnemy[i].Disp();
			g_LockShootEnemy[i].Disp();
			g_TankEnemy[i].Disp();
			g_RazerEnemy[i].Disp();
		}
	}
	
}




void enemyMove() {
	static bool Initflg = true;
	if (Initflg) {
		enemyInit();
		Initflg = false;
	}
	if (g_Boss.CheckWindow()) {
		g_Boss.BossMove();
	}
	else {
		for (int i = 0; i < ENEMY_MAX; i++) {

			g_WalkEnemy[i].WalkMove();
			g_ShootEnemy[i].ShootMove();
			g_LockShootEnemy[i].LockShootMove();
			g_TankEnemy[i].TankMove();
			g_RazerEnemy[i].ShotMove();
		}
	}

	if (DebugMode) {
	//	DrawFormatString(100, 300, 0xff0000, "%d %d", g_Boss.x, g_Boss.y);
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
			|| g_MapChip[(y +(WALK_ENEMY_SIZE /2) ) / MAP_SIZE + l + j][(x + WALK_ENEMY_SIZE) / MAP_SIZE - k - w] != 1){	//�E��
			return true;
		}
	}
	else {
		if (g_MapChip[(y) / MAP_SIZE + l][(x) / MAP_SIZE - k] != 1				//����
			|| g_MapChip[(y +(WALK_ENEMY_SIZE / 2) ) / MAP_SIZE + l][(x) / MAP_SIZE - k] != 1){	//����
 		return true;
		}

	}

	return false;
}

bool enemyInfo::CheckWindow() {

	if ((x + MapDrawPointX - MapX * MAP_SIZE > -WIDTH / 8 * MAP_SIZE)
		&& (x + MapDrawPointX - MapX * MAP_SIZE < WIDTH * MAP_SIZE + (WIDTH / 8 * MAP_SIZE))) {
		return true;
	}

	return false;
}