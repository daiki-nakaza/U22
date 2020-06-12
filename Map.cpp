#include "DxLib.h"
#include "Map.h"


void MapDisp() {			// マップの描画
	for (int y = 0; y < SCREEN_HEIGHT_MAX; y++) {
		for (int x = 0; x < SCREEN_WIDTH_MAX; x++) {
			DrawFormatString(ChipSize * x, ChipSize * y, 0xffffff, "%d", x);
			switch (g_MapChip[y][x])
			{
			case 0:
				//DrawGraph(TipSize * x, TipSize * y, 画像データ, true);
				DrawBox(ChipSize * x, ChipSize * y, ChipSize * x + ChipSize, ChipSize * y + ChipSize, 0x000000, true);   //とりまDrawBox
				break;
			case 1:
				//DrawGraph(TipSize * x, TipSize * y, 画像データ, true);
				DrawBox(ChipSize * x, ChipSize * y, ChipSize * x + ChipSize, ChipSize * y + ChipSize, 0xff0000, true);   //とりまDrawBox
				break;
			}
			DrawLine(ChipSize * x, ChipSize * y, ChipSize * x, ChipSize * y + ChipSize, 0xffffff, true);
			DrawLine(ChipSize * x, ChipSize * y, ChipSize * x + ChipSize, ChipSize * y, 0xffffff, true);
		}
	}
}

void MapMove() {			//マップのスクロール処理


}


void MapChipInit(){	//マップチップの初期化処理


}