#include "DxLib.h"

#include "Define.h"
#include "PlayerAndIronBall.h"

#include "Player.h"
#include "accessory.h"
#include "Enemy.h"
#include "Map.h"

/**************************************
*	ŠÖ”‚Ì’è‹`
***************************************/
void IronInit(int *ironX, int *ironY, int px,int py) {

	*ironX = ( (px / MAP_SIZE) + 4 ) * MAP_SIZE ;
}

void IronHold(int* ironX, int* ironY, int px, int py, int mpx,int mpy) {
	*ironX = px + mpx;
	*ironY = py + mpy;
}

void IronHoldOrThrow() {

	//ƒvƒŒƒCƒ„[‚ª“S‹…‚ğ‚Â‚©“Š‚°‚éˆ—
	if (!g_IronBall.HoldFlg && !g_IronBall.ThrowFlg		//“S‹…‚ğ‚Á‚Ä‚¢‚È‚¢‚©‚Â“S‹…‚ª“Š‚°‚ç‚ê‚Ä‚¢‚È‚¢
		&& g_NowKey & PAD_INPUT_1 && Jump_Flg == 0) {
		g_IronBall.HoldFlg = true;
	}
	else if (g_IronBall.HoldFlg && !g_IronBall.ThrowFlg	//“S‹…‚ğ‚Á‚Ä‚¢‚Ä‚©‚Â“S‹…‚ª“Š‚°‚ç‚ê‚Ä‚¢‚È‚¢
		&& g_NowKey & PAD_INPUT_2) {
		g_IronBall.HoldFlg = false;
		g_IronBall.ThrowFlg = true;
	}
	if (true) {

	}
}


bool IronToEnemy() {

	if (g_Enemy.picDir) {			//‰EŒü‚«‚Ìˆ—
		//Ÿ‚ÌˆÚ“®‚ÌêŠ‚ª“S‹…‚Æ”í‚Á‚Ä‚¢‚½‚çtrue‚ğ•Ô‚·
		if ((g_Enemy.y + g_Enemy.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
			&& (((g_Enemy.x + g_Enemy.w - MapDrawPointX) + (g_Enemy.direct * g_Enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x - g_IronBall.r) / MAP_SIZE + MapX) return true;
	}
	else {							//¶Œü‚«‚Ìˆ—
		//Ÿ‚ÌˆÚ“®‚ÌêŠ‚ª“S‹…‚Æ”í‚Á‚Ä‚¢‚½‚çtrue‚ğ•Ô‚·
		if ((g_Enemy.y + g_Enemy.h + MapDrawPointY) / MAP_SIZE + MapY == g_IronBall.y / MAP_SIZE + MapY
			&& (((g_Enemy.x - MapDrawPointX) + (g_Enemy.direct * g_Enemy.speed)) / MAP_SIZE) + MapX == (g_IronBall.x + g_IronBall.r) / MAP_SIZE + MapX) return true;
	}
	


		return false;
}