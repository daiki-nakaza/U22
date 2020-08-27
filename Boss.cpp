#include "DxLib.h"

#include "Boss.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Define.h"
#include "Map.h"
#include "IronToEnemy.h"

#include <time.h>


/******************************************
*****************�{�X**********************
*******************************************/
Boss g_Boss;			//�{�X�̍\���̕ϐ�

int SetTP;


void Boss::BossInit(int Tempx, int Tempy) {
	int SetX = Tempx * (MAP_SIZE)/* + (((Tempy / HEIGHT) * WIDTH) * WIDTH)*/, SetY = (Tempy % HEIGHT) * MAP_SIZE;


	x = SetX;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = SetY - (BOSS_H - MAP_SIZE);								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

	TPSpace[0][TP_MAX - 1] = SetX;								// �G��TP���X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	TPSpace[1][TP_MAX - 1] = SetY - (BOSS_H - MAP_SIZE);		// �G��TP���Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

	w = BOSS_W;						//�G�̉���
	h = BOSS_H;						//�G�̏c

	pic = LoadGraph("images/rasubosu.png");

	anm = 0;

	direct = -1;						//����������n�߂�
	picDir = true;

	speed = 2;						//�G�̃X�s�[�h

	Life = 3;					//�G��HP�@�Ƃ�܂R

	type = 0;					//�G�̃^�C�v

	outtime = 0;				//�P�x�U������������疳�G


	DispFlg = TRUE;					//�G��\��
}

void Boss::TPInit(int Tempx, int Tempy) {
	int SetX = Tempx * MAP_SIZE + (((Tempy / HEIGHT) * WIDTH) * WIDTH), SetY = (Tempy % HEIGHT) * MAP_SIZE;

	TPSpace[0][SetTP] = SetX;								// �G��TP���X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	TPSpace[1][SetTP] = SetY - (BOSS_H - MAP_SIZE) + 3;		// �G��TP���Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)

	if (SetTP++ >= TP_MAX - 2) SetTP = TP_MAX - 2;

}


//****************�{�X�̓���*******************//

void Boss::BossMove() {
	Move();
}



//****************�{�X�̕\��*******************//
void Boss::Disp() {
	if (DispFlg && CheckWindow()) {		//�G�\��
		if (outtime == 0) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2,
				1, 0, pic, true, picDir);
		}
		else if (outtime % 2 == 1) {
			DrawRotaGraph(x + MapDrawPointX - MapX * MAP_SIZE + w / 2, y - MapDrawPointY - MapY * MAP_SIZE + h / 2,
				1, 0, pic, true, picDir);
		}
	}
	else {				//�G��\��

	}
}
