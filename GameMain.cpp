#include "DxLib.h"


#include "GameMain.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "accessory.h"
#include "UI.h"



void DrawGameMain() {
	static int i = 0;
	if (i++ == 0) {
		PlayerInit();
	}
	MapDisp();			//ƒ}ƒbƒv‚Ì•`‰æ
	MapMove();			//ƒXƒNƒŠ[ƒ“‚Ìˆ—

	IronBallDisp();		//“S‹…‚Ì•`‰æˆ—
	IronBallMove();		//	“S‹…‚Ì“®‚«‚Ìˆ—

	PlayerMove();
	PlayerDisp();


	enemyDisp();		//“G‚Ì•`‰æˆ—
	enemyMove();		//“G‚Ìˆ—

	PlayerAttack();		//ƒvƒŒƒCƒ„[UŒ‚

	HUDDisp();
}

