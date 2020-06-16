#include "DxLib.h"

#include "Player.h"
#include "Map.h"


//�v���C���[�̈ʒu
int PlayerX, PlayerY;              //0�`��ʔ����܂ŁB�i�v���C���[�ʒu�j
int Map_PlayerX, Map_PlayerY;      //�}�b�v�S�̂̃X�N���[���ʒu�i�}�b�v�ʒu�j
int OldX, OldY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�
int Map_OldX, Map_OldY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�

void PlayerInit() {

	// �v���C���[�̏����ʒu���Z�b�g
	PlayerX = 200;
	PlayerY = 200;
	Map_PlayerX = 0;
	Map_PlayerY = 0;

}

void PlayerMove() {

	int i = 0, j = 0, w = 0, z = 0;//���[�J���Ȃ̂ŋC�ɂ��Ȃ��ł�������!�����蔻��p�̕␳�l

	////�v���C���[�d��
	//PlayerY += GRAVITY;
	

	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�
	OldX = PlayerX;
	OldY = PlayerY;
	Map_OldX = Map_PlayerX;
	Map_OldY = Map_PlayerY;
	

	// �L�[���͂ɉ����ăv���C���[�̍��W���ړ�
	if (g_NowKey & PAD_INPUT_LEFT) PlayerX -= 2;
	if (g_NowKey & PAD_INPUT_RIGHT) PlayerX += 2;
	if (g_NowKey & PAD_INPUT_UP) PlayerY -= 2;
	if (g_NowKey & PAD_INPUT_DOWN) PlayerY += 2;

	
		

//	DrawFormatString(0, 0, 0x000000, "%d", PlayerY);
//	DrawFormatString(0, 20, 0x000000, "%d", Map_PlayerY);

	if (PlayerX > 500) {
		PlayerX = 500;
		Map_PlayerX += 2;
	}
	if (PlayerX < 64) {
		PlayerX = 64;
		if (Map_PlayerX > 0) {
			Map_PlayerX -= 2;
		}

	}

	// �X���C�h�p�̂O����R�P�܂ł̒l
	MapDrawPointX = -(Map_PlayerX % MAP_SIZE);
	MapDrawPointY = -(Map_PlayerY % MAP_SIZE);

	MapX = (Map_PlayerX) / MAP_SIZE;
	MapY = (Map_PlayerY) / MAP_SIZE;

	MapChipNumX = 0;
	MapChipNumY = 0;
	for (int k = 1; MapX + (PlayerX / MAP_SIZE)  >= WIDTH * k; k++) {
		MapChipNumX += WIDTH;
		MapChipNumY += HEIGHT;
	}

	//���������ꍇ
	if (MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) + MapChipNumY > HEIGHT) {
	}

	//�v���C���[�ʒu���}�b�v���܂����ł���
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) - MapChipNumX > WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//�^�񒆂̈ʒu���}�b�v���܂����ł���
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX > WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}




	//// �d�͂��ז������������
	//if ( g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1)
	//{
	//	PlayerY -= GRAVITY;	
	//}

	// �i���s�\�ȃ}�b�v�������ꍇ�͈ړ��ł��Ȃ�
	if (g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) ) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) ) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE/2) / MAP_SIZE) - MapChipNumX - w] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE-1) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1
		)
	{
		PlayerX = OldX;
		PlayerY = OldY;
		Map_PlayerX = Map_OldX;
		Map_PlayerY = Map_OldY;

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
	PlayerY += GRAVITY;


	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�
	OldX = PlayerX;
	OldY = PlayerY;
	Map_OldX = Map_PlayerX;
	Map_OldY = Map_PlayerY;


	// �L�[���͂ɉ����ăv���C���[�̍��W���ړ�
	if (g_NowKey & PAD_INPUT_LEFT) PlayerX -= 2;
	if (g_NowKey & PAD_INPUT_RIGHT) PlayerX += 2;
	if (g_NowKey & PAD_INPUT_UP) PlayerY -= 32;
	if (g_NowKey & PAD_INPUT_DOWN) PlayerY += 2;




	//	DrawFormatString(0, 0, 0x000000, "%d", PlayerY);
	//	DrawFormatString(0, 20, 0x000000, "%d", Map_PlayerY);

	if (PlayerX > 500) {
		PlayerX = 500;
		Map_PlayerX += 2;
	}
	if (PlayerX < 64) {
		PlayerX = 64;
		if (Map_PlayerX > 0) {
			Map_PlayerX -= 2;
		}

	}

	// �X���C�h�p�̂O����R�P�܂ł̒l
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

	//���������ꍇ
	if (MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) + MapChipNumY > HEIGHT) {
	}

	//�v���C���[�ʒu���}�b�v���܂����ł���
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE) / MAP_SIZE) - MapChipNumX > WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//�^�񒆂̈ʒu���}�b�v���܂����ł���
	if (MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX > WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}




	// �d�͂��ז������������
	if (g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1)
	{
		PlayerY -= GRAVITY;
	}

	// �i���s�\�ȃ}�b�v�������ꍇ�͈ړ��ł��Ȃ�
	if (g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY + j][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) - MapChipNumX - i] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1
		|| g_MapChip[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE) + CHA_SIZE - 1) / MAP_SIZE) + MapChipNumY + z][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE) + CHA_SIZE / 2) / MAP_SIZE) - MapChipNumX - w] != 1
		)
	{
		PlayerX = OldX;
		PlayerY = OldY;
		Map_PlayerX = Map_OldX;
		Map_PlayerY = Map_OldY;

	}
}