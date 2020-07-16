#include "DxLib.h"

#include "UI.h"

const char data[] = __DATE__;
const char time[] = __TIME__;


void HUDDisp() {

	SetFontSize(30);
	DrawFormatString(800, 10, 0x000000, "%c%c%c%c %c%c%c %c%c\n %s",
		data[7], data[8], data[9], data[10],
		data[0], data[1], data[2],
		data[4], data[5] ,
		time);
}