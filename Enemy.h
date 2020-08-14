#pragma once

#include "DxLib.h"

#include "Bullet.h"
#include "Define.h"



struct enemyInfo
{
	int x, y;			//�G��X���W�AY���W
	int w, h;			//�G�̕��ƍ���
	int direct;			//�G�̌��� (�E:1  ��:-1)
	int speed;			//�G�̃X�s�[�h
	int type;			//�G�̃^�C�v//��x�U������������炵�΂炭���G
	int outtime;		

	int pic;			//�摜�p�ϐ�
	int anm;			//�A�j���[�V�����p�ϐ�
	bool picDir;			//�摜�̌���

	bool DispFlg = false;		//�G���̕\���̃t���O
	bool AttckFlg = false;		//�G�̍U���t���O

	int Life = 0;				//�G�̃��C�t


	void Disp();				//�G�̕`�揈��
	void Move();
};


//�����G�̍\����
struct WalkEnemy : public enemyInfo
{
	void Init(int Tempx,int Tempy);			//�p�j���Ă���G�̏���������
	void WalkMove();			//�p�j���Ă���G�̏���
	void Disp();
};


//�܂��������G�̍\����
struct ShootEnemy : public enemyInfo
{
	NormalBullet Bullet[Bullet_MAX];			//�^���������G���g���e�ۂR��

	void Init(int Tempx, int Tempy);			//���G�̏���������
	void ShootMove();			//���G�̏���

};


//�_�����G�̍\����
struct LockShootEnemy : public enemyInfo
{

	LockBullet Bullet[Bullet_MAX];			//�e��3��

	void Init(int Tempx, int Tempy);			//�_�����G�̏���������
	void LockShootMove();			//���G�̏���

};

//��Ԃ̓G(��Ɍ������Ēe���΂��z)
struct TankEnemy : public enemyInfo
{
	ChargeBullet Bullet[Bullet_MAX];		//�e��3��

	void Init(int Tempx, int Tempy);			//��Ԃ̏���������
	void TankMove();		//��Ԃ̏���
};

struct RazerEnemy : public enemyInfo
{
	RazerBullet Bullet;			//�g���C�ϐ�

	int pic[3];

	void Init(int Tempx, int Tempy);
	void ShotMove();
	void Disp();
};


/**********************************************
*�@�@�֐��̃v���g�^�C�v�錾
*********************************************/
void enemyDisp();			//�G�̕`�揈��
void enemyMove();			//�G�̓���
void enemyInit();			//�G�̏���������

bool EnemyCheckHit(int x,int y,int direct);		//�G���̓����蔻��`�F�b�N
bool CheckWindow(int x);							//�E�B���h�E�̒��ɂ��邩�ǂ��� �����Ă�����true

//void EnemyShoot();



/*********************************************
*�ϐ��̐錾
*******************************************/

//�G���[�h�~�p�i��ŏ����܂��j
extern enemyInfo g_Enemy[ENEMY_MAX];


extern WalkEnemy g_WalkEnemy[ENEMY_MAX];			//�����G
extern ShootEnemy g_ShootEnemy[ENEMY_MAX];			//�^���������G
extern LockShootEnemy g_LockShootEnemy[ENEMY_MAX];			//�_�����G
extern TankEnemy g_TankEnemy[ENEMY_MAX];			//�ԂƗ΂̒e�ۂ����G
extern RazerEnemy g_RazerEnemy[ENEMY_MAX];					//�g���C�̓G

//extern BulletInfo Bullet[]

