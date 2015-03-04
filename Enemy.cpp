#include "GameObject.h"


Enemy* Enemy::s_pInstance = 0;
//sukuriamas priesas
Enemy::Enemy(int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, int lango_w, int lango_h, int nr)
{
	CGameObject::load(xp, yp, wp, hp, xg, yg, wg, hg, lango_w, lango_h, nr);
	counter = 0;
	shot = false;
	shoot_counter = 0;
}


//priesas piesiamas
void Enemy::piesti(SDL_Renderer* pRenderer)
{
	CGameObject::piesti(pRenderer);//piesia priesa
}



void Enemy::update()
{
	shoot_counter++;
	counter++;
	kadras = int(((SDL_GetTicks() / 60) % 2));	//keicia prieso animacijos kadrus
	xg = xg - 2;

	if (counter <= 70)		//juda zigzagu
	{
		if ((counter < 35) && (yg<lango_h - hg))
			yg = yg + 2;
		if ((counter >= 35) && (yg > 0))
			yg = yg - 2;
	}
	if (counter == 70)
		counter = 0;

	if (xg <= -32)	//juda iki lango krasto
	{
		xg = lango_w;
	}

	if (shoot_counter == 100)	// kas 100 kadru isauna
	{
		shoot_counter = 0;
		shot = true;
	}
}


void Enemy::update_standby() //stovejimas vietoje
{
	xg = xg;	
}

void Enemy::mirties_animacija(int pass_kadr)//vykdoma mirties animacija
{
	CGameObject::mirties_animacija(pass_kadr);
	if (CGameObject::dead==true)
	{
		death = true;
	}
}

SDL_Rect Enemy::GetEnemyRekt()
{
	return (CGameObject::GetRekt(xg,yg,wg,hg));
}

int Enemy::GetEnemyK()
{
	return (CGameObject::GetKadr());
}