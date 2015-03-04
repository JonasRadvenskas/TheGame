#include "Texture.h"
#include "MainHeader.h"

class CBackground
{
private:
	int scroll_speed, nr;
	SDL_Rect m_srcRect1, m_srcRect2, m_destRect1, m_destRect2;
	int pav_width, pav_height,lango_width, lango_height, count;
public:
	void scrolling(int m_width, int m_height, int image_width, int image_height, int nr, int scroll_speed);//=load
	void piesti(SDL_Renderer* pRenderer);
	void update();
};