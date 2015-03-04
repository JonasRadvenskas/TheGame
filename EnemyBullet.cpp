#include "GameObject.h"


EnemyBullet::EnemyBullet()
{
	kulkos_busena = false;
}

void EnemyBullet::load(int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, int lango_w, int lango_h, int nr)
{
	CGameObject::load(xp, yp, wp, hp, xg, yg, wg, hg, lango_w, lango_h, nr);
}

void EnemyBullet::piesti(SDL_Renderer* pRenderer)
{
	CGameObject::piesti(pRenderer);//piesia kulkas.
}


void EnemyBullet::update()
{
	kadras = int(((SDL_GetTicks() / 60) % 2));	//keicia kulkos animacijos kadrus

	if ((xg >= -10)&&(kulkos_busena))
	{
		xg = xg - 6;
	}
	else
	{
		kulkos_busena = false;
		xg = 50;
		yg = 800;
	}
}


SDL_Rect EnemyBullet::GetBulletRekt()
{
	return (CGameObject::GetRekt(xg, yg, wg, hg));
}

void EnemyBullet::SetBulletBusena(bool passed_value)
{
	kulkos_busena = passed_value;
}