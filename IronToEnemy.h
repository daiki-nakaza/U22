#pragma once

#include "DxLib.h"
#include "Enemy.h"
#include "Bullet.h"
#include "accessory.h"
#include "Player.h"


bool IronToEnemy(WalkEnemy enemy);			//“S‹…‚Æ“G‚Ì“–‚½‚è”»’è
bool IronToEnemy(ShootEnemy enemy);			//“S‹…‚Æ“G‚Ì“–‚½‚è”»’è

//bool IronToEnemy(BulletInfo Bullet);			//“S‹…‚Æ“G‚Ì’eŠÛ‚Ì“–‚½‚è”»’è

bool PlayerToEnemy(BulletInfo Bullet);			//ƒvƒŒƒCƒ„[‚Æ’eŠÛ‚Ì“–‚½‚è”»’è

bool IronToBullet(BulletInfo Bullet);			//ƒvƒŒƒCƒ„[‚Æ’eŠÛ‚Ì“–‚½‚è”»’è

