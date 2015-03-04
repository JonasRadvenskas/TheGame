#include "Collision.h"


CCollision* CCollision::s_pInstance = 0;

const static int s_buffer = 4;
bool CCollision::isColliding(SDL_Rect* A, SDL_Rect* B)
{
	//dalys, kurios isimamos is paveiksliuko sonu
	int aHBuf = A->h / s_buffer;
	int aWBuf = A->w / s_buffer;
	int bHBuf = B->h / s_buffer;
	int bWBuf = B->w / s_buffer;
	//jei a apacia mazesne uz B virsu- susidurimo nebuvo
	if ((A->y + A->h) - aHBuf <= B->y + bHBuf) { return false; }
	//jei a virsus daugiau uz b apacia- susidurimo nebuvo
	if (A->y + aHBuf >= (B->y + B->h) - bHBuf) { return false; }
	//jei a desine yra maziau uz b kaire- susidurimo nebuvo
	if ((A->x + A->w) - aWBuf <= B->x + bWBuf) { return false; }
	//jei a kaire yra daugiau uz b desine- susidurimo nebuvo
	if (A->x + aWBuf >= (B->x + B->w) - bWBuf) { return false; }
	//kitais atvejais- susidurimas buvo
	return true;
}


bool CCollision::susidurimas_zaidejas_kulka(Player* m_player, EnemyBullet* &kulkos/*, int kulkos_nr*/)
{
	if (isColliding(&m_player->GetPlayerRekt(), &kulkos->GetBulletRekt()))
	{
		return true;
	}
	return false;
}


bool CCollision::susidurimas_priesas_raketa(const std::vector<Enemy*> &priesai, int prieso_nr, Bullet* &raketos)
{
	if (isColliding(&priesai[prieso_nr]->GetEnemyRekt(), &raketos->GetRocketRekt()))
	{
		return true;
	}
	return false;
}


bool CCollision::susidurimas_zaidejas_priesas(Player* m_player, const std::vector<Enemy*> &priesai, int prieso_nr)
{
	if (isColliding(&m_player->GetPlayerRekt(), &priesai[prieso_nr]->GetEnemyRekt()))
	{
		return true;
	}
	return false;
}