#ifndef __Game__
#define __Game__


#include "GameTimer.h"
#include "Texture.h"
#include "GameObject.h"
#include "Background.h"
#include "Collision.h"
#include "Sound.h"

const int FRAMES_PER_SECOND = 60;
#define priesu_kiekis 100
#define r_kiekis 40
#define k_kiekis 80

//pagrindine klase
class Game
{
public:
	Game() {}
	~Game() {}
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void render();
	void update(int width, int height);
	void handleEvents();
	void clean();
	void restart_the_game(int width, int height);

	bool running() { return ProgramRunning; }
private:

	std::vector<Enemy*> GetPriesai(){ return priesai; }

	SDL_Window* m_pWindow = 0;
	SDL_Renderer* m_pRenderer = 0;

	int dabartinis_kadras;
	int j, i, spwn, kill_count;
	int zaidejo_gyvybes, turimu_raketu_kiekis;
	int p_busena[priesu_kiekis];
	bool r_busena[r_kiekis];
	bool k_busena[k_kiekis];
	bool suzeide, shoot;
	double enemy_count;

	std::string tekstas1, tekstas2, tekstas3, tekstas4, tekstas5;
	CTexture score, life, rockets,game_over_text,you_win_text;
	int taskai;

	CGameObject pav_zaid, pav_raketa;
	CBackground fonas3,fonas2, fonas1;
	Player m_player;

	std::vector<Enemy*> priesai;

	Bullet raketos[r_kiekis];
	EnemyBullet kulkos[k_kiekis];

	SoundManager sprogimas, suvis_z, suvis_p, g_o;

	bool ProgramRunning;
};

#endif