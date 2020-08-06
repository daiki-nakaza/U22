#pragma once

#include "DxLib.h"
#include "Enemy.h"
#include "Bullet.h"
#include "accessory.h"
#include "Player.h"


bool IronToEnemy(enemyInfo enemy);			//鉄球と敵の当たり判定
//bool IronToEnemy(BulletInfo Bullet);			//鉄球と敵の弾丸の当たり判定

bool PlayerToEnemy(BulletInfo Bullet);			//プレイヤーと弾丸の当たり判定

bool IronToBullet(BulletInfo Bullet);			//プレイヤーと弾丸の当たり判定

//敵キャラが移動する場所にいたら戻す
int PlayerMoveCheck(enemyInfo enemy);

void PlayerAttackCheck(enemyInfo enemy);			//プレイヤーの攻撃判定

