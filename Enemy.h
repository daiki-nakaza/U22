#pragma once

#include "DxLib.h"

#include "Bullet.h"
#include "Define.h"



struct enemyInfo
{
	int x, y;			//“G‚ÌXÀ•WAYÀ•W
	int w, h;			//“G‚Ì•‚Æ‚‚³
	int direct;			//“G‚ÌŒü‚« (‰E:1  ¶:-1)
	int speed;			//“G‚ÌƒXƒs[ƒh
	int type;			//“G‚Ìƒ^ƒCƒv//ˆê“xUŒ‚‚ğ‚à‚ç‚Á‚½‚ç‚µ‚Î‚ç‚­–³“G
	int outtime;		

	int pic;			//‰æ‘œ—p•Ï”
	int anm;			//ƒAƒjƒ[ƒVƒ‡ƒ“—p•Ï”
	bool picDir;			//‰æ‘œ‚ÌŒü‚«

	bool DispFlg = false;		//“G‚ğ‚Ì•\¦‚Ìƒtƒ‰ƒO
	bool AttckFlg = false;		//“G‚ÌUŒ‚ƒtƒ‰ƒO

	int Life = 0;				//“G‚Ìƒ‰ƒCƒt


	void Disp();				//“G‚Ì•`‰æˆ—
	void Move();
};


//•à‚­“G‚Ì\‘¢‘Ì
struct WalkEnemy : public enemyInfo
{
	void Init(int Tempx,int Tempy);			//œpœj‚µ‚Ä‚¢‚é“G‚Ì‰Šú‰»ˆ—
	void WalkMove();			//œpœj‚µ‚Ä‚¢‚é“G‚Ìˆ—
	void Disp();
};


//‚Ü‚Á‚·‚®Œ‚‚Â“G‚Ì\‘¢‘Ì
struct ShootEnemy : public enemyInfo
{
	NormalBullet Bullet[Bullet_MAX];			//^‚Á‚·‚®Œ‚‚Â“G‚ªg‚¤’eŠÛ‚R”­

	void Init(int Tempx, int Tempy);			//Œ‚‚Â“G‚Ì‰Šú‰»ˆ—
	void ShootMove();			//Œ‚‚Â“G‚Ìˆ—

};


//‘_‚¢Œ‚‚Â“G‚Ì\‘¢‘Ì
struct LockShootEnemy : public enemyInfo
{

	LockBullet Bullet[Bullet_MAX];			//’eŠÛ3”­

	void Init(int Tempx, int Tempy);			//‘_‚¢Œ‚‚Â“G‚Ì‰Šú‰»ˆ—
	void LockShootMove();			//Œ‚‚Â“G‚Ìˆ—

};

//íÔ‚Ì“G(ã‚ÉŒü‚©‚Á‚Ä’e‚ğ”ò‚Î‚·“z)
struct TankEnemy : public enemyInfo
{
	ChargeBullet Bullet[Bullet_MAX];		//’eŠÛ3”­

	void Init(int Tempx, int Tempy);			//íÔ‚Ì‰Šú‰»ˆ—
	void TankMove();		//íÔ‚Ìˆ—
};

struct RazerEnemy : public enemyInfo
{
	RazerBullet Bullet;			//”g“®–C•Ï”

	int pic[3];

	void Init(int Tempx, int Tempy);
	void ShotMove();
	void Disp();
};


/**********************************************
*@@ŠÖ”‚Ìƒvƒƒgƒ^ƒCƒvéŒ¾
*********************************************/
void enemyDisp();			//“G‚Ì•`‰æˆ—
void enemyMove();			//“G‚Ì“®‚«
void enemyInit();			//“G‚Ì‰Šú‰»ˆ—

bool EnemyCheckHit(int x,int y,int direct);		//“G‘¤‚Ì“–‚½‚è”»’èƒ`ƒFƒbƒN
bool CheckWindow(int x);							//ƒEƒBƒ“ƒhƒE‚Ì’†‚É‚¢‚é‚©‚Ç‚¤‚© “ü‚Á‚Ä‚¢‚½‚çtrue

//void EnemyShoot();



/*********************************************
*•Ï”‚ÌéŒ¾
*******************************************/

//ƒGƒ‰[–h~—piŒã‚ÅÁ‚µ‚Ü‚·j
extern enemyInfo g_Enemy[ENEMY_MAX];


extern WalkEnemy g_WalkEnemy[ENEMY_MAX];			//•à‚­“G
extern ShootEnemy g_ShootEnemy[ENEMY_MAX];			//^‚Á‚·‚®Œ‚‚Â“G
extern LockShootEnemy g_LockShootEnemy[ENEMY_MAX];			//‘_‚¢Œ‚‚Â“G
extern TankEnemy g_TankEnemy[ENEMY_MAX];			//Ô‚Æ—Î‚Ì’eŠÛ‚ğŒ‚‚Â“G
extern RazerEnemy g_RazerEnemy[ENEMY_MAX];					//”g“®–C‚Ì“G

//extern BulletInfo Bullet[]

