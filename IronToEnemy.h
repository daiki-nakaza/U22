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

//�v���C���[�̍��W���~����
int GetPlayerX();
int GetPlayerY();


//�G�L�������ړ�����ꏊ�ɂ�����߂�
int PlayerMoveCheck(WalkEnemy enemy);
int PlayerMoveCheck(ShootEnemy enemy);
int PlayerMoveCheck(LockShootEnemy enemy);
int PlayerMoveCheck(TankEnemy enemy);
int PlayerMoveCheck(RazerEnemy enemy);

//�v���C���[�̍U������
void PlayerAttackCheck(WalkEnemy enemy);
void PlayerAttackCheck(ShootEnemy enemy);
void PlayerAttackCheck(LockShootEnemy enemy);
void PlayerAttackCheck(TankEnemy enemy);
void PlayerAttackCheck(RazerEnemy enemy);
