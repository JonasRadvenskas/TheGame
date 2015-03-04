#include "GameObject.h"

Player* Player::s_pInstance = 0;

void Player::load(int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, int lango_w, int lango_h, int nr)//, CCollisionRectangle passed_CollisionRect)
{
	CGameObject::load(xp, yp, wp, hp, xg, yg, wg, hg, lango_w, lango_h, nr);
}



void Player::piesti(SDL_Renderer* pRenderer)
{
	CGameObject::piesti(pRenderer);//piesia zaideja.
}



void Player::update()
{
	kadras = int(((SDL_GetTicks() / 80) % 3));//keicia zaidejo animacijos kadrus

	if ((moveup) && (yg > 0))
	{
		setY(yg - mov_speed);
	}
	else if ((movedown) && (yg <lango_h - wp+30))
	{
		setY(yg + mov_speed);
	}
}


SDL_Rect Player::GetPlayerRekt()
{
	return (CGameObject::GetRekt(xg, yg, wg, hg));
}