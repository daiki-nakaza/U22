#pragma once

#include "DxLib.h"
#include "Enemy.h"
#include "Bullet.h"
#include "accessory.h"
#include "Player.h"


bool IronToEnemy(enemyInfo enemy);			//�S���ƓG�̓����蔻��
//bool IronToEnemy(BulletInfo Bullet);			//�S���ƓG�̒e�ۂ̓����蔻��

bool PlayerToEnemy(BulletInfo Bullet);			//�v���C���[�ƒe�ۂ̓����蔻��

bool IronToBullet(BulletInfo Bullet);			//�v���C���[�ƒe�ۂ̓����蔻��

//�G�L�������ړ�����ꏊ�ɂ�����߂�
int PlayerMoveCheck(enemyInfo enemy);

void PlayerAttackCheck(enemyInfo enemy);			//�v���C���[�̍U������

