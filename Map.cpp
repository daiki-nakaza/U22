#include "DxLib.h"
#include "Map.h"


void MapDisp() {			// �}�b�v�̕`��
	for (int y = 0; y < SCREEN_HEIGHT_MAX; y++) {
		for (int x = 0; x < SCREEN_WIDTH_MAX; x++) {
			DrawFormatString(ChipSize * x, ChipSize * y, 0xffffff, "%d", x);
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


void MapChipInit(){	//�}�b�v�`�b�v�̏���������


}