#include "Texture.h"


CTexture* CTexture::s_pInstance = 0;


CTexture::CTexture()
{
	texture_list[100] = { NULL };

	TTF_Init();
};

bool CTexture::load(std::string vardas, int nr, SDL_Renderer* pRenderer)
{
	SDL_Texture* pTexture = IMG_LoadTexture(pRenderer, vardas.c_str());
	if (pTexture != 0)
	{
		texture_list[nr] = pTexture;
		return true;
	}
	return false;
}

void CTexture::piesti(int nr, int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, SDL_Renderer* pRenderer)
{
	pradinis_keturkampis.x = xp;
	pradinis_keturkampis.y = yp;
	pradinis_keturkampis.w = wp;
	pradinis_keturkampis.h = hp;
	galutinis_keturkampis.x = xg;
	galutinis_keturkampis.y = yg;
	galutinis_keturkampis.w = wg;
	galutinis_keturkampis.h = hg;
	SDL_RenderCopy(pRenderer, texture_list[nr], &pradinis_keturkampis, &galutinis_keturkampis);
}

void CTexture::piesti_kadra(int nr, int xp, int yp, int wp, int hp, int xg, int yg, int wg, int hg, int eile, int kadras, SDL_Renderer* pRenderer)
{
	pradinis_keturkampis.x = wp * kadras;
	pradinis_keturkampis.y = hp * (eile - 1);
	pradinis_keturkampis.w = wp;
	pradinis_keturkampis.h = hp;
	galutinis_keturkampis.x = xg;
	galutinis_keturkampis.y = yg;
	galutinis_keturkampis.w = wg;
	galutinis_keturkampis.h = hg;
	SDL_RenderCopy(pRenderer, texture_list[nr], &pradinis_keturkampis, &galutinis_keturkampis);
}

void CTexture::kurti_teksta(SDL_Renderer* pRenderer, std::string font_pav, int f_size, std::string score, int r, int g, int b, int x,int y)
{
	textDestRect.x = x;
	textDestRect.y = y;
	bg = { 0, 20, 20, 20 };
	color = {255, r, g, b };	//paruosia teksto spalva
	font = TTF_OpenFont(font_pav.c_str(), f_size);	//paruosia teksto srifta
	surfptr = TTF_RenderText_Shaded(font, score.c_str(), color ,bg);	//sukuria teksto pavirsiu
	text_texture = SDL_CreateTextureFromSurface(pRenderer, surfptr);
	SDL_QueryTexture(text_texture, NULL, NULL, &textDestRect.w, &textDestRect.h);
}

void CTexture::piesti_teksta(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, text_texture, NULL, &textDestRect);
}

void CTexture::trinti_teksta()
{
	SDL_FreeSurface(surfptr);
	SDL_DestroyTexture(text_texture);

}

CTexture::~CTexture()
{
	int i;
	SDL_DestroyTexture(text_texture);
	for (i = 0; i < 10; i++)
		SDL_DestroyTexture(texture_list[i]);
}