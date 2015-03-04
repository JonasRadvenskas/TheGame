#include "GameObject.h"


Bullet::Bullet()
{
	raketos_busena = true;
}

//krauna raketas.
void Bullet::load(int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, int lango_w, int lango_h, int nr)
{
	CGameObject::load(xp, yp, wp, hp, xg, yg, wg, hg, lango_w, lango_h, nr);
}

//piesia raketas.
void Bullet::piesti(SDL_Renderer* pRenderer)
{
	CGameObject::piesti(pRenderer);
}


void Bullet::update()
{
	kadras = int(((SDL_GetTicks() / 60) % 4));	//keicia raketos animacijos kadrus

	if (xg<=lango_w)//judina raketas.
	{
		xg = xg + 9;
	}
	else
	{
		raketos_busena = false;
		xg = 0;
		yg = 800;
	}
}


SDL_Rect Bullet::GetRocketRekt()
{
	return (CGameObject::GetRekt(xg, yg, wg, hg));
}

void Bullet::SetRocketBusena(bool passed_value)
{
	raketos_busena = passed_value;
}