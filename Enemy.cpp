#include "DxLib.h"

#include "Enemy.h"
#include "Define.h"
#include "Map.h"

#include "PlayerAndIronBall.h"

#define ENEMY_SIZE 48	//�G�̑傫��

/**************************************************
*		�ϐ��̐錾
***************************************************/
enemyInfo g_Enemy;			//�G�̏����������ϐ�


/***************************************************
*�@�@�G�̍\���̂̊֐��̒�`
*****************************************************/
void enemyInfo::WalkInit() {                 // �G�̏�����
	x = 24 * MAP_SIZE;							 // �G��X���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	y = 15 * MAP_SIZE;								    // �G��Y���W�̏����ʒu(�}�b�v�`�b�v�̏ꏊ)
	w = ENEMY_SIZE;						//�G�̉���
	h = ENEMY_SIZE;						//�G�̏c

	LoadDivGraph("images/MouseAll.png", 4, 4, 1, ENEMY_SIZE, ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//����������n�߂�

	speed = 1;						//�G�̃X�s�[�h
	picDir = true;

	chipY = ((y + MapDrawPointY) / MAP_SIZE) + MapY;
	chipX = ((x - MapDrawPointX) / MAP_SIZE) + MapX;

	DispFlg = TRUE;					//�G��\��


}

void enemyInfo::Disp() {

	if (DispFlg) {		//�G�\��
		DrawBox(x,y, x + w, y + h, 0xff0000, true);
		//DrawRotaGraphFast2(x, y,0,0,1,0, pic[anm], true,picDir);
	}
	else {				//�G��\��

	}
	/*for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH + 1; x++) {
			DrawFormatString(x * MAP_SIZE + 16, y * MAP_SIZE + 16, 0xf0f0f0, "%d", g_MapChip[y + MapY + MapChipNumY][x + MapX + MapChipNumX]);
		}
	}*/
}

void enemyInfo::WalkMove(){

	static int AnmCnt = 0;

	const int FrmMax = 10;		//�A�j���[�V�����t���[���̊�



	if (DispFlg) {
		if (g_MapChip[((y + h/2) / MAP_SIZE + MapY) + 1][(x / MAP_SIZE + MapX)] == 1) {			//�P���̃}�X�����ċ󒆂�������
			g_Enemy.y += GRAVITY;
		}

		if (EnemyCheckHit(g_Enemy)) {	//���̃t���[���̈ړ�������ĕǂ�������
			direct *= -1;			//�ړ��̌����𔽓]������
		}

		if (direct < 0) picDir = false;		//�������Ȃ�
		else picDir = true;					//�E�����Ȃ�

		//x = (chipX * MAP_SIZE - MapDrawPointX) + direct * speed;				//�ړ��̃X�s�[�h��G�L�����ɓ����
		x += direct * speed;

		if (++AnmCnt >= FrmMax) {
			if (++anm > 3) anm = 0;
			AnmCnt = 0;
		}

		chipY = ((y + MapDrawPointY) / MAP_SIZE) + MapY;
		chipX = ((x - MapDrawPointX) / MAP_SIZE) + MapX;

	}

}

/**************************************************
*�@�G�̊֐��̒�`
***************************************************/
void enemyDisp() {
	g_Enemy.Disp();
}

void enemyMove() {
	static int Initflg = true;

	if (Initflg) {
		g_Enemy.WalkInit();

		Initflg = false;
	}
	if (g_Enemy.DispFlg) {
		g_Enemy.WalkMove();
	}
}

bool EnemyCheckHit(enemyInfo enemy) {
	if (enemy.picDir)			//�E�����̏���
	{
		//���̈ړ��̏ꏊ���G�L�����̉E�[�ɕǂ��d�Ȃ�����true��Ԃ�
		if 
			(g_MapChip[(enemy.y + enemy.h + MapDrawPointY) / MAP_SIZE + MapY]
			[(((enemy.x + enemy.w - MapDrawPointX)+(enemy.direct * enemy.speed)) / MAP_SIZE) + MapX] == 0) return true;

	}
	else {							//�������̏���
		//���̈ړ��̏ꏊ���G�L�����̍��[�ɕǂ��d�Ȃ�����X�s�[�h�𔽓]����
		if
			(g_MapChip[(enemy.y + enemy.h + MapDrawPointY) / MAP_SIZE + MapY]
			[((enemy.x - MapDrawPointX + (enemy.direct * enemy.speed)) / MAP_SIZE) + MapX] == 0) return true;
	}

	if (IronToEnemy()) return true;

	return false;
}