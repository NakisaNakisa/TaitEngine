#include "TaitPCH.h"
#include "Texture2D.h"
#include <SDL.h>

tait::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* tait::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

tait::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
