#include"DxLib.h"
#include <math.h>

#define HEIGHT 22 //�P��ʂ̍���
#define WIDTH 32//�P��ʂ̕�
#define STAGE 10
#define MAP_SIZE 32//32�r�b�g
#define CHA_SIZE 48//48�r�b�g

/****************************************************
* �񋓑̂̐錾
*****************************************************/
typedef enum MENU_MODE {
	GAME_TITLE,//�O
	GAME_MAIN,//�P
	GAME_END,//�Q
	GAME_MENU,//3
	GAME_INIT,//4
	GAME_CLEAR,//5
	GAME_HELP,//6


	END = 99
};


/****************************************************
*�萔�̐錾
****************************************************/


/****************************************************
*�ϐ��̐錾
****************************************************/

int g_OldKey;
int g_NowKey;
int g_KeyFlg;
int g_OldKey2;
int g_NowKey2;
int g_KeyFlg2;
int g_MouseX;//�}�E�X�����W
int g_MouseY;//�}�E�X�����W


int g_GameState = GAME_MAIN;//�Q�[�����[�h

//�v���C���[�̈ʒu
int PlayerX, PlayerY;              //0�`��ʔ����܂ŁB
int Map_PlayerX, Map_PlayerY;      //�}�b�v�S�̂̃X�N���[���ʒu
int MapX, MapY;                    //
int OldX, OldY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�
int Map_OldX, Map_OldY;	// �ړ�����O�̃v���C���[�̈ʒu��ۑ�����ϐ�

int MapDrawPointX, MapDrawPointY;		// �`�悷��}�b�v���W�l
int MapChipNumX, MapChipNumY;


/***************************************
*�}�b�v�p�ϐ�
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
*�T�E���h�p�ϐ�
***************************************/



/*********************************************
*�֐��̃v���g�^�C�v�錾
*********************************************/
void DrawGameTitle(void);
void DrawGameMain(void);
void DrawEnd(void);
void DrawMenu(void);
void DrawInit(void);
void DrawClear(void);
void DrawGameOver(void);//�Q�[���I�[�o�[�`�揈��
void DrawHelp(void);


int LoadImages();//�摜�ǂݍ���
int LoadSounds();//�����ǂݍ���

void DrawStage(void);
void GraphDraw(void);



/******************************************************
*�v���O�����̊J�n
******************************************************/

//�v���O������WinMain����n�܂�܂�//
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);//�E�B���h�E���[�h�ŋN��
	SetMainWindowText("");//�^�C�g����ݒ�
	SetGraphMode(1024, 700, 16);
//	32*32, 32*24

	// �v���C���[�̏����ʒu���Z�b�g
	PlayerX = 200;
	PlayerY = 200;
	Map_PlayerX = 0;
	Map_PlayerY = 0;

	if (DxLib_Init() == -1) {                    //DX���C�u��������������

		return -1;								//�G���[���N�����璼���ɏI��
	}
	//�摜�ǂݍ��݊֐����Ăяo��
	if (LoadImages() == -1) {
		return -1;
	}

	//�T�E���h�ǂݍ��݊֐����Ăяo��
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

		//�}�E�X�̈ʒu���擾
		GetMousePoint(&g_MouseX, &g_MouseY);

		ClearDrawScreen();
		DrawBox(0, 0, 1050, 620, 0x2f4f4f, TRUE); // ��ʑS�̂���]�̐F�œh��Ԃ�
		//DrawBox(0, 0, 1050, 620, 0xffffff, TRUE); // ��ʑS�̂���]�̐F�œh��Ԃ�

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

	// �X���C�h�p�̂O����R�P�܂ł̒l
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

	// �i���s�\�ȃ}�b�v�������ꍇ�͈ړ��ł��Ȃ�
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
void DrawGameOver(void) {}//�Q�[���I�[�o�[�`�揈��
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


// �}�b�v�ƃv���C���[�̕`��֐�
void GraphDraw(void)
{
	int i, j;
	int DrawMapChipNumX, DrawMapChipNumY;	// �`�悷��}�b�v�`�b�v�̐�
	

	// �`�悷��}�b�v�`�b�v�̐����Z�b�g
	DrawMapChipNumX = WIDTH + 1;
	DrawMapChipNumY = HEIGHT + 1;

	MapChipNumX = 0;
	MapChipNumY = 0;

	// �}�b�v��`��
	for (i = 0; i < DrawMapChipNumY; i++)
	{
		for (j = 0; j < DrawMapChipNumX; j++)
		{
			// ��ʂ���͂ݏo���ʒu�Ȃ�`�悵�Ȃ�
			if (j + MapX < 0 || i + MapY < 0 || j + MapX >= WIDTH*2) continue;
			
			while (  j + MapX - MapChipNumX >= WIDTH ) {
				MapChipNumX += WIDTH;
				MapChipNumY += HEIGHT;
			}

			// �}�b�v�f�[�^���O��������l�p��`�悷��
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

	// �v���C���[�̕`��
	DrawBox((PlayerX), (PlayerY),
		(PlayerX)+CHA_SIZE, (PlayerY)+CHA_SIZE,
		GetColor(255, 255, 255), TRUE);//�����ɓ����蔻�肠��
}