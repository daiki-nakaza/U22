/*#include "DxLib.h"
#include "Map.h"
/**********************************************************************
*defineの宣言
***********************************************************************/
/*#define SCREEN_WIDTH_MAX 32		//横のマップチップの最大数
#define SCREEN_HEIGHT_MAX 24		//縦のマップチップの最大数
#define ChipSize 32		//マップチップのサイズ
//#define
*/

/*****************************************************
*	プログラムの開始
******************************************************/
/*int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetMainWindowText("U22");		//タイトルを設定
	SetWindowSize(1024, 768);			//ウィンドウの大きさ設定
	ChangeWindowMode(TRUE);			//ウィンドウモードで起動
	if (DxLib_Init() == -1) return -1;		//DXライブラリ使用の終了処理
	SetDrawScreen(DX_SCREEN_BACK);			//描画先画面を裏にする
	gameInit();
	while (1) {
		MapDisp();
		MapMove();
		ScreenFlip();			// 裏画面の内容を表画面に反映
	}
	DxLib_End();	//DXライブラリ使用の終了処理
	return 0;		//ソフトの終了
}
void gameInit() {			//ゲームの初期化処理
	MapChipInit();
}
void MapChipInit() {			//マップチップの初期化処理
}
void MapDisp() {			// マップの描画
	for (int y = 0; y < SCREEN_HEIGHT_MAX; y++) {
		for (int x = 0; x < SCREEN_WIDTH_MAX; x++) {
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
