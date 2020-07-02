#include "DxLib.h"

#include "Player.h"
#include "Map.h"


//�v���C���[�̈ʒu
int PlayerX, PlayerY;              //0�`��ʔ����܂ŁB�i�v���C���[�ʒu�j
int Map_PlayerX, Map_PlayerY;      //�}�b�v�S�̂̃X�N���[���ʒu�i�}�b�v�ʒu�j
int NewX, NewY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�
int Map_NewX, Map_NewY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�
int Jump_Flg;
int y_temp;
int y_prev;

void PlayerInit() {

	// �v���C���[�̏����ʒu���Z�b�g
	PlayerX = 200;
	PlayerY = 200;
	Map_PlayerX = 0;
	Map_PlayerY = 0;

	Jump_Flg = false;

}

void PlayerMove() {

	int i = 0, j = 0, w = 0, z = 0;//���[�J���Ȃ̂ŋC�ɂ��Ȃ��ł�������!�����蔻��p�̕␳�l

	//�v���C���[�d��
	PlayerGravity();
	

	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�
	NewX = PlayerX;
	NewY = PlayerY;
	Map_NewX = Map_PlayerX;
	Map_NewY = Map_PlayerY;
	

	// �L�[���͂ɉ����ăv���C���[�̍��W���ړ�
	if (g_NowKey & PAD_INPUT_LEFT) NewX -= 2;
	if (g_NowKey & PAD_INPUT_RIGHT) NewX += 2;
	if (g_NowKey & PAD_INPUT_UP) {
		if (Jump_Flg == 0) {
			y_prev = PlayerY;
			NewY -= 16;
			Jump_Flg = 1;
		}
		else if (Jump_Flg == 3) {
			Jump_Flg = 1;
		}
	}
	if (g_NowKey & PAD_INPUT_DOWN) NewY += 2;

	
	
	

	DrawFormatString(0, 0, 0xffffff,"%d", Jump_Flg);
		

	if (NewX > 500) {
		NewX = 500;
		Map_NewX += 2;
	}
	if (NewX < 64) {
		NewX = 64;
		if (Map_NewX > 0) {
			Map_NewX -= 2;
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
	if (MapY + ((NewY + (Map_NewX % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) + MapChipNumY >= HEIGHT) {
	}

	//�v���C���[�ʒu���}�b�v���܂����ł���
	if (MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//�^�񒆂̈ʒu���}�b�v���܂����ł���
	if (MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}


	// �i���s�\�ȃ}�b�v�������ꍇ�͈ړ��ł��Ȃ�
	if (g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) + MapChipNumY][MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) ) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) + MapChipNumY + j][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) ) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE/2) / MAP_SIZE) - MapChipNumX - w] != 1
		|| g_MapChip[MapY + ((NewY + (Map_NewY % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) + MapChipNumY + z][MapX + ((NewX + (Map_NewX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1
		)
	{
		
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
	else {//�ړ��ł���
		PlayerX = NewX;
		PlayerY = NewY;
		Map_PlayerX = Map_NewX;
		Map_PlayerY = Map_NewY;
	}
}

void PlayerDisp() {
	// �v���C���[�̕`��
	DrawBox((PlayerX), (PlayerY),
		(PlayerX)+CHA_SIZE, (PlayerY)+CHA_SIZE,
		GetColor(255, 255, 255), TRUE);//�����ɓ����蔻�肠��
}

void PlayerGravity() {
	int i = 0, j = 0, w = 0, z = 0;//���[�J���Ȃ̂ŋC�ɂ��Ȃ��ł�������!�����蔻��p�̕␳�l

	//�v���C���[�d��
	NewY = PlayerY;

	if (Jump_Flg == 0 || Jump_Flg == -1) {
		NewY += GRAVITY;
	}
	//�W�����v����
	else if (Jump_Flg == 4 || Jump_Flg == 6) {
		y_temp = NewY;
		NewY += (NewY - y_prev) + 2;
		y_prev = y_temp;
		Jump_Flg = 5;
	}
	else if (Jump_Flg == 2) {
		y_temp = NewY;
		NewY += (NewY - y_prev) + 1;
		y_prev = y_temp;
		//NewY -= 12;
		Jump_Flg = 3;
	}
	else if(Jump_Flg>0){
		Jump_Flg++;
	}

	// �X���C�h�p�̂O����R�P�܂ł̒l
	MapDrawPointY = -(Map_PlayerY % MAP_SIZE);

	MapY = (Map_PlayerY) / MAP_SIZE;

	MapChipNumX = 0;
	MapChipNumY = 0;
	for (int k = 1; MapX + ((NewX + (Map_NewX % MAP_SIZE)) / MAP_SIZE) >= WIDTH * k; k++) {
		MapChipNumX += WIDTH;
		MapChipNumY += HEIGHT;
	}


	//�v���C���[�ʒu���}�b�v���܂����ł���(�E�������j
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) - MapChipNumX >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//�^�񒆂̈ʒu���}�b�v���܂����ł���
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX  >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}
	//DrawFormatString(x * MAP_SIZE + MapDrawPointX, y * MAP_SIZE + MapDrawPointY, 0xffffff, "%d %d", y + MapY + MapChipNumY, x + MapX + MapChipNumX);





	// �i���s�\�ȃ}�b�v�������ꍇ�͏d�͂�����
	if (g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w ] != 1
		|| g_MapChip[MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1
		)
	{
		if (Jump_Flg == -1) {
			PlayerY = (NewY / MAP_SIZE) * MAP_SIZE + CHA_SIZE % MAP_SIZE;
			Jump_Flg = 0;
			//(MapY + ((NewY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY) * 32;
		}
		else if(Jump_Flg != 0) 
		{
			Jump_Flg = -1;
		}
		
		
	}
	else {
		PlayerY = NewY;
		
	}
}