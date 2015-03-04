#pragma once
#include "GameObject.h"
#include "Game.h"

class CCollision
{
private:
	static CCollision* s_pInstance;
public:
	bool susidurimas_zaidejas_kulka(Player* m_player, EnemyBullet* &kulkos);
	bool susidurimas_zaidejas_priesas(Player* m_player, const std::vector<Enemy*> &priesai, int prieso_nr);
	bool susidurimas_priesas_raketa(const std::vector<Enemy*> &priesai, int prieso_nr, Bullet* &raketos);
	static bool isColliding(SDL_Rect* A, SDL_Rect* B);

	static CCollision* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new CCollision();
			return s_pInstance;
		}
		return s_pInstance;
	}
};