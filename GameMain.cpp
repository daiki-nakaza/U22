#include "DxLib.h"


#include "GameMain.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "accessory.h"
#include "UI.h"



void DrawGameMain() {
	MapDisp();			//ƒ}ƒbƒv‚Ì•`‰æ
	MapMove();			//ƒXƒNƒŠ[ƒ“‚Ìˆ—

	PlayerMove();
	PlayerDisp();

	IronBallDisp();		//“S‹…‚Ì•`‰æˆ—
	IronBallMove();		//	“S‹…‚Ì“®‚«‚Ìˆ—


	enemyDisp();		//“G‚Ì•`‰æˆ—
	enemyMove();		//“G‚Ìˆ—

	HUDDisp();
}

