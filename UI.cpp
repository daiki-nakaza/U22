#include "DxLib.h"

#include "UI.h"

void HUDDisp() {
	time_t now = time(NULL); 
#pragma warning(suppress : 4996)
	struct tm* pnow = localtime(&now);
	char week[][3] = { "日","月","火","水","木","金","土" };

	DrawFormatString(10,10,0x000000,"今日は%2d年%2d月%2d日(%s)\n",
		pnow->tm_year + 1900,
		pnow->tm_mon + 1,
		pnow->tm_mday,
		week[pnow->tm_wday]);
}