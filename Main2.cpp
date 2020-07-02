#include"DxLib.h"
#include <math.h>

#define HEIGHT 22 //１画面の高さ
#define WIDTH 32//１画面の幅
#define STAGE 10
#define MAP_SIZE 32//32ビット
#define CHA_SIZE 48//48ビット

/****************************************************
* 列挙体の宣言
*****************************************************/
typedef enum MENU_MODE {
	GAME_TITLE,//０
	GAME_MAIN,//１
	GAME_END,//２
	GAME_MENU,//3
	GAME_INIT,//4
	GAME_CLEAR,//5
	GAME_HELP,//6


	END = 99
};


/****************************************************
*定数の宣言
****************************************************/


/****************************************************
*変数の宣言
****************************************************/

int g_OldKey;
int g_NowKey;
int g_KeyFlg;
int g_OldKey2;
int g_NowKey2;
int g_KeyFlg2;
int g_MouseX;//マウスｘ座標
int g_MouseY;//マウスｙ座標


int g_GameState = GAME_MAIN;//ゲームモード

//プレイヤーの位置
int PlayerX, PlayerY;              //0～画面半分まで。
int Map_PlayerX, Map_PlayerY;      //マップ全体のスクロール位置
int MapX, MapY;                    //
int OldX, OldY;	// 移動する前のプレイヤーの位置を保存する変数
int Map_OldX, Map_OldY;	// 移動する前のプレイヤーの位置を保存する変数

int MapDrawPointX, MapDrawPointY;		// 描画するマップ座標値
int MapChipNumX, MapChipNumY;


/***************************************
*マップ用変数
***************************************/
int Map[HEIGHT*2][WIDTH] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	

	///////////////////////////////////////////////////////////////////

	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	


};



/***************************************
*サウンド用変数
***************************************/



/*********************************************
*関数のプロトタイプ宣言
*********************************************/
void DrawGameTitle(void);
void DrawGameMain(void);
void DrawEnd(void);
void DrawMenu(void);
void DrawInit(void);
void DrawClear(void);
void DrawGameOver(void);//ゲームオーバー描画処理
void DrawHelp(void);


int LoadImages();//画像読み込み
int LoadSounds();//音声読み込み

void DrawStage(void);
void GraphDraw(void);



/******************************************************
*プログラムの開始
******************************************************/

//プログラムはWinMainから始まります//
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);//ウィンドウモードで起動
	SetMainWindowText("");//タイトルを設定
	SetGraphMode(1024, 700, 16);
//	32*32, 32*24

	// プレイヤーの初期位置をセット
	PlayerX = 200;
	PlayerY = 200;
	Map_PlayerX = 0;
	Map_PlayerY = 0;

	if (DxLib_Init() == -1) {                    //DXライブラリ初期化処理

		return -1;								//エラーが起きたら直ちに終了
	}
	//画像読み込み関数を呼び出し
	if (LoadImages() == -1) {
		return -1;
	}

	//サウンド読み込み関数を呼び出し
	if (LoadSounds() == -1) {
		return -1;
	}




	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0 && g_GameState != END && !(g_KeyFlg & PAD_INPUT_START)) {

		//PlaySoundMem(g_TitleBGM, DX_PLAYTYPE_LOOP, FALSE);

		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & g_OldKey;

		g_OldKey2 = g_NowKey2;
		g_NowKey2 = GetMouseInput();
		g_KeyFlg2 = g_NowKey2 & g_OldKey2;

		//マウスの位置を取得
		GetMousePoint(&g_MouseX, &g_MouseY);

		ClearDrawScreen();
		DrawBox(0, 0, 1050, 620, 0x2f4f4f, TRUE); // 画面全体を希望の色で塗りつぶす
		//DrawBox(0, 0, 1050, 620, 0xffffff, TRUE); // 画面全体を希望の色で塗りつぶす

		switch (g_GameState) {
		case GAME_TITLE:
			DrawGameTitle();
			break;
		case GAME_MAIN:
			DrawGameMain();
			break;
		case GAME_END:
			DrawEnd();
			break;
		case GAME_MENU:
			DrawMenu();
			break;
		case GAME_INIT:
			DrawInit();
			break;
		case GAME_CLEAR:
			DrawClear();
			break;
		case GAME_HELP:
			DrawHelp();
			break;
		}

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}


void DrawGameTitle(){
	
}
void DrawGameMain(){
	// 移動する前のプレイヤーの位置を保存
	OldX = PlayerX;
	OldY = PlayerY;
	Map_OldX = Map_PlayerX;
	Map_OldY = Map_PlayerY;

	// キー入力に応じてプレイヤーの座標を移動
	if (g_NowKey & PAD_INPUT_LEFT) PlayerX -= 2;
	if (g_NowKey & PAD_INPUT_RIGHT) PlayerX += 2;
	if (g_NowKey & PAD_INPUT_UP) PlayerY -= 2;
	if (g_NowKey & PAD_INPUT_DOWN) PlayerY += 2;

	if (PlayerX > 500) {
		PlayerX = 500;
		Map_PlayerX += 1;
	}
	if (PlayerX < 64) {
		PlayerX = 64;
		if (Map_PlayerX > 0) {
			Map_PlayerX -= 1;
		}
		
	}

	// スライド用の０から３１までの値
	MapDrawPointX = -(Map_PlayerX % MAP_SIZE);
	MapDrawPointY = -(Map_PlayerY % MAP_SIZE);

	MapX = (Map_PlayerX) / MAP_SIZE;   
	MapY = (Map_PlayerY) /MAP_SIZE;   

	MapChipNumX = 0;
	MapChipNumY = 0;
	for (int k = 1; MapX + (PlayerX / MAP_SIZE) >= WIDTH * k; k++) {
		MapChipNumX += WIDTH;
		MapChipNumY += HEIGHT;
	}

	// 進入不可能なマップだった場合は移動できない
	if (Map[MapY + ((PlayerY + (Map_PlayerY % MAP_SIZE)) / MAP_SIZE) + MapChipNumY][MapX + ((PlayerX + (Map_PlayerX % MAP_SIZE)) / MAP_SIZE) - MapChipNumX] != 1)
	{
		PlayerX = OldX;
		PlayerY = OldY;	
		Map_PlayerX = Map_OldX;
		Map_PlayerY = Map_OldY;

	}

	

	GraphDraw();

}
void DrawEnd(){}
void DrawMenu(){
	DrawStage();
	
}
void DrawInit(void){}
void DrawClear(void){}
void DrawGameOver(void) {}//ゲームオーバー描画処理
void DrawHelp(void){}


int LoadImages() {
	return 0;
}
int LoadSounds() {
	return 0;
}

void DrawStage(void){
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (Map[i][j] == 0) {

			}
			else if (Map[i][j] == 1) {

			}
		}
	}
}


// マップとプレイヤーの描画関数
void GraphDraw(void)
{
	int i, j;
	int DrawMapChipNumX, DrawMapChipNumY;	// 描画するマップチップの数
	

	// 描画するマップチップの数をセット
	DrawMapChipNumX = WIDTH + 1;
	DrawMapChipNumY = HEIGHT + 1;

	MapChipNumX = 0;
	MapChipNumY = 0;

	// マップを描く
	for (i = 0; i < DrawMapChipNumY; i++)
	{
		for (j = 0; j < DrawMapChipNumX; j++)
		{
			// 画面からはみ出た位置なら描画しない
			if (j + MapX < 0 || i + MapY < 0 || j + MapX >= WIDTH*2) continue;
			
			while (  j + MapX - MapChipNumX >= WIDTH ) {
				MapChipNumX += WIDTH;
				MapChipNumY += HEIGHT;
			}

			// マップデータが０だったら四角を描画する
			if (Map[i + MapY + MapChipNumY][j + MapX - MapChipNumX] == 0)
			{
				DrawBox(j * MAP_SIZE + MapDrawPointX, i * MAP_SIZE + MapDrawPointY,
					(j + 1) * MAP_SIZE + MapDrawPointX, (i + 1) * MAP_SIZE + MapDrawPointY,
					GetColor(255, 255, 0), TRUE);
			}
			if (Map[i + MapY + MapChipNumY][j + MapX - MapChipNumX] == 1)
			{
				DrawBox(j * MAP_SIZE+MapDrawPointX, i * MAP_SIZE+MapDrawPointY,
					(j + 1) * MAP_SIZE+MapDrawPointX, (i + 1) * MAP_SIZE+MapDrawPointY,
					GetColor(0, 255, 0), TRUE);
			}
			MapChipNumX = 0;
			MapChipNumY = 0;
		}
	}

	// プレイヤーの描画
	DrawBox((PlayerX), (PlayerY),
		(PlayerX)+CHA_SIZE, (PlayerY)+CHA_SIZE,
		GetColor(255, 255, 255), TRUE);//左下に当たり判定あり
}