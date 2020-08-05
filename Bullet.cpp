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

		if (x < 0 || x > WIDTH * MAP_SIZE) DispFlg = false;		//��ʊO�ɏo����\���t���O��false�ɂ���
		
	}
	else {

	}
}


//�v���C���[�̓��Ɍ������Ĕ�Ԓe��
void LockBullet::Init(const int Ex, const int Ey) {			//�e�ۂ̏���������
	const int valanceY = 10;		//�e�ۂ̍����̕␳�l
	int rangeX = abs(GetPlayerX() - Ex);
	int rangeY = abs(GetPlayerY() - Ey);

	Speed = 4;							//���̒e�ۂ̃X�s�[�h

	SpeedY = (float)rangeY / ((float)rangeX / (float)Speed);

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

		if (x < 0 || x > WIDTH * MAP_SIZE) DispFlg = false;		//��ʊO�ɏo����\���t���O��false�ɂ���

	}
	else {

	}
}

//��Ɍ������Ĕ��ł��e�ۂ̏���������
void ChargeBullet::Init(const int Ex, const int Ey) {			//�e�ۂ̏���������
	const int valanceY = 10,valanceX = SHOOT_ENEMY_SIZE / 2;		//�e�ۂ̕␳�l
	const int SizeW = 10, SizeH = 20;

	Speed = 8;							//���̒e�ۂ̃X�s�[�h

	srand((unsigned int)time(NULL) + rand()); // ���ݎ����̏��ŏ�����

	type = (rand() % 2) + 2;

	if (type == 2) Cr = 0xff0000;
	else           Cr = 0x00ff00;

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
		//if (x < 0 || x > WIDTH * MAP_SIZE) DispFlg = false;		//��ʊO�ɏo����\���t���O��false�ɂ���
		if (y > HEIGHT * MAP_SIZE) DispFlg = false;

		switch (sequence)
		{
		case 1:		//��ɑł��グ�鏈��
			y -= Speed;

			if (y + h < -50) {		//��ɍs������E������Set
				LockX = GetPlayerX();
				y = 0;

				Replace = w;
				w = h;
				h = Replace;

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
	const int valanceY = 10;		//�e�ۂ̍����̕␳�l

	Speed = 4;							//���̒e�ۂ̃X�s�[�h

	x = Ex;		//�G�L�����̍��W��Set
	y = Ey - valanceY;

	w = BULLET_W;
	h = BULLET_H;



	DispFlg = true;			//�\���t���O���I���ɂ���
}

void RazerBullet::Move(int direct) {

}





//�e�ۂ̕`�揈��
void BulletInfo::Disp() {			//�e�ۂ̕\������
	if (DispFlg) {
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0x000000, true);
	}
}
void ChargeBullet::Disp() {			//��ɂނ����Ă����e�ۂ̕\������
	if (DispFlg) {
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, Cr, true);
	}
}


