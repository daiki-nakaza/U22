#include "DxLib.h"

#include "Define.h"
#include "PlayerAndIronBall.h"

#include "Player.h"
#include "accessory.h"

/**************************************
*	ä÷êîÇÃíËã`
***************************************/
void IronInit(int *ironX, int *ironY, int px,int py) {

	*ironX = ( (px / MAP_SIZE) + 4 ) * MAP_SIZE ;
}

void IronHold(int* ironX, int* ironY, int px, int py) {
	*ironX = px;
	*ironY = py;
}