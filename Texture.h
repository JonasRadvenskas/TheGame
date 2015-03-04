#pragma once
#include "MainHeader.h"


class CTexture
{
private:
	SDL_Texture*  texture_list[100];
	static CTexture* s_pInstance;

	SDL_Rect pradinis_keturkampis;
	SDL_Rect galutinis_keturkampis;

	//tekstui (taskams ir gyvybems) rasyti
	SDL_Rect textDestRect;
	SDL_Surface *surfptr;
	SDL_Color color, bg;
	TTF_Font *font;
	SDL_Texture *text_texture;
public:
	CTexture();
	~CTexture();

	static CTexture* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new CTexture();
			return s_pInstance;
		}
		return s_pInstance;
	}
	
	bool load(std::string failo_pav, int nr, SDL_Renderer* pRenderer);
	void piesti(int nr, int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, SDL_Renderer* pRenderer);
	void piesti_kadra(int nr, int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, int eile, int kadras, SDL_Renderer* pRenderer);

	void kurti_teksta(SDL_Renderer* pRenderer, std::string font_pav, int f_size, std::string score, int r, int g, int b, int x,int y);
	void piesti_teksta(SDL_Renderer* pRenderer);
	void trinti_teksta();
};

