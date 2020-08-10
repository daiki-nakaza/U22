#include "DxLib.h"

#include "UI.h"

#include "Define.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"

const char data[] = __DATE__;
const char time[] = __TIME__;


void HUDDisp() {

	SetFontSize(30);
	DrawFormatString(800, 10, 0x000000, "%c%c%c%c %c%c%c %c%c\n %s",
		data[7], data[8], data[9], data[10],
		data[0], data[1], data[2],
		data[4], data[5] ,
		time);

	//DrawFormatString(150, 210, 0x000000, "x = %d", g_ShootEnemy[0].Life);
}