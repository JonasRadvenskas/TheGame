#include "GameObject.h"


CGameObject::CGameObject()
{
	moveup = false;
	movedown = false;
	mov_speed = 7;
	dyingTime = 25;
	dyingCounter = 0;
}


void CGameObject::load(int passed_xp, int passed_yp, int passed_wp, int passed_hp,
	int passed_xg, int passed_yg, int passed_wg, int passed_hg,
	int passed_lango_w, int passed_lango_h, int passed_nr)
{
	xp = passed_xp;
	yp = passed_yp;
	wp = passed_wp;
	hp = passed_hp;
	xg = passed_xg;
	yg = passed_yg;
	wg = passed_wg;
	hg = passed_hg;
	lango_w = passed_lango_w;
	lango_h = passed_lango_h;
	nr = passed_nr;
	kadras = 1;
	eile = 1;
}
void CGameObject::piesti(SDL_Renderer* pRenderer)
{
	CTexture::Instance()->piesti_kadra(nr, xp, yp, wp, hp, xg, yg, wg, hg, eile, kadras, pRenderer);
}
void CGameObject::update()
{
	kadras = 0;
	xg = xg;	//tai nesvarbu, nes sia funkcija perkraunu dukterinese klasese.
}

void CGameObject::mirties_animacija(int passed_k)
{
	nr = 5;
	xg = xg - 2;
	kadras = passed_k;
	if (dyingCounter == dyingTime)
	{
		dead = true;
	}
	dyingCounter++;
}

void CGameObject::clean()
{
}


void CGameObject::setY(int Y)
{
	yg = Y;
}

int CGameObject::getY()
{
	return yg;
}

SDL_Rect CGameObject::GetRekt(int x, int y, int w, int h)
{
	kvadratas.x = x;
	kvadratas.y = y;
	kvadratas.w = w;
	kvadratas.h = h;
	return (kvadratas);
}

int CGameObject::GetKadr()
{
	return kadras;
}

CGameObject::~CGameObject()
{

}