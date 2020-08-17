#include "DxLib.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Define.h"
#include "Map.h"
#include "IronToEnemy.h"

#include <time.h>

//////////////////////////////////////////////
////////////�e�ۂ̊֐��̒�`///////////////////
//////////////////////////////////////////////

//�^��������Ԓe�ۂ̊֐���`
void NormalBullet::Init(const int Ex, const int Ey) {			//�e�ۂ̏���������
	const int valanceY = 10;		//�e�ۂ̍����̕␳�l

	Speed = 4;							//���̒e�ۂ̃X�s�[�h
	MoveSum = 0;

	x = Ex;		//�G�L�����̍��W��Set
	y = Ey - valanceY;

	w = BULLET_W;
	h = BULLET_H;

	

	DispFlg = true;			//�\���t���O���I���ɂ���
}

void NormalBullet::Move(const int dir) {			//�e�ۂ̏���

	if (DispFlg) {
		direct = dir;

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�

		x += dir * Speed;
		MoveSum += Speed;

		if (CheckWindow() || CheckHitBall())DispFlg = false;

		if (CheckHitPlayer()) {		//�v���C���[�ɂ������Ă�����
			DispFlg = false;
		}
	}
	else {

	}
}


//�v���C���[�̓��Ɍ������Ĕ�Ԓe��
void LockBullet::Init(const int Ex, const int Ey) {			//�e�ۂ̏���������
	const int valanceY = 10;		//�e�ۂ̍����̕␳�l
	int rangeX = abs(PlayerX - Ex + MapDrawPointX - MapX * MAP_SIZE);
	int rangeY = (PlayerY - Ey + MapDrawPointY - MapY * MAP_SIZE) + (CHA_SIZE_Y / 2);

	Speed = 4;							//���̒e�ۂ̃X�s�[�h

	SpeedY = rangeY / (rangeX / Speed);

	x = Ex;		//�G�L�����̍��W��Set
	y = Ey - valanceY;

	w = BULLET_W;
	h = BULLET_H;



	DispFlg = true;			//�\���t���O���I���ɂ���
}


//
void LockBullet::Move(const int dir) {			//�e�ۂ̏���
	if (DispFlg) {
		direct = dir;

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�

		x += dir * Speed;

		(y) += -dir * SpeedY;

		if (CheckWindow() || CheckHitBall())DispFlg = false;

		if (CheckHitPlayer()) {		//�v���C���[�ɂ������Ă�����
			DispFlg = false;
		}
	}
	else {

	}
}


//��Ɍ������Ĕ��ł��e�ۂ̏���������
void ChargeBullet::Init(const int Ex, const int Ey) {			//�e�ۂ̏���������
	const int valanceY = 10,valanceX = SHOOT_ENEMY_SIZE / 2;		//�e�ۂ̕␳�l
	const int SizeW = MAP_SIZE, SizeH = MAP_SIZE;

	Speed = 8;							//���̒e�ۂ̃X�s�[�h

	srand((unsigned int)time(NULL) + rand()); // ���ݎ����̏��ŏ�����

	type = (rand() % 2) + 2;
	anm = 0;

	if (type == 2) LoadDivGraph("images/Red bulletAll.png", 2, 2, 1, MAP_SIZE, MAP_SIZE, pic);
	else           LoadDivGraph("images/Green bulletAll.png", 2, 2, 1, MAP_SIZE, MAP_SIZE, pic);

	sequence = 1;			//�ŏ��Set

	x = Ex + valanceX;		//�G�L�����̍��W��Set
	y = Ey - valanceY;

	w = SizeW;
	h = SizeH;


	DispFlg = true;			//�\���t���O���I���ɂ���
}

//��Ɍ������Ĕ��ł��e�ۂ̏���
void ChargeBullet::Move(const int dir) {			//�e�ۂ̏���
	static int LockX;
	int Replace;		//�傫�������ւ���p�̕ϐ�

	if (DispFlg) {
		direct = dir; 
		if (CheckHitBall())DispFlg = false;

		if (CheckHitPlayer()) {		//�v���C���[�ɂ������Ă�����
			DispFlg = false;
		}
		if (CheckWindow() && sequence > 1 && y > (WIDTH / 2 * MAP_SIZE))DispFlg = false;

		switch (sequence)
		{
		case 1:		//��ɑł��グ�鏈��
			y -= Speed;

			if (y + h < -50) {		//��ɍs������E������Set
				LockX = GetPlayerX() + CHA_SIZE_X/2;
				y = 0 + CHA_SIZE_Y / 2;

				Replace = w;
				w = h;
				h = Replace;
				anm++;

				if (type == 2)x =LockX + (HEIGHT - ((HEIGHT * MAP_SIZE) - GetPlayerY()) / MAP_SIZE) * MAP_SIZE;
				else          x =LockX - (HEIGHT - ((HEIGHT * MAP_SIZE) - GetPlayerY()) / MAP_SIZE)* MAP_SIZE;

				sequence = type;
			}
			break;
		case 2:		//�E������ł��鏈��
			y += Speed;
			x -= Speed;

			break;
		case 3:		//��������ł��鏈��
			y += Speed;
			x += Speed;

			break;
		default:
			break;
		}
	}
	else {

	}
}


//���[�U�[�̒e	
void RazerBullet::Init(const int Ex, const int Ey) {
	const int valanceY = 4;		//�e�ۂ̍����̕␳�l

	Speed = 8;							//���̒e�ۂ̃X�s�[�h

	x = Ex + (RAZER_ENEMY_SIZE / 4);		//�G�L�����̍��W��Set
	y = Ey - valanceY;

	w = BULLET_W;
	h = MAP_SIZE;

	BWidth = 0;
	MoveSum = 0;

	pic = LoadGraph("images/Laser.png");

	DispFlg = true;			//�\���t���O���I���ɂ���
}

void RazerBullet::Move(int direct) {
	const int rangeX = MAP_SIZE * WIDTH;		//���[�U�[�̒���

	if (DispFlg) {
		x += direct * Speed;
		MoveSum += Speed;

		if(BWidth < rangeX) BWidth -= direct * Speed;

		if (x + BWidth + MapDrawPointX - MapX * MAP_SIZE < 0) {
			DispFlg = false;
		}
	}
}





//�e�ۂ̕`�揈��
void BulletInfo::Disp() {			//�e�ۂ̕\������
	if (DispFlg) {
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0x000000, true);
	}
}

void RazerBullet::Disp() {			//��ɂނ����Ă����e�ۂ̕\������
	if (DispFlg) {
		//DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
		//	x + BWidth + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0x00ff00, true);
		DrawExtendGraph(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
			x + BWidth + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, pic, true);
	}
}

void ChargeBullet::Disp() {			//��ɂނ����Ă����e�ۂ̕\������
	if (DispFlg) {
		DrawGraph(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,pic[anm], true);
	}
}



/************************************************************
***********************�����蔻��****************************
************************************************************/

bool BulletInfo::CheckHitBall() {		//�S���Ƃ̓����蔻��
	if (y - MapDrawPointY - MapY * MAP_SIZE < (g_IronBall.y + MapDrawPointY - MapY * MAP_SIZE) + g_IronBall.r
		&& y + h - MapDrawPointY - MapY * MAP_SIZE > (g_IronBall.y + MapDrawPointY - MapY * MAP_SIZE) - g_IronBall.r) {
		if ( (x + MapDrawPointX - MapX * MAP_SIZE) < ( (g_IronBall.x + MapDrawPointX - MapX * MAP_SIZE) + g_IronBall.r)
			&& (x + w + MapDrawPointX - MapX * MAP_SIZE) > ( (g_IronBall.x + MapDrawPointX - MapX * MAP_SIZE) - g_IronBall.r) ) {
			return true;
		}
	}

	return false;
}


//�����蔻��
bool BulletInfo::CheckHitPlayer() {		//�v���C���[�Ƃ̓����蔻��

	if (y - MapDrawPointY - MapY * MAP_SIZE < PlayerY + CHA_SIZE_Y
		&& y + h - MapDrawPointY - MapY * MAP_SIZE > PlayerY) {
		if (x + MapDrawPointX - MapX * MAP_SIZE < (PlayerX + CHA_SIZE_X)
			&& x + w + MapDrawPointX - MapX * MAP_SIZE >(PlayerX)) {
			return true;
		}
	}
	return false;
}


bool BulletInfo::CheckWindow() {		//��ʂɓ����Ă��邩

	if ((x + h + MapDrawPointX - MapX * MAP_SIZE < -1 * ( (WIDTH / 8) * MAP_SIZE))
		|| (x + MapDrawPointX - MapX * MAP_SIZE > WIDTH * MAP_SIZE + (WIDTH / 8 * MAP_SIZE))) {
		return true;
	}

	return false;
}