/*#include "DxLib.h"
#include "Map.h"
/**********************************************************************
*define�̐錾
***********************************************************************/
/*#define SCREEN_WIDTH_MAX 32		//���̃}�b�v�`�b�v�̍ő吔
#define SCREEN_HEIGHT_MAX 24		//�c�̃}�b�v�`�b�v�̍ő吔
#define ChipSize 32		//�}�b�v�`�b�v�̃T�C�Y
//#define
*/

/*****************************************************
*	�v���O�����̊J�n
******************************************************/
/*int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetMainWindowText("U22");		//�^�C�g����ݒ�
	SetWindowSize(1024, 768);			//�E�B���h�E�̑傫���ݒ�
	ChangeWindowMode(TRUE);			//�E�B���h�E���[�h�ŋN��
	if (DxLib_Init() == -1) return -1;		//DX���C�u�����g�p�̏I������
	SetDrawScreen(DX_SCREEN_BACK);			//�`����ʂ𗠂ɂ���
	gameInit();
	while (1) {
		MapDisp();
		MapMove();
		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
	}
	DxLib_End();	//DX���C�u�����g�p�̏I������
	return 0;		//�\�t�g�̏I��
}
void gameInit() {			//�Q�[���̏���������
	MapChipInit();
}
void MapChipInit() {			//�}�b�v�`�b�v�̏���������
}
void MapDisp() {			// �}�b�v�̕`��
	for (int y = 0; y < SCREEN_HEIGHT_MAX; y++) {
		for (int x = 0; x < SCREEN_WIDTH_MAX; x++) {
			switch (g_MapChip[y][x])
			{
			case 0:
				//DrawGraph(TipSize * x, TipSize * y, �摜�f�[�^, true);
				DrawBox(ChipSize * x, ChipSize * y, ChipSize * x + ChipSize, ChipSize * y + ChipSize, 0x000000, true);   //�Ƃ��DrawBox
				break;
			case 1:
				//DrawGraph(TipSize * x, TipSize * y, �摜�f�[�^, true);
				DrawBox(ChipSize * x, ChipSize * y, ChipSize * x + ChipSize, ChipSize * y + ChipSize, 0xff0000, true);   //�Ƃ��DrawBox
				break;
			}
			DrawLine(ChipSize * x, ChipSize * y, ChipSize * x, ChipSize * y + ChipSize, 0xffffff, true);
			DrawLine(ChipSize * x, ChipSize * y, ChipSize * x + ChipSize, ChipSize * y, 0xffffff, true);
		}
	}
}
void MapMove() {			//�}�b�v�̃X�N���[������

}
