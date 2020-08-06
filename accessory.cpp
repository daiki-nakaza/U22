#include "DxLib.h"
#include "Math.h"

#include "accessory.h"

#include "PlayerAndIronBall.h"
#include "Map.h"

/**************************************************
*		�ϐ��̐錾
***************************************************/
partsInfo g_IronBall;			//�S���̏����������ϐ�
Lock Locka;						//���̏����������ϐ�

/*****************************************************
*		�֐��̒�`
********************************************************/

//��������
void partsInfo::Init() {                 // �S���̏�����
	IronInit(&x, &y);		//���W���v���C���[�ׂ̗ɑ��
	New_x = x;
	New_y = y;

	r = IRONBALL_R;

	//LoadDivGraph("images/MouseAll.png", 4, 4, 1, ENEMY_SIZE, ENEMY_SIZE, pic);
	anm = 0;

	direct = -1;						//����������n�߂�

	speed = 2;						//�S���̃X�s�[�h
	picDir = true;

	DispFlg = TRUE;					//�S����\��


}

void Lock::Init() {
	LockInit(&x[0], &y[0]);
	for (int i = 0; i < LOCK_MAX; i++) {
		New_x[i] = x[i];
		New_y[i] = y[i];
		Wall[i] = 0;
	}

	ro = 4;

	HenkaX = 0;		//�l�̕ω���
	HenkaY = 0;		//�l�̕ω���

	LenkaX = 0;		//�S���̕ω���
	LenkaY = 0;		//�S���̕ω���

	HI = 0;//���������Ă���t���O
}

//�`�揈��
void partsInfo::Disp() {


	if (DispFlg) {		//�S���\��
		//DrawBox(x,y, x + w, y + h, 0x000000, true);
		//DrawRotaGraphFast2(x, y, 0, 0, 1, 0, pic, true, picDir);
	//	DrawCircle(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY * MAP_SIZE, MAP_SIZE * 9, 0xffffff, true);
		DrawCircle(x + MapDrawPointX - MapX * MAP_SIZE, y - MapDrawPointY - MapY*MAP_SIZE, r, 0x000000, true);
		DrawFormatString(30, 90, 0x000000, "Y = %d\nX = %d\n", /*Locka.x[LOCK_MAX-1]*/0, 0);
		if (HoldFlg)DrawFormatString(100, 30, 0x000000, "HOLD");
		if (ThrowFlg)DrawFormatString(100, 30, 0x000000, "THROW");
	}
	else {				//�S����\��

	}
}

void Lock::Disp() {
	for (int i = 0; i < LOCK_MAX; i++) {
		DrawCircle(x[i] + MapDrawPointX - MapX * MAP_SIZE, y[i] - MapDrawPointY - MapY * MAP_SIZE, ro, GetColor(252 - i*30,i*30,0), true);
	}
	DrawFormatString(30, 30, 0x000000, "Y = %d\nX = %d\n", x[0] + MapDrawPointX - MapX * MAP_SIZE, PlayerX+16);

}

//�ړ��ł��邩�ǂ����m���߂�
void Lock::MoveCheck() {
	int ox, oy;//���[�J���ϐ��A���P���̍��������Ă���
	bool Gr = true;//���[�J���ϐ��AHenkaY�̂Ƃ���Ŏg�p�B���ׂĂ̍����n�ʂɂ��Ă���Ȃ�HenkaY���Ȃ����B
	int EL = 0;//���[�J���ϐ��AHenkaX�̂Ƃ���Ŏg�p
	//HenkaY = 0;
	//LenkaY = 0;
	for (int i = 0; i < LOCK_MAX; i++) {
		New_x[i] = x[i];
		New_y[i] = y[i];
	}

	//�ړ��ʂȂ��Ȃ�I���
	if (HenkaX == 0 && HenkaY == 0 && LenkaX == 0 && LenkaY == 0) {
		return;
	}

	/*********************************
	*�S�����ړ������Ƃ��̕ω�
	*********************************/
	//y���W�̕ω�
	//�}�C�i�X�Ȃ�B��ɂ����B�v���X������
	if (LenkaY < 0) {
		for (int i = LOCK_MAX - 1; i > 0; i--) {

			//�ω��ʂȂ��Ȃ�u���C�N
			if (LenkaY == 0) {
				break;
			}

			//���̍���}��
			oy = New_y[i-1] - New_y[i];
			//���W�ړ�
			while (LenkaY != 0) {
				New_y[i]--;
				oy++;
				LenkaY++;
				if (HitCheck(i) == true) {//�ǂɓ������Ă���̂ō����E�Ɉړ�������
					New_y[i]++;//����������
					if (x[i] - x[i + 1] >= 0) {
						New_x[i]++;
						//HenkaX++;
					}
					else if (x[i] - x[i + 1] < 0) {
						New_x[i]--;
						//HenkaX--;
					}

				}
			}

			if (oy >= IRONBALL_R) {//�I�[�o�[������������ω��ʂɖ߂�
				LenkaY -= oy - IRONBALL_R;
			}

		}
	}
	else if (LenkaY > 0) {
		for (int i = LOCK_MAX - 1; i > 0; i--) {
			//�ω��ʂȂ��Ȃ�u���C�N
			if (LenkaY == 0) {
				break;
			}
			//���̍���}��
			oy = New_y[i] - New_y[i - 1];
			//���W�ړ�
			while (LenkaY != 0) {
				New_y[i]++;
				oy++;
				LenkaY--;
				if (HitCheck(i) == true) {//�ǂɓ������Ă���̂ō����E�Ɉړ�������
					New_y[i]--;//����������
					//if (x[i] - x[i + 1] >= 0) {
					//	New_x[i]++;
					//	//HenkaX++;
					//}
					//else if (x[i] - x[i + 1] < 0) {
					//	New_x[i]--;
					//	//HenkaX--;
					//}

				}
			}

			if (oy >= IRONBALL_R) {//�I�[�o�[������������ω��ʂɖ߂�
				LenkaY += oy - IRONBALL_R;
			}

		}
	}

	//�c�ړ�����
	if (LenkaY == 0) {

	}
	//�ړ����s
	else {
		NewY += LenkaY;
		//HenkaY += LenkaY;
	}

	LenkaY = 0;

	//�����W�̕ω�
	//�v���X�Ȃ̂ŉE�Ɉړ����Ă���B
	if (LenkaX > 0) {
		for (int i = LOCK_MAX - 1; i > 0; i--) {
			//�ω��ʂȂ��Ȃ�u���C�N
			if (LenkaX == 0) {
				break;
			}

			ox = New_x[i] - New_x[i - 1];							//���̍���}��

			//���W�ړ�
			New_x[i] += LenkaX;
			ox += LenkaX;
			LenkaX = 0;
			if (ox > IRONBALL_R) {
				LenkaX += ox - IRONBALL_R;
			}
		}
	}
	//�}�C�i�X�Ȃ̂ō��Ɉړ����Ă���B
	else if (LenkaX < 0) {
		for (int i = LOCK_MAX - 1; i > 0; i--) {
			//�ω��ʂȂ��Ȃ�u���C�N
			if (LenkaX == 0) {
				break;
			}

			ox = New_x[i - 1] - New_x[i];							//���̍���}��

			//���W�ړ�
			New_x[i] -= (-LenkaX);
			ox += (-LenkaX);
			LenkaX = 0;
			if (ox > IRONBALL_R) {
				LenkaX -= ox - IRONBALL_R;
			}
		}
	}

	//�ړ������B���Ɠ�����`�F�b�N������
	if (LenkaX == 0) {

	}//�ړ����s�B�l�̂ق��𓮂����B�G���[���邩��
	else {
		NewX += LenkaX;
		HenkaX += LenkaX;
	}
	LenkaX = 0;

	/*********************************
	*�l���ړ������Ƃ��̕ω�
	*********************************/
	//y���W�̕ω�
	//�}�C�i�X�����Ȃ��B��ɂ���
	if (HenkaY < 0) {
		for (int i = 0; i < LOCK_MAX - 1; i++) {
			//�ω��ʂȂ��Ȃ�u���C�N
			if (HenkaY == 0) {
				break;
			}
			//���̍���}��
			oy = /*abs(x[i] - x[i + 1])*/  New_y[i + 1] - New_y[i];
			//���W�ړ�
			while (HenkaY != 0) {
				New_y[i]--;
				oy++;
				HenkaY++;
				if (HitCheck(i) == true) {//�ǂɓ������Ă���̂ō����E�Ɉړ�������B�����l����ׂ�
					New_y[i]++;//����������
					if (x[i] - x[i + 1] >= 0) {
						New_x[i]++;
						//HenkaX++;
					}
					else if (x[i] - x[i + 1] < 0) {
						New_x[i]--;
						//HenkaX--;
					}
					
				}
			}

			if (oy >= IRONBALL_R) {//�I�[�o�[������������ω��ʂɖ߂�//���������ɂ���
				HenkaY -= oy - IRONBALL_R;
			}

		}
		//if(i==LOCK_MAX - 2){
		//HenkaY = 0;

	}
	else if (HenkaY > 0) {//�ЂƂ������Ă����ꍇ

		static int zo[LOCK_MAX];//�d�͂Ǝ����悤�ȏ��������邽��

		New_y[0] += HenkaY;
		zo[0] = 4;
		if (HitCheck(0) == false && (y[0] - (NewY + Map_PlayerY)) < (CHA_SIZE_Y - 8)) {
		}
		else {
			New_y[0] -= HenkaY;
			zo[0] = 2;
		}
		



		//�Ō�̕��̍�
		New_y[LOCK_MAX - 1] += HenkaY;
		if (HitCheck(0) == false && (y[LOCK_MAX - 1] - g_IronBall.y) < 0) {
		}
		else {
			New_y[LOCK_MAX - 1] -= HenkaY;
		}
		

		//���ׂĂɏd�͂������Ă��̌�A�����Ă���
		for (int i = 1; i < LOCK_MAX - 1; i++) {
			New_y[i] += HenkaY;
			zo[i] = 4;
		}

		//4�F�����ɗ������B2�F�ǂɈ����������Ă��邪�܂����v�B0�F���̒����ň����������Ă���̂ŕs��
		for (int i = LOCK_MAX - 2; i >= 0; i--) {
			if (New_y[i] - New_y[i + 1] >= IRONBALL_R) {
				if (zo[i] == 4 ) {
					New_y[i] -= HenkaY;
					zo[i] = 0;
				}
				else if (zo[i] == 2) {
					zo[i] = 0;
				}
			}
			else if (HitCheck(i) == true) {
				if (zo[i] == 4) {
					New_y[i] -= HenkaY;
					zo[i] = 2;
				}
			}
		}

		for (int i = 1; i < LOCK_MAX-1; i++) {
			if (New_y[i] - New_y[i-1] >= IRONBALL_R) {
				if (zo[i] == 4) {
					New_y[i] -= HenkaY;
					zo[i] = 0;
				}
				else if (zo[i] == 2) {
					zo[i] = 0;
				}
			}
			else if (HitCheck(i) == true) {
				if (zo[i] == 4) {
					New_y[i] -= HenkaY;
					zo[i] = 2;
				}
			}
		}
		//�`�F�b�N
		for (int i = 0; i < LOCK_MAX - 1; i++) {
			if (zo[i] == 4 ) {
				HenkaY = 0;
				break;
			}
			if (zo[i] == 2 ) {
				continue;
			}
			Gr = false;
		}
		//�������ׂĂ̍����n�ʂɂ��Ă�����HenkaY���O�ɂ���B����񂩂�
		if (Gr == true) {
			HenkaY = 0;
		}

		if (HenkaY != 0 && Jump_Flg == -2) {
			if (PlayerX - New_x[1] > 0) {
				HenkaX += HenkaY;
			}
			else if (PlayerX - New_x[1] < 0) {
				HenkaX -= HenkaY;
			}
		}
	}
	
	//HenkaY = 0;


	//�����W�̕ω�
	//�v���X�Ȃ̂ŉE�Ɉړ����Ă���B
	if (HenkaX > 0) {
		for (int i = 0; i < LOCK_MAX - 1; i++) {
			//�ω��ʂȂ��Ȃ�u���C�N
			if (HenkaX == 0) {
				break;
			}
			if (HI != 0 && (PlayerX + 16 + Map_PlayerX) - New_x[i] <= 0) {
				continue;
			}

		//	ox = (New_x[i] - New_x[i + 1]); //+ //abs(New_y[i] - New_y[i + 1]);							//���̍���}��

			//���W�ړ�
			while (HenkaX != 0) {
				New_x[i]++;
			//	ox ++;
				HenkaX--;
				if (HitCheck(i) == true) {//�ǂɓ������Ă���̂ŏ�ɏ㏸������
					New_y[i]--;//����������
					New_x[i]--;
				//	EL++;
				}
			}

			//HenkaX += EL;			//
			//EL = 0;

			//if (ox >= IRONBALL_R) {//�I�[�o�[������������ω��ʂɖ߂�

			//		HenkaX += ox - IRONBALL_R;
			//	
			//}
			//(New_x[i] - New_x[i + 1])
			if (New_x[i] - New_x[i + 1] >= 0
				&& pow((double)New_x[i] - (double)New_x[i + 1], 2.0) + pow((double)New_y[i] - (double)New_y[i + 1], 2.0) >= pow(IRONBALL_R, 2.0)
				) {
				ox = (int)(pow((double)New_x[i] - (double)New_x[i + 1], 2.0) + pow((double)New_y[i] - (double)New_y[i + 1], 2.0));
				if (ox >= pow(IRONBALL_R, 2.0)) {
					HenkaX += (int)sqrt(ox) - IRONBALL_R;
				}

			}
		}
	}
	//�}�C�i�X�Ȃ̂ō��Ɉړ����Ă���B
	else if (HenkaX < 0) {
		for (int i = 0; i < LOCK_MAX - 1; i++) {
			//�ω��ʂȂ��Ȃ�u���C�N
			if (HenkaX == 0) {
				break;
			}
			if (HI!=0 && (PlayerX + 16 + Map_PlayerX) - New_x[i] >= 0) {
				continue;
			}

		//	ox = New_x[i + 1] - New_x[i];// + abs(New_y[i] - New_y[i + 1]);							//���̍���}��

			//���W�ړ�
			while (HenkaX != 0) {
				New_x[i]--;
			//	ox++;
				HenkaX++;
				if (HitCheck(i) == true) {//�ǂɓ������Ă���̂ŏ�ɏ㏸������
					New_y[i]--;//����������
					New_x[i]++;
					//EL++;
				}
			}

			//HenkaX += EL;
			//EL = 0;

			if ( New_x[i + 1] - New_x[i] >= 0
				&& pow((double)New_x[i + 1] - (double)New_x[i], 2.0) + pow((double)New_y[i + 1] - (double)New_y[i], 2.0) >= pow(IRONBALL_R, 2.0)
				) {
				ox = (int)(pow((double)New_x[i + 1] - (double)New_x[i], 2.0) + pow((double)New_y[i + 1] - (double)New_y[i], 2.0));
				if (ox >= pow(IRONBALL_R, 2.0)) {
					HenkaX -= (int)sqrt(ox) - IRONBALL_R;
				}
				
			}
		}
	}

	//�ړ������B���Ɠ�����`�F�b�N������
	if (HenkaX == 0) {
		
	}//�ړ����s�B
	else if(HI == 0){
		for (int i = 0; i < LOCK_MAX - 1; i++) {
			New_x[i] += (-HenkaX);
		}
	}
}

//�ړ�����
void partsInfo::Move() {
	

	//if (!ThrowFlg)y += 4;
	New_x = x;
	New_y = y;
	if (!HitCheck() && !ThrowFlg ) y += 4;
	

	if (!HoldFlg && !ThrowFlg) {
		HitBectl();
		DrawFormatString(100, 100, 0x000000, "true");
	}
	
	
	
	//x = ((PlayerX / MAP_SIZE) + 4) * MAP_SIZE;
	if (HoldFlg) {
		
	}
	//�v���C���[���S���𓊂��邩����
	IronHoldOrThrow();
	Throw();
	
	

}


void Lock::Move() {
	 
	for (int i = 0; i < LOCK_MAX; i++) {
		x[i] = New_x[i];
		y[i] = New_y[i];
	}

	
}


//�����鏈��
void partsInfo::Throw(){			//�S�������ł�������
	const int InitPow = -20;
	static int Pow = InitPow;
	static int move = 1;

	//if (g_NowKey & PAD_INPUT_UP) ThrowFlg = true;

	if (HoldFlg) {
		IronHold(&x,&y);
	}

	if (ThrowFlg && Bectl == 0) {			//�������Ă��鏈���E
		New_x = x;
		New_y = y;
		Pow++;
		New_x += 6;
		New_y += Pow;
		if (HitCheck()) {
		//	ThrowFlg = false;
			
			if (Pow < 0) {
				Pow = 0;
			}
			else {
				//���~���������Ă����v�Ȃ炷��
				New_x = x;
				if (!HitCheck()) {
					//x = New_x;
					y = New_y;
				}
			}
			
		}
		else {
			x = New_x;
			y = New_y;
			Locka.LenkaX += 6;
			Locka.LenkaY += Pow;
		}
	}else if(ThrowFlg && Bectl == 1){		//�������Ă��鏈����
		New_x = x;
		New_y = y;
		Pow++;
		New_x -= 6;
		New_y += Pow;
		if (HitCheck()) {
			//	ThrowFlg = false;

			if (Pow < 0) {
				Pow = 0;
			}
			else {
				//���~���������Ă����v�Ȃ炷��
				New_x = x;
				if (!HitCheck()) {
					x = New_x;
					y = New_y;
				}
			}
			
			
		}
		else {
			x = New_x;
			y = New_y;
			Locka.LenkaX -= 6;
			Locka.LenkaY += Pow;
		}
	}
	else { Pow = InitPow; }

	New_x = x;
	New_y = y;//�ŏI�I�ȃ��Z�b�g
}


void Lock::Throw() {

}



//�����蔻��
bool partsInfo::HitCheck() {		//�n�ʂƂ̓����蔻��@�������Ă����true �������Ă��Ȃ����false�B��������̍��W���݂�Ƃ���
	 int i=0, j=0, k=0, l=0, w=0, z=0;//���[�J���ϐ�
	//�S���̈ʒu�i���j���}�b�v���܂����ł���
	while ((New_x - IRONBALL_R)/MAP_SIZE - k >= WIDTH) {
		k += WIDTH;
		l += HEIGHT;
	}
	//�S���̈ʒu�i�E�j���}�b�v���܂����ł���
	if ((New_x + IRONBALL_R)/MAP_SIZE - k>= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//�^�񒆂̈ʒu���}�b�v���܂����ł���
	if (New_x/MAP_SIZE - k >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}
	
	//�����Ă���Ƃ��ɕǂɂ��������瓊����̂���߂�BThrowFlg��ς���Ƃ���
	if (g_MapChip[(New_y + IRONBALL_R) / MAP_SIZE + l + z][New_x / MAP_SIZE - k - w] != 1		//���S�̐^��
		//|| g_MapChip[(New_y - IRONBALL_R + 10) / MAP_SIZE + l][(New_x - IRONBALL_R) / MAP_SIZE - k] != 1	//���� + 10
		//|| g_MapChip[(New_y - IRONBALL_R + 10) / MAP_SIZE + l + j][(New_x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//�E�� + 10
		|| g_MapChip[(New_y ) / MAP_SIZE + l][(New_x - IRONBALL_R) / MAP_SIZE - k] != 1	//���^��
		|| g_MapChip[(New_y ) / MAP_SIZE + l + j][(New_x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//�E�^��
		|| g_MapChip[(New_y + IRONBALL_R) / MAP_SIZE + l][(New_x - IRONBALL_R) / MAP_SIZE - k] != 1	//����
		|| g_MapChip[(New_y + IRONBALL_R) / MAP_SIZE + l + j][(New_x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//�E��
		) {
		
		ThrowFlg = false;
	}


	if(g_MapChip[ (New_y - IRONBALL_R  ) / MAP_SIZE + l + z][New_x  / MAP_SIZE - k - w] != 1		//���S�̐^��
		||g_MapChip[(New_y + IRONBALL_R) / MAP_SIZE + l + z][New_x / MAP_SIZE - k - w] != 1		//���S�̐^��
		|| g_MapChip[ (New_y - IRONBALL_R ) / MAP_SIZE + l][(New_x - IRONBALL_R ) / MAP_SIZE - k] != 1	//����
		|| g_MapChip[ (New_y - IRONBALL_R ) / MAP_SIZE + l + j][(New_x + IRONBALL_R ) / MAP_SIZE - k - i] != 1	//�E��
		|| g_MapChip[ (New_y + IRONBALL_R ) / MAP_SIZE + l][(New_x - IRONBALL_R ) / MAP_SIZE - k] != 1	//����
		|| g_MapChip[ (New_y + IRONBALL_R ) / MAP_SIZE + l + j][(New_x + IRONBALL_R ) / MAP_SIZE - k - i] != 1	//�E��
		){	
		return true;
	}

	return false;
}


//�E���ǂ���ɂ������Ă��邩�ǂ����B���݂̍��W���݂�Ƃ���
void  partsInfo::HitBectl() {
	int i = 0, j = 0, k = 0, l = 0, w = 0, z = 0;//���[�J���ϐ�
	//�S���̈ʒu�i���j���}�b�v���܂����ł���
	while ((x - IRONBALL_R) / MAP_SIZE - k >= WIDTH) {
		k += WIDTH;
		l += HEIGHT;
	}
	//�S���̈ʒu�i�E�j���}�b�v���܂����ł���
	if ((x + IRONBALL_R) / MAP_SIZE - k >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//�^�񒆂̈ʒu���}�b�v���܂����ł���
	if (x / MAP_SIZE - k >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}


	//���݂̏���W���݂�
	if (g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l][(x - IRONBALL_R) / MAP_SIZE - k] != 1	//����
		|| g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l + j][(x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//�E��
		|| g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l + z][x / MAP_SIZE - k - w] != 1)		//���S�̐^��
	{
		//���Ȃ̂Ń}�b�v�ň�����݂Ă����v�Ȃ͂��B�������ǂ���Ȃ���΂����W�������Ɉڂ�
		if (g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l + 1][(x - IRONBALL_R) / MAP_SIZE - k] != 1	//����
			|| g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l + j + 1][(x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//�E��
			|| g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l + z + 1][x / MAP_SIZE - k - w] != 1)
		{
		}
		else {
			y = ((y - IRONBALL_R) / MAP_SIZE + 1) * MAP_SIZE + IRONBALL_R + 1;
		}
	}




	//���݂̍����W���ǂɖ�����Ă���Ȃ�΍��W����E�ɂ���
	if (g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l][(x - IRONBALL_R) / MAP_SIZE - k] != 1	//����
		|| g_MapChip[(y + IRONBALL_R - 4) / MAP_SIZE + l ][(x - IRONBALL_R) / MAP_SIZE - k] != 1	//����-4
		) {
		Locka.LenkaX +=  (((x - IRONBALL_R) / MAP_SIZE + 1) * MAP_SIZE + IRONBALL_R) - x;
		x = ((x - IRONBALL_R) / MAP_SIZE + 1) * MAP_SIZE + IRONBALL_R;
		Locka.MoveCheck();
		//return;
	}
	//���݂̉E���W���ǂɖ�����Ă���Ȃ�΍��W������ɂ���
	if (g_MapChip[(y - IRONBALL_R) / MAP_SIZE + l + j][(x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//�E��
		|| g_MapChip[(y + IRONBALL_R - 4) / MAP_SIZE + l + j][(x + IRONBALL_R) / MAP_SIZE - k - i] != 1	//�E��-4
		) {
		Locka.LenkaX +=  (((x + IRONBALL_R) / MAP_SIZE) * MAP_SIZE - IRONBALL_R - 1) - x;
		x = ((x + IRONBALL_R) / MAP_SIZE) * MAP_SIZE - IRONBALL_R - 1;
		Locka.MoveCheck();
		//return;
	}

	//New_x = x;
	//New_y = y;//�ŏI�I�ȃ��Z�b�g�����new_X���G���
	return ;
}


int Lock::HitCheck(int num) {
	int i = 0, j = 0, k = 0, l = 0, w = 0, z = 0;//���[�J���ϐ�

	//���̈ʒu�i���j���}�b�v���܂����ł���
	while ((New_x[num] - ro) / MAP_SIZE - k >= WIDTH) {
		k += WIDTH;
		l += HEIGHT;
	}
	//�S���̈ʒu�i�E�j���}�b�v���܂����ł���
	if ((New_x[num] + ro) / MAP_SIZE - k >= WIDTH) {
		i += WIDTH;
		j += HEIGHT;
	}
	//�^�񒆂̈ʒu���}�b�v���܂����ł���
	if (New_x[num] / MAP_SIZE - k >= WIDTH) {
		w += WIDTH;
		z += HEIGHT;
	}


	if (g_MapChip[(New_y[num] - ro) / MAP_SIZE + l + z][New_x[num] / MAP_SIZE - k - w] != 1		//���S�̐^��
		|| g_MapChip[(New_y[num] + ro) / MAP_SIZE + l + z][New_x[num] / MAP_SIZE - k - w] != 1		//���S�̐^��
		|| g_MapChip[(New_y[num] - ro) / MAP_SIZE + l][(New_x[num] - ro) / MAP_SIZE - k] != 1	//����
		|| g_MapChip[(New_y[num] - ro) / MAP_SIZE + l + j][(New_x[num] + ro) / MAP_SIZE - k - i] != 1	//�E��
		|| g_MapChip[(New_y[num] + ro) / MAP_SIZE + l][(New_x[num] - ro) / MAP_SIZE - k] != 1	//����
		|| g_MapChip[(New_y[num] + ro) / MAP_SIZE + l + j][(New_x[num] + ro) / MAP_SIZE - k - i] != 1	//�E��
		) {
		return true;
	}

	return false;

	//return 0;
}


void Lock::Gravity() {
	static int zo[LOCK_MAX];//

	for (int i = 0; i < LOCK_MAX; i++) {
		x[i] = New_x[i];
		y[i] = New_y[i];
	}

	if (!g_IronBall.ThrowFlg && Jump_Flg == 0/*&& !g_IronBall.HoldFlg*/) {//�S���𓊂��ĂȂ��Ƃ��A�����Ă��Ȃ��Ƃ��d�͂����ɉ�����.
													//����ƍ��̒����̐����������ׂ�
		New_y[0] += 4;
		if (HitCheck(0) == false && (y[0] - (PlayerY + Map_PlayerY)) < (CHA_SIZE_Y - 8)) {
			y[0] += 4;
		}
		New_y[0] = y[0];

		//�Ō�̕��̍�
		New_y[LOCK_MAX - 1] += 4;
		if (HitCheck(0) == false && (y[LOCK_MAX - 1] - g_IronBall.y) < 0) {
			y[LOCK_MAX - 1] += 4;
		}
		New_y[LOCK_MAX - 1] = y[LOCK_MAX - 1];

		//���ׂĂɏd�͂������Ă��̌�A�����Ă���
		for (int i = 1; i < LOCK_MAX - 1; i++) {
			New_y[i] += 4;
			zo[i] = 4;
			Wall[i] = 0;
		}

		//�����P���E���ǂȂ�//������������Ȃ�����
		for (int i = 1; i < LOCK_MAX - 1; i++) {
			New_x[i] += 2;
			if (zo[i] == 4 && HitCheck(i) == true ) {
				/*New_y[i] -= 4;
				zo[i] = 0;*/
				Wall[i] = 1;
			}
			New_x[i] -= 4;
			if (zo[i] == 4 && HitCheck(i) == true) {
				/*New_y[i] -= 4;
				zo[i] = 0;*/
				Wall[i] = 1;
			}
			New_x[i] += 2;
		}


		for (int i = LOCK_MAX - 2; i >= 1; i--) {
			if (Wall[i] == 0) {//�ǂɓ������Ă��Ȃ��̂ňꉞ�ȂȂ߂̒��������𒲂ׂ�B//�Q��̒��g���{�ł��邱���ł͍��������d�v
				if (HitCheck(i) == true 
					|| (New_y[i] - New_y[i + 1] > 0  &&  pow((double)New_y[i] - (double)New_y[i + 1] , 2.0) + pow((double)New_x[i] - (double)New_x[i + 1], 2.0) >= pow((double)IRONBALL_R, 2.0))
					) {
					if (zo[i] == 4) {
						New_y[i] -= 4;
						zo[i] = 0;
					}
				}
			}
			else if (Wall[i] == 1) {//�����ǂɓ������Ă���̂ŏc�{��
				if (HitCheck(i) == true || (New_y[i] - New_y[i + 1]) + abs(New_x[i] - New_x[i + 1])  >= IRONBALL_R) {
					if (zo[i] == 4) {
						New_y[i] -= 4;
						zo[i] = 0;
					}
				}
			}
		}

		for (int i = 1; i < LOCK_MAX - 1; i++) {
			if (Wall[i] == 0) {
				if (HitCheck(i) == true 
					|| (New_y[i] - New_y[i - 1] > 0 && pow((double)New_y[i] - (double)New_y[i - 1], 2.0) + pow((double)New_x[i] - (double)New_x[i - 1], 2.0) >= pow((double)IRONBALL_R , 2.0)))
				{
					if (zo[i] == 4) {
						New_y[i] -= 4;
						zo[i] = 0;
					}
				}
			}
			else if (Wall[i] == 1) {
				if (HitCheck(i) == true || New_y[i] - New_y[i - 1] + abs(New_y[i] - New_y[i - 1]) >= IRONBALL_R) {
					if (zo[i] == 4) {
						New_y[i] -= 4;
						zo[i] = 0;
					}
				}
			}
		}

	}


	for (int i = 0; i < LOCK_MAX; i++) {
		x[i] = New_x[i];
		y[i] = New_y[i];
	}
}


/***********************************************
*		�S���̊֐��̒�`
************************************************/
void IronBallDisp() {
	g_IronBall.Disp();
	Locka.Disp();
}



void IronBallMove() {
	static bool initflg = true;

	if (initflg) {
		g_IronBall.Init();
		Locka.Init();
		initflg = false;
	}

	Locka.Gravity();
	g_IronBall.Move();
	Locka.Move();
}