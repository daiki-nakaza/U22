#include "DxLib.h"

#include "IronToEnemy.h"
#include "Map.h"


bool IronToEnemy(WalkEnemy enemy) {

	if (enemy.picDir) {			//�E�����̏���
		//���̈ړ��̏ꏊ���S���Ɣ���Ă�����true��Ԃ�
		if ((enemy.y + enemy.h) / MAP_SIZE == g_IronBall.y / MAP_SIZE + MapY
			&& (((enemy.x + enemy.w - MapDrawPointX) + (enemy.direct * enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x - g_IronBall.r) / MAP_SIZE + MapX) return true;
	}
	else {							//�������̏���
		//���̈ړ��̏ꏊ���S���Ɣ���Ă�����true��Ԃ�
		if ((enemy.y + enemy.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
			&& (((enemy.x - MapDrawPointX) + (enemy.direct * enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x + g_IronBall.r) / MAP_SIZE + MapX) return true;
	}

	return false;
}

bool IronToEnemy(ShootEnemy enemy) {

	if (enemy.picDir) {			//�E�����̏���
		//���̈ړ��̏ꏊ���S���Ɣ���Ă�����true��Ԃ�
		if ((enemy.y + enemy.h) / MAP_SIZE == g_IronBall.y / MAP_SIZE + MapY
			&& (((enemy.x + enemy.w - MapDrawPointX) + (enemy.direct * enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x - g_IronBall.r) / MAP_SIZE + MapX) return true;
	}
	else {							//�������̏���
		//���̈ړ��̏ꏊ���S���Ɣ���Ă�����true��Ԃ�
		if ((enemy.y + enemy.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
			&& (((enemy.x - MapDrawPointX) + (enemy.direct * enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x + g_IronBall.r) / MAP_SIZE + MapX) return true;
	}

	return false;
}

bool IronToBullet(BulletInfo Bullet) {			//�S���ƓG�̒e�ۂ̓����蔻��
	if (Bullet.picDir) {			//�E�����̏���
		//���̈ړ��̏ꏊ���S���Ɣ���Ă�����true��Ԃ�
		if ((Bullet.y + Bullet.h) / MAP_SIZE == g_IronBall.y / MAP_SIZE + MapY
			&& (((Bullet.x + Bullet.w - MapDrawPointX) + (Bullet.direct * Bullet.Speed)) / MAP_SIZE) + MapX == (g_IronBall.x - g_IronBall.r) / MAP_SIZE + MapX) return true;
	}
	else {							//�������̏���
		//���̈ړ��̏ꏊ���S���Ɣ���Ă�����true��Ԃ�
		if ((Bullet.y + Bullet.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
			&& (((Bullet.x - MapDrawPointX) + (Bullet.direct * Bullet.Speed)) / MAP_SIZE) + MapX == (g_IronBall.x + g_IronBall.r) / MAP_SIZE + MapX) return true;
	}

	if (Bullet.picDir) {			//�E�����̏���
		//���̈ړ��̏ꏊ���S���Ɣ���Ă�����true��Ԃ�
		if ((Bullet.y + Bullet.h) / MAP_SIZE == PlayerY + (CHA_SIZE_Y / 2) / MAP_SIZE + MapY
			&& (((Bullet.x + Bullet.w - MapDrawPointX) + (Bullet.direct * Bullet.Speed)) / MAP_SIZE) + MapX == PlayerX / MAP_SIZE + MapX) return true;
	} else {							//�������̏���
		//���̈ړ��̏ꏊ���S���Ɣ���Ă�����true��Ԃ�
		if ((Bullet.y + Bullet.h + MapDrawPointY) / MAP_SIZE + MapY == PlayerY + (CHA_SIZE_Y / 2) / MAP_SIZE + MapY
			&& (((Bullet.x - MapDrawPointX) + (Bullet.direct * Bullet.Speed)) / MAP_SIZE) + MapX == PlayerX + CHA_SIZE_X / MAP_SIZE + MapX) return true;
	}

	return false;
}


bool PlayerToEnemy(BulletInfo Bullet) {			//�v���C���[�ƒe�ۂ̓����蔻��

	//�v���C���[�̉E��̍��W�����Ă̔���
	if ((Bullet.y + Bullet.h) / MAP_SIZE + MapY == (PlayerY + Map_NewY) / MAP_SIZE + MapY
		&& ((Bullet.x - MapDrawPointX) / MAP_SIZE) + MapX == (PlayerX + CHA_SIZE_X + Map_NewX) / MAP_SIZE + MapX) return true;


	//�v���C���[�̍���̍��W�����Ă̔���
	if ((Bullet.y + Bullet.h) / MAP_SIZE == (PlayerY + Map_NewY) / MAP_SIZE + MapY
		&& ((Bullet.x + Bullet.w - MapDrawPointX) / MAP_SIZE) + MapX == (PlayerX + Map_NewX) / MAP_SIZE + MapX) return true;

	//�v���C���[�̉E���̍��W�����Ă̔���
	if ((Bullet.y) / MAP_SIZE + MapY == (PlayerY + Map_NewY) / MAP_SIZE + MapY
		&& ((Bullet.x - MapDrawPointX) / MAP_SIZE) + MapX == (PlayerX + CHA_SIZE_X + Map_NewX) / MAP_SIZE + MapX) return true;


	//�v���C���[�̍����̍��W�����Ă̔���
	if ((Bullet.y) / MAP_SIZE == (PlayerY + Map_NewY) / MAP_SIZE + MapY
		&& ((Bullet.x + Bullet.w - MapDrawPointX) / MAP_SIZE) + MapX == (PlayerX + Map_NewX) / MAP_SIZE + MapX) return true;

	return false;
}

bool EnemyCheckDir(enemyInfo enemy) {
	if(enemy.x < PlayerX){}

	return true;
}