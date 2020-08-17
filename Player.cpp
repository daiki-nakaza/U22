#include "DxLib.h"
#include "Math.h"

#include "Player.h"
#include "Map.h"
#include "PlayerAndIronBall.h"
#include "Enemy.h"
#include "IronToEnemy.h"


//�f�o�b�N�p
bool DebugMode = false;


//�v���C���[�̈ʒu
int PlayerX, PlayerY;              //0�`��ʔ����܂ŁB�i�v���C���[�ʒu�j
int Map_PlayerX, Map_PlayerY;      //�}�b�v�S�̂̃X�N���[���ʒu�i�}�b�v�ʒu�j
int NewX, NewY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�
int Map_NewX, Map_NewY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�
int Jump_Flg;
int y_temp;
int y_prev;
int Down_flg;//���Ⴊ�݂̃t���O

int Bectl;
int Attack;

int Player_Pic[4];
int Player_Pic_R[4];

int Player_Pic_Attack[6];
int Player_Pic_Attack_R[6];

int Player_Pic_Down;
int Player_Pic_Down_R;

int Player_Pic_Hold[4];//�v���C���[���S���������Ĉړ�����摜
int Player_Pic_Hold_R[4];//�t�v���C���[���S���������Ĉړ�����摜

void PlayerInit() {

	// �v���C���[�̏����ʒu���Z�b�g
	PlayerX = 200;//200
	PlayerY = 54;//544
	Map_PlayerX = 0;
	Map_PlayerY = 0;

	Jump_Flg = false;

	Bectl = 0;//�O�͉E�����A�P�͍�����
	Attack = 0;//�O�͍U���\
	Down_flg = 0;//�O�͂��Ⴊ��łȂ��P�͂��Ⴊ��ł���

}

void PlayerMove() {

	int i = 0, j = 0, w = 0, z = 0;//���[�J���Ȃ̂ŋC�ɂ��Ȃ��ł�������!�����蔻��p�̕␳�l
	int flg = 0;//���[�J���ϐ��ŁA�G�Ƃ̓����蔻��ɂ����Ă��܂�

	//�v���C���[�d��
	PlayerGravity();
	

	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�
	NewX = PlayerX;
	NewY = PlayerY;
	Map_NewX = Map_PlayerX;
	Map_NewY = Map_PlayerY;

	//���Ⴊ�݂̃t���O�𖈉�O�ɂ���
	Down_flg = 0;

	if (DebugMode) {
		DrawFormatString(500, 0, 0xffffff, "%d", Locka.WI);
	}

	//�Ԃ牺�����Ă���t���O
	if (Locka.WI > 0) {
		Locka.HenkaX += 2;
		NewX += 2;
	//	Locka.WI = 0;
	}
	else if (Locka.WI < 0) {
		Locka.HenkaX -= 2;
		NewX -= 2;
	//	Locka.WI = 0;
	}


	//�L�[���͂ɉ����ăv���C���[�̍��W���ړ� ��
	if (g_NowKey & PAD_INPUT_UP && g_IronBall.HoldFlg == false && g_IronBall.ThrowFlg == false && !(g_NowKey & PAD_INPUT_1)) {
		if (Jump_Flg == 0) {
			y_prev = PlayerY;
			NewY -= 16;
			Locka.HenkaY -= 16;
			Jump_Flg = 1;
		}
		else if (Jump_Flg == 3) {
			Jump_Flg = 1;
		}
	}
	//  ��
	if (g_NowKey & PAD_INPUT_LEFT && g_IronBall.ThrowFlg == false && !(g_NowKey & PAD_INPUT_1) && Jump_Flg != -2) {
		NewX -= 2;
		Locka.HenkaX -= 2;
		if (g_IronBall.HoldFlg == true) {//�S���������Ă���ꍇ
			Locka.LenkaX -= 2;
		}

		if (Attack < 10 && g_IronBall.ThrowFlg == false) {
			Bectl = 1;
		}
		if (Locka.RD > 0) {
			Locka.RD = 0;
		}
	}
	//�E
	if (g_NowKey & PAD_INPUT_RIGHT && g_IronBall.ThrowFlg == false && !(g_NowKey & PAD_INPUT_1) && Jump_Flg != -2) {
		NewX += 2; 
		Locka.HenkaX += 2;
		if (g_IronBall.HoldFlg == true) {//�S���������Ă���ꍇ
			Locka.LenkaX += 2;
		}

		//�U�����Ă��炸�A�S���𓊂��Ă��Ȃ��Ƃ����������Ă�������������邱�Ƃ��ł���B
		if (Attack < 10 && g_IronBall.ThrowFlg == false) {
			Bectl = 0;
		}
		if (Locka.RD < 0) {
			Locka.RD = 0;
		}
	}
	
	//���Ⴊ�ݗp�A���R��������Jump_Flg��-1�Ȃ̂ŁA�n�ʂɂ��Ă���Ƃ�������p����
	if (g_NowKey & PAD_INPUT_DOWN && Jump_Flg == 0 && g_IronBall.HoldFlg == false && g_IronBall.ThrowFlg == false && !(g_NowKey & PAD_INPUT_1)) {
		PlayerY += 16;
		NewY += 16; 
		Down_flg = 1;
	}

	//���̈ړ��ł��邩����
	//Locka.HenkaY = 0;
	Locka.MoveCheck();
	
	
	if (DebugMode) {
		DrawFormatString(0, 0, 0xffffff, "%d", Jump_Flg);
	}

	if (NewX > 500) {
		Map_NewX += NewX - 500;
		NewX = 500;
	}
	if (NewX < 64) {
		if (Map_NewX > 0) {
			Map_NewX -= 64 - NewX;
			NewX = 64;
		}
		
	}

	// �X���C�h�p�̂O����R�P�܂ł̒l
	MapDrawPointX = -(Map_NewX % MAP_SIZE);
	MapDrawPointY = -(Map_NewY % MAP_SIZE);

	MapX = (Map_NewX) / MAP_SIZE;
	MapY = (Map_NewY) / MAP_SIZE;

	MapChipNumX = 0;
	MapChipNumY = 0;
	for (int k = 1; MapX + ((NewX+ (Map_NewX % MAP_SIZE)) / MAP_SIZE)  >= WIDTH * k; k++) {
		MapChipNumX += WIDTH;
		MapChipNumY += HEIGHT;
	}

	//���������ꍇ
	if (MapY + ((NewY + (Map_NewX % MAP_SIZE) + CHA_SIZE_Y-1) / MAP_SIZE) + MapChipNumY >= HEIGHT) {
		//g_GameState = GAME_OVER;
	}

	//�v���C���[�ʒu���}�b�v���܂����ł���
	if (MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X-1) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//�^�񒆂̈ʒu���}�b�v���܂����ł���
	if (MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}

	//�G�L�������ړ�����ꏊ�ɂ�����߂�
	for (int a = 0; a < ENEMY_MAX; a++) {
		flg = PlayerMoveCheck(g_WalkEnemy[a]);
		flg = PlayerMoveCheck(g_ShootEnemy[a]);
		flg = PlayerMoveCheck(g_LockShootEnemy[a]);
		flg = PlayerMoveCheck(g_TankEnemy[a]);
		flg = PlayerMoveCheck(g_RazerEnemy[a]);
	}

	//�S���̒��ɓ������ꍇ�B//���Ƃŏ���

	

	// �i���s�\�ȃ}�b�v�������ꍇ�͈ړ��ł��Ȃ�//�S��������//���̒��������v���ǂ���
	if (g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1												//����
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1								//����
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1						//���^��
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] != 1						//�E��
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] != 1			//�E��
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] != 1			//�E�^��
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] != 1						//�^�񒆏�
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] != 1		//�^�񒆉�
		||		(g_IronBall.x - NewX - Map_NewX < CHA_SIZE_X + IRONBALL_R
			  && g_IronBall.y - NewY - Map_NewY < CHA_SIZE_Y - 1 + IRONBALL_R
			  && g_IronBall.x - NewX - Map_NewX > 0 - IRONBALL_R
			  && g_IronBall.y - NewY - Map_NewY > 0 - IRONBALL_R
			  && g_IronBall.HoldFlg == false)
		//|| (pow((double)g_IronBall.x - (double)NewX - (double)Map_NewX - (double)CHA_SIZE_X / 2.0, 2.0) + pow((double)g_IronBall.y - (double)NewY - (double)Map_NewY - (double)CHA_SIZE_Y / 2.0, 2.0) > pow((double)MAP_SIZE * 9.0, 2.0))
		|| flg == 1
		|| (Locka.HenkaX != 0 || Locka.HenkaY != 0)
		)
	{
		//�ǂɂ������āA�����ɂ͂������Ȃ�ړ������������ɖ߂�
		//if (Locka.HenkaX == 0 && Locka.HenkaY == 0) {
			for (int i = 0; i < LOCK_MAX; i++) {
				Locka.New_x[i] = Locka.x[i];
				Locka.New_y[i] = Locka.y[i];
			}
		//}
		if (Locka.HenkaX > 0 ) {
			Locka.RD = 2;
		}
		else if (Locka.HenkaX < 0) {
			Locka.RD = -2;
		}
		
		Locka.HenkaX = 0;
		Locka.HenkaY = 0;

		if (Locka.LenkaX != 0 || Locka.LenkaY != 0) {
			g_IronBall.x -= Locka.LenkaX;
			Locka.LenkaX = 0;
			Locka.LenkaY = 0;
		}

		MapDrawPointX = -(Map_PlayerX % MAP_SIZE);
		MapDrawPointY = -(Map_PlayerY % MAP_SIZE);

		MapX = (Map_PlayerX) / MAP_SIZE;
		MapY = (Map_PlayerY) / MAP_SIZE;

		MapChipNumX = 0;
		MapChipNumY = 0;
		for (int k = 1; MapX + (PlayerX / MAP_SIZE) >= WIDTH * k; k++) {
			MapChipNumX += WIDTH;
			MapChipNumY += HEIGHT;
		}
		
	}
	else {	
			PlayerX = NewX;
			PlayerY = NewY;
			Map_PlayerX = Map_NewX;
			Map_PlayerY = Map_NewY;

			Locka.LenkaX = 0;//�ړ������Ȃ�A�S���Ɉ��������Ă��Ă��A�����Ƃ������ƂłO�ɂ���
			Locka.LenkaY = 0;//�ړ������Ȃ�A�S���Ɉ��������Ă��Ă��A�����Ƃ������ƂłO�ɂ���

	}
	Locka.Move();
	
}

void PlayerDisp() {
	static int i = 0;
	//return;
	//DrawBox((PlayerX), (PlayerY),
	//	(PlayerX)+CHA_SIZE_X, (PlayerY)+CHA_SIZE_Y,
	//	GetColor(255, 255, 255), TRUE);//�����ɓ����蔻�肠��
	//DrawGraph(PlayerX, PlayerY, Player_Pic[0], false);
	// �v���C���[�̕`��E
	if (g_NowKey & PAD_INPUT_RIGHT && Bectl == 0 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic[i/10], true);
		if (++i >= 40) {
			i = 0;
		}
	}
	else if(Bectl == 0 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == false){
		i = 0;
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic[0], true);
	}

	// �v���C���[�̕`�捶
	else if (g_NowKey & PAD_INPUT_LEFT && Bectl == 1 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_R[3 - i / 10], true);
		if (++i >= 40) {
			i = 0;
		}
	}
	else if (Bectl == 1 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
		i = 0;
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_R[3], true);
	}
	//�v���C���[���S���������Ă���摜�E
	else if (g_NowKey & PAD_INPUT_RIGHT && Bectl == 0 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == true) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Hold[i / 10], true);
		if (++i >= 40) {
			i = 0;
		}
	}
	else if (Bectl == 0 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == true) {
		i = 0;
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Hold[0], true);
	}

	//�v���C���[���S���������Ă���摜�E
	else if (g_NowKey & PAD_INPUT_LEFT && Bectl == 1 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == true) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Hold_R[3 - i / 10], true);
		if (++i >= 40) {
			i = 0;
		}
	}
	else if (Bectl == 1 && Attack < 10 && Down_flg == 0 && g_IronBall.HoldFlg == true) {
		i = 0;
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Hold_R[3], true);
	}

	//�U���p�摜�E
	if (Attack >= 10 && Bectl == 0 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X*2, PlayerY + CHA_SIZE_Y, Player_Pic_Attack[5 - Attack/5], true);
	}
	//�U���p�摜��
	else if (Attack >= 10 && Bectl == 1 && Down_flg == 0 && g_IronBall.HoldFlg == false) {
		DrawExtendGraph(PlayerX - CHA_SIZE_X, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y, Player_Pic_Attack_R[Attack / 5], true);
	}

	//���Ⴊ�݉摜
	if (Bectl == 0 && Attack < 10 && Down_flg == 1 && g_IronBall.HoldFlg == false) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y/4*3, Player_Pic_Down, true);
	}
	else if (Bectl == 1 && Attack < 10 && Down_flg == 1 && g_IronBall.HoldFlg == false) {
		DrawExtendGraph(PlayerX, PlayerY, PlayerX + CHA_SIZE_X, PlayerY + CHA_SIZE_Y/4*3, Player_Pic_Down_R, true);
	}
	if (DebugMode) {
		DrawCircle(Locka.x[0] + MapDrawPointX - MapX * MAP_SIZE, Locka.y[0] - MapDrawPointY - MapY * MAP_SIZE, 4, GetColor(252, 252, 252), true);
		DrawCircle(Locka.x[1] + MapDrawPointX - MapX * MAP_SIZE, Locka.y[1] - MapDrawPointY - MapY * MAP_SIZE, 4, GetColor(252, 50, 252), true);
	}
}

void PlayerGravity() {
	int i = 0, j = 0, w = 0, z = 0;//���[�J���Ȃ̂ŋC�ɂ��Ȃ��ł�������!�����蔻��p�̕␳�l
	int flg = 0;//���[�J���ϐ��ł��B�G�L�������ړ�����ꏊ�ɂ��邩�ǂ����̃t���O


	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�
	NewX = PlayerX;
	NewY = PlayerY;
	Map_NewX = Map_PlayerX;
	Map_NewY = Map_PlayerY;

	//�v���C���[�d��
	NewY = PlayerY;

	if (Jump_Flg == 0 || Jump_Flg == -1 || Jump_Flg == -2) {
		NewY += GRAVITY;
		if (Jump_Flg == -1 || Jump_Flg == -2) {
			Locka.HenkaY += GRAVITY;
		}
		
	}
	//�W�����v����
	else if (Jump_Flg == 4 || Jump_Flg == 6) {
		y_temp = NewY;
		Locka.HenkaY += (NewY - y_prev) + 2;
		NewY += (NewY - y_prev) + 2;
		y_prev = y_temp;
		Jump_Flg = 5;
	}
	else if (Jump_Flg == 2) {
		y_temp = NewY;
		Locka.HenkaY += (NewY - y_prev) + 1;
		NewY += (NewY - y_prev) + 1;
		y_prev = y_temp;
		//NewY -= 12;
		Jump_Flg = 3;
	}
	else if(Jump_Flg>0){
		Jump_Flg++;
	}

	//���̈ړ�����
	Locka.MoveCheck();

	if (NewX > 500) {
		Map_NewX += NewX - 500;
		NewX = 500;
	}
	if (NewX < 64) {
		if (Map_NewX > 0) {
			Map_NewX -= 64 - NewX;
			NewX = 64;
		}

	}

	// �X���C�h�p�̂O����R�P�܂ł̒l
	MapDrawPointX = -(Map_NewX % MAP_SIZE);
	MapDrawPointY = -(Map_NewY % MAP_SIZE);

	MapX = (Map_NewX) / MAP_SIZE;
	MapY = (Map_NewY) / MAP_SIZE;

	MapChipNumX = 0;
	MapChipNumY = 0;
	for (int k = 1; MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) >= WIDTH * k; k++) {
		MapChipNumX += WIDTH;
		MapChipNumY += HEIGHT;
	}


	//�v���C���[�ʒu���}�b�v���܂����ł���(�E�������j
	if (MapX + ((NewX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X-1) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//�^�񒆂̈ʒu���}�b�v���܂����ł���
	if (MapX + ((NewX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX  >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}

	if (DebugMode) {
		//DrawFormatString(x * MAP_SIZE + MapDrawPointX, y * MAP_SIZE + MapDrawPointY, 0xffffff, "%d %d", y + MapY + MapChipNumY, x + MapX + MapChipNumX);
	}

	//�G�L�������ړ�����ꏊ�ɂ�����߂�
	for (int a = 0; a < ENEMY_MAX; a++) {
		flg = PlayerMoveCheck(g_WalkEnemy[a]);
		flg = PlayerMoveCheck(g_ShootEnemy[a]);
		flg = PlayerMoveCheck(g_LockShootEnemy[a]);
		flg = PlayerMoveCheck(g_TankEnemy[a]);
		flg = PlayerMoveCheck(g_RazerEnemy[a]);
	}

	

	// �i���s�\�ȃ}�b�v�������ꍇ�͏d�͂�����
	if (g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE_Y / 2 - 1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1						//���^��
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w ] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE_Y - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE_X / 2) / MAP_SIZE) - MapChipNumX - w] != 1	
		)
	{
		/*if (Jump_Flg != 0)
		{
			Jump_Flg = -1;
		}*/
		
		if (Jump_Flg == -1) {
			PlayerY = (NewY / MAP_SIZE) * MAP_SIZE + CHA_SIZE_Y % MAP_SIZE;
			Jump_Flg = 0;
		}
		else if(Jump_Flg != 0) 
		{
			Jump_Flg = -1;
		}
		else if (Jump_Flg == 0) {
			PlayerY = (NewY / MAP_SIZE) * MAP_SIZE + CHA_SIZE_Y % MAP_SIZE;
		}
		//�l���n�ʂɂ����Ƃ��͐l�Ɉ�ԋ߂��������͂��Ƃɖ߂�
		Locka.New_x[0] = Locka.x[0];
		Locka.New_y[0] = Locka.y[0];
		
	}//���̒��������v���ǂ���
	else if ( (Locka.HenkaX != 0 || Locka.HenkaY != 0)) 
	{
		if (Locka.HenkaX != 0 || Locka.HenkaY != 0) {
			for (int i = 0; i < LOCK_MAX; i++) {
				Locka.New_x[i] = Locka.x[i];
				Locka.New_y[i] = Locka.y[i];
	//			Jump_Flg = -2;//�����΂��邘������
			}
			Jump_Flg = -2;//�|�Q�ɂ��Ă�̂́A��������

			Locka.HenkaX = 0;
			Locka.HenkaY = 0;

			if (Locka.New_x[0] - Locka.New_x[1] > 0) {//���Ɉړ�
				Locka.WI = -1;
			}
			else if (Locka.New_x[0] - Locka.New_x[1] < 0) {
				Locka.WI = 1;
			}
			
		}

	}//�S��������ꍇ�ƓG�������ꍇ
	else if ((g_IronBall.x - PlayerX - Map_PlayerX < CHA_SIZE_X + IRONBALL_R
		  && g_IronBall.y - NewY - Map_PlayerY < CHA_SIZE_Y - 1 + IRONBALL_R
		  && g_IronBall.x - PlayerX - Map_PlayerX > 0 - IRONBALL_R
		  && g_IronBall.y - NewY - Map_PlayerY > 0 - IRONBALL_R
		  && g_IronBall.HoldFlg == false)
		  || flg==1) {
		if (Jump_Flg == -1) {
		//	PlayerY = (NewY / MAP_SIZE) * MAP_SIZE + CHA_SIZE_Y % MAP_SIZE;
			Jump_Flg = 0;
		}
		else if (Jump_Flg != 0)
		{
			Jump_Flg = -1;
		}
		for (int i = 0; i < LOCK_MAX; i++) {
			Locka.New_x[i] = Locka.x[i];
			Locka.New_y[i] = Locka.y[i];
		//	Jump_Flg = -2;//�����΂��邘������
		}
	}
	else {
		if (Jump_Flg == 0) {
			Jump_Flg = -1;
		}
		if (Jump_Flg == -2) {
			Jump_Flg = -1;
		}
		PlayerX = NewX;
		PlayerY = NewY;
		
	}

	

	Locka.HenkaY = 0;
	Locka.HenkaX = 0;
	
	Locka.Move();
	
}


//�U��
void PlayerAttack() {
	if (g_NowKey & PAD_INPUT_3 && g_IronBall.HoldFlg == false) {
		if (Attack == 0) {
			Attack = 30;
		}
	}

	if(--Attack > 0){
		for (int i = 0; i < ENEMY_MAX; i++) {
			PlayerAttackCheck(g_WalkEnemy[i]);
			PlayerAttackCheck(g_ShootEnemy[i]);
			PlayerAttackCheck(g_LockShootEnemy[i]);
			PlayerAttackCheck(g_TankEnemy[i]);
			PlayerAttackCheck(g_RazerEnemy[i]);
		}
	}
	else if (Attack < 0) {
		Attack = 0;
	}
}