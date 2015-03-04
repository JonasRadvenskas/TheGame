#include "Game.h"


Game* g_game = 0;
int main(int argc, char* argv[])
{
	Timer fps;
	g_game = new Game();
	//paskutinis parametras- norime per visa ekrana ar ne.
	g_game->init("Shoot Da Aliens- Defend Da Planet v0.9", 200, 80, 1000, 640, 0);
	while (g_game->running())
	{
		fps.start();	//pradeda kadru skaiciavima
		g_game->handleEvents();
		g_game->update(1000, 640);
		g_game->render();
		if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND)	//uzdeda kadru limita
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}
	g_game->clean();
	return 0;
}