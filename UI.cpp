#include "DxLib.h"

#include "UI.h"

void HUDDisp() {
	time_t now = time(NULL); 
#pragma warning(suppress : 4996)
	struct tm* pnow = localtime(&now);
	char week[][3] = { "“ú","Œ","‰Î","…","–Ø","‹à","“y" };

	DrawFormatString(10,10,0x000000,"¡“ú‚Í%2d”N%2dŒ%2d“ú(%s)\n",
		pnow->tm_year + 1900,
		pnow->tm_mon + 1,
		pnow->tm_mday,
		week[pnow->tm_wday]);
}