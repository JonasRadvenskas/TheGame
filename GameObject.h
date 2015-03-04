#pragma once
#include "MainHeader.h"
#include "Texture.h"

class CGameObject		//pagrindine veikiancio objekto klase.
{
public:
	CGameObject();
	~CGameObject();
	void load(int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, int lango_w, int lango_h, int nr);
	void piesti(SDL_Renderer* pRenderer);
	void update();
	void clean();

	int GetKadr();
	SDL_Rect GetRekt(int x, int y, int w, int h);

	void setY(int y);
	int getY();

	void SetMoveup(bool p_moveup) { moveup = p_moveup; }
	void SetMovedown(bool p_movedown){ movedown = p_movedown; }

	void mirties_animacija(int passed_k);
protected:
	bool moveup;
	bool movedown;
	int mov_speed;
	int xp, yp, wp, hp, xg, yg, wg, hg, nr, lango_w, lango_h;
	int kadras, i, eile;
	int dyingTime, dyingCounter;
	bool dead;
	SDL_Rect kvadratas;
};



class Player : public CGameObject	//paveldima is CGameObject zaidejo klase
{
private:
	static Player* s_pInstance;
public:
	void load(int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, int lango_w, int lango_h, int nr);
	void piesti(SDL_Renderer* pRenderer);
	void update();
	void clean();
	int GetPlayerY(){ return yg; }

	SDL_Rect GetPlayerRekt();


	static Player* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Player();
			return s_pInstance;
		}
		return s_pInstance;
	}
};



class Enemy : public CGameObject	//paveldima is CGameObject prieso klase
{
private:
	int counter;
	int shoot_counter;
	bool death;
	bool shot;
	static Enemy* s_pInstance;
public:
	Enemy(){};
	Enemy(int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, int lango_w, int lango_h, int nr);
	~Enemy(){};
	void piesti(SDL_Renderer* pRenderer);
	void update();
	void update_standby();
	void mirties_animacija(int pass_kadr);
	void clean();

	int GetEnemyK();
	int GetEnemyX(){ return xg; }
	int GetEnemyY(){ return yg; }
	void SetEnemyX(int param_x){ xg = param_x; }
	SDL_Rect GetEnemyRekt();

	void SetShootCounter(int p_counter){ shoot_counter = p_counter; }

	void SetShot(bool p_shot){ shot = p_shot; }
	bool GetShot(){ return shot; }
	void SetDeath(bool p_death){ death = p_death; }
	bool GetDeath(){ return death; }

	static Enemy* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Enemy();
			return s_pInstance;
		}
		return s_pInstance;
	}
};



class Bullet :public Player		//paveldima is klases Player zaidejo raketu klase
{
private:
	bool raketos_busena;
public:
	Bullet();
	void load(int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, int lango_w, int lango_h, int nr);
	void piesti(SDL_Renderer* pRenderer);
	void update();
	void clean();

	void SetRocketBusena(bool passed_value);
	bool GetRocketBusena(){ return raketos_busena; }

	SDL_Rect GetRocketRekt();
	void SetRocketX(int param_x){ xg = param_x; }
	void SetRocketY(int param_y){ yg = param_y; }
};



class EnemyBullet : public Bullet	//paveldima is Bullet prieso kulku klase
{
private:
	bool kulkos_busena;
public:
	EnemyBullet();
	void load(int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, int lango_w, int lango_h, int nr);
	void piesti(SDL_Renderer* pRenderer);
	void update();
	void clean();

	void SetBulletBusena(bool passed_value);
	bool GetBulletBusena(){ return kulkos_busena; }

	SDL_Rect GetBulletRekt();
	void SetBulletX(int param_x){ xg = param_x; }
	void SetBulletY(int param_y){ yg = param_y; }
};