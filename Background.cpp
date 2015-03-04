#include "Background.h"


//krauna
void CBackground::scrolling(int passed_width, int passed_height, int image_width, int image_height, int passed_nr, int passed_scroll_speed)
{
	scroll_speed = passed_scroll_speed;
	count = 0;
	nr = passed_nr;

	lango_width = passed_width;//lango
	lango_height = passed_height;//lango
	pav_width = image_width;//fono paveiksliuko
	pav_height = image_height;//fono paveiksliuko

	m_srcRect1.x = 0;
	m_srcRect1.y = 0;
	m_srcRect1.w = pav_width;
	m_srcRect1.h = pav_height;
	m_srcRect2.x = 0;
	m_srcRect2.y = 0;
	m_srcRect2.w = pav_width;
	m_srcRect2.h = pav_height;
	
	m_destRect1.x = 0;
	m_destRect1.y = 0;
	m_destRect1.w = lango_width;
	m_destRect1.h = lango_height;
	m_destRect2.x = lango_width;
	m_destRect2.y = 0;
	m_destRect2.w = lango_width;
	m_destRect2.h = lango_height;
}


//piesia
void CBackground::piesti(SDL_Renderer* pRenderer)
{
	CTexture::Instance()->piesti(nr, m_srcRect1.x, m_srcRect1.y, m_srcRect1.w, m_srcRect1.h,
		m_destRect1.x, m_destRect1.y, m_destRect1.w, m_destRect1.h, pRenderer);

	CTexture::Instance()->piesti(nr, m_srcRect2.x, m_srcRect2.y, m_srcRect2.w, m_srcRect2.h,
		m_destRect2.x, m_destRect2.y, m_destRect2.w, m_destRect2.h, pRenderer);
}


//judina
void CBackground::update()
{
	m_destRect1.x = m_destRect1.x - scroll_speed;
	m_destRect2.x = m_destRect2.x - scroll_speed;
	if (count >= lango_width)
		{
		m_srcRect1.x = 0;
		m_srcRect1.y = 0;
		m_srcRect1.w = pav_width;
		m_srcRect1.h = pav_height;
		m_srcRect2.x = 0;
		m_srcRect2.y = 0;
		m_srcRect2.w = pav_width;
		m_srcRect2.h = pav_height;
		m_destRect1.x = 0;
		m_destRect1.y = 0;
		m_destRect1.w = lango_width;
		m_destRect1.h = lango_height;
		m_destRect2.x = lango_width;
		m_destRect2.y = 0;
		m_destRect2.w = lango_width;
		m_destRect2.h = lango_height;
		count = 0;
		}
	count = count + scroll_speed;
}