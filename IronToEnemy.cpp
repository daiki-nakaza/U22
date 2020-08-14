#include "DxLib.h"

#include "IronToEnemy.h"
#include "Map.h"


bool IronToEnemy(enemyInfo enemy) {

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
	

	//�S���̉E��̍��W�����Ă̔���
	if ((Bullet.y + Bullet.h) / MAP_SIZE + MapY == (g_IronBall.y - g_IronBall.r) / MAP_SIZE + MapY
		&& ((Bullet.x - MapDrawPointX) / MAP_SIZE) + MapX == (g_IronBall.x + g_IronBall.r) / MAP_SIZE + MapX) return true;


	//�S���̍���̍��W�����Ă̔���
	if ((Bullet.y + Bullet.h) / MAP_SIZE == (g_IronBall.y - g_IronBall.r) / MAP_SIZE + MapY
		&& ((Bullet.x + Bullet.w - MapDrawPointX) / MAP_SIZE) + MapX == (g_IronBall.x - g_IronBall.r) / MAP_SIZE + MapX) return true;

	//�S���̉E���̍��W�����Ă̔���
	if ((Bullet.y) / MAP_SIZE + MapY == (g_IronBall.y + g_IronBall.r) / MAP_SIZE + MapY
		&& ((Bullet.x - MapDrawPointX) / MAP_SIZE) + MapX == (g_IronBall.x + g_IronBall.r) / MAP_SIZE + MapX) return true;


	//�S���̍����̍��W�����Ă̔���
	if ((Bullet.y) / MAP_SIZE == (g_IronBall.y + g_IronBall.r) / MAP_SIZE + MapY
		&& ((Bullet.x + Bullet.w - MapDrawPointX) / MAP_SIZE) + MapX == (g_IronBall.x - g_IronBall.r) / MAP_SIZE + MapX) {
		return true;
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

int GetPlayerX() {
	return PlayerX + Map_PlayerX;
}


int GetPlayerY() {
	return PlayerY;
}

//�G�L�������ړ�����ꏊ�ɂ�����߂�
//�G�̍\���̂̎�ޕ��I�[�o�[���[�h�ō��܂�
int PlayerMoveCheck(WalkEnemy enemy) {
	if (enemy.Life > 0) {
		if (enemy.x - NewX - Map_NewX < CHA_SIZE_X
			&& enemy.y - NewY - Map_NewY < CHA_SIZE_Y - 1
			&& enemy.x - NewX - Map_NewX > 0 - enemy.w
			&& enemy.y - NewY - Map_NewY > 0 - enemy.h) {
			return 1;
		}
	}
	return 0;
}

int PlayerMoveCheck(ShootEnemy enemy) {
	if (enemy.Life > 0) {
		if (enemy.x - NewX - Map_NewX < CHA_SIZE_X
			&& enemy.y - NewY - Map_NewY < CHA_SIZE_Y - 1
			&& enemy.x - NewX - Map_NewX > 0 - enemy.w
			&& enemy.y - NewY - Map_NewY > 0 - enemy.h) {
			return 1;
		}
	}
	return 0;
}

int PlayerMoveCheck(LockShootEnemy enemy) {
	if (enemy.Life > 0) {
		if (enemy.x - NewX - Map_NewX < CHA_SIZE_X
			&& enemy.y - NewY - Map_NewY < CHA_SIZE_Y - 1
			&& enemy.x - NewX - Map_NewX > 0 - enemy.w
			&& enemy.y - NewY - Map_NewY > 0 - enemy.h) {
			return 1;
		}
	}
	return 0;
}

int PlayerMoveCheck(TankEnemy enemy) {
	if (enemy.Life > 0) {
		if (enemy.x - NewX - Map_NewX < CHA_SIZE_X
			&& enemy.y - NewY - Map_NewY < CHA_SIZE_Y - 1
			&& enemy.x - NewX - Map_NewX > 0 - enemy.w
			&& enemy.y - NewY - Map_NewY > 0 - enemy.h) {
			return 1;
		}
	}
	return 0;
}

int PlayerMoveCheck(RazerEnemy enemy) {
	if (enemy.Life > 0) {
		if (enemy.x - NewX - Map_NewX < CHA_SIZE_X
			&& enemy.y - NewY - Map_NewY < CHA_SIZE_Y - 1
			&& enemy.x - NewX - Map_NewX > 0 - enemy.w
			&& enemy.y - NewY - Map_NewY > 0 - enemy.h) {
			return 1;
		}
	}
	return 0;
}



//�G�L�����ɍU���𓖂Ă�
//�G�̍\���̂̎�ޕ��I�[�o�[���[�h�ō��܂�
void PlayerAttackCheck(WalkEnemy enemy) {
	if (enemy.Life > 0) {					//�G�̃��C�t���O����Ȃ��Ȃ���W���݂�
		if (Bectl == 0 && enemy.outtime == 0) {						//�E����
			if (enemy.x - PlayerX - Map_PlayerX < CHA_SIZE_X * 2
				&& enemy.x - PlayerX - Map_PlayerX > 0) {
				enemy.Life--;
				enemy.outtime = 30;
			}
		}
		else if (Bectl == 1) {						//�E����
			if (enemy.x - PlayerX - Map_PlayerX > 0 - CHA_SIZE_X
				&& enemy.x - PlayerX - Map_PlayerX < 0) {
				enemy.Life--;
				enemy.outtime = 30;
			}
		}

	}
}
void PlayerAttackCheck(ShootEnemy enemy) {
	if (enemy.Life > 0) {					//�G�̃��C�t���O����Ȃ��Ȃ���W���݂�
		if (Bectl == 0 && enemy.outtime == 0) {						//�E����
			if (enemy.x - PlayerX - Map_PlayerX < CHA_SIZE_X * 2
				&& enemy.x - PlayerX - Map_PlayerX > 0) {
				enemy.Life--;
				enemy.outtime = 30;
			}
		}
		else if (Bectl == 1) {						//�E����
			if (enemy.x - PlayerX - Map_PlayerX > 0 - CHA_SIZE_X
				&& enemy.x - PlayerX - Map_PlayerX < 0) {
				enemy.Life--;
				enemy.outtime = 30;
			}
		}

	}
}

void PlayerAttackCheck(LockShootEnemy enemy) {
	if (enemy.Life > 0) {					//�G�̃��C�t���O����Ȃ��Ȃ���W���݂�
		if (Bectl == 0 && enemy.outtime == 0) {						//�E����
			if (enemy.x - PlayerX - Map_PlayerX < CHA_SIZE_X * 2
				&& enemy.x - PlayerX - Map_PlayerX > 0) {
				enemy.Life--;
				enemy.outtime = 30;
			}
		}
		else if (Bectl == 1) {						//�E����
			if (enemy.x - PlayerX - Map_PlayerX > 0 - CHA_SIZE_X
				&& enemy.x - PlayerX - Map_PlayerX < 0) {
				enemy.Life--;
				enemy.outtime = 30;
			}
		}

	}
}

void PlayerAttackCheck(TankEnemy enemy) {
	if (enemy.Life > 0) {					//�G�̃��C�t���O����Ȃ��Ȃ���W���݂�
		if (Bectl == 0 && enemy.outtime == 0) {						//�E����
			if (enemy.x - PlayerX - Map_PlayerX < CHA_SIZE_X * 2
				&& enemy.x - PlayerX - Map_PlayerX > 0) {
				enemy.Life--;
				enemy.outtime = 30;
			}
		}
		else if (Bectl == 1) {						//�E����
			if (enemy.x - PlayerX - Map_PlayerX > 0 - CHA_SIZE_X
				&& enemy.x - PlayerX - Map_PlayerX < 0) {
				enemy.Life--;
				enemy.outtime = 30;
			}
		}

	}
}

void PlayerAttackCheck(RazerEnemy enemy) {
	if (enemy.Life > 0) {					//�G�̃��C�t���O����Ȃ��Ȃ���W���݂�
		if (Bectl == 0 && enemy.outtime == 0) {						//�E����
			if (enemy.x - PlayerX - Map_PlayerX < CHA_SIZE_X * 2
				&& enemy.x - PlayerX - Map_PlayerX > 0) {
				enemy.Life--;
				enemy.outtime = 30;
			}
		}
		else if (Bectl == 1) {						//�E����
			if (enemy.x - PlayerX - Map_PlayerX > 0 - CHA_SIZE_X
				&& enemy.x - PlayerX - Map_PlayerX < 0) {
				enemy.Life--;
				enemy.outtime = 30;
			}
		}

	}
}