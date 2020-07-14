#include "DxLib.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Define.h"
#include "Map.h"
#include "IronToEnemy.h"


//////////////////////////////////////////////
////////////�e�ۂ̊֐��̒�`///////////////////
//////////////////////////////////////////////
void BulletInfo::Init(const int Ex, const int Ey) {			//�e�ۂ̏���������
	const int valanceY = 10;		//�e�ۂ̍����̕␳�l

	Speed = 4;							//�e�ۂ̃X�s�[�h

	x = Ex;		//�G�L�����̍��W��Set
	y = Ey - valanceY;

	w = BULLET_W;
	h = BULLET_H;

	

	DispFlg = true;			//�\���t���O���I���ɂ���
}

void BulletInfo::Move(const int dir) {			//�e�ۂ̏���
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

void BulletInfo::Disp() {			//�e�ۂ̕\������
	if (DispFlg) {
		DrawBox(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE,
			x + w + MapDrawPointX - MapX * MAP_SIZE, y + h - MapDrawPointY - MapY * MAP_SIZE, 0x000000, true);
	}
}
