#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "CameraComponent.h"
#include "Scene.h"
#include "GameObject.h"

void tait::Renderer::Init(SDL_Window * window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void tait::Renderer::Render() const
{
	SDL_RenderClear(m_Renderer);

	CameraComponent* cam = SceneManager::GetInstance().GetActiveScene().GetCamera();

	if (cam == nullptr)
		return;

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_Renderer);
}

void tait::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void tait::Renderer::RenderTexture(const Texture2D& texture, const Vector& p) const
{
	RenderTexture(texture, p.x, p.y);
}

void tait::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	Vector p = GetTransformedPosition(x, y);
	SDL_Rect dst;
	dst.x = static_cast<int>(p.x);
	dst.y = static_cast<int>(p.y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void tait::Renderer::RenderTexture(const Texture2D& texture, const Rect& r) const
{
	RenderTexture(texture, r.x, r.y, r.w, r.h);
}

void tait::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	Vector p = GetTransformedPosition(x, y);
	SDL_Rect dst;
	dst.x = static_cast<int>(p.x);
	dst.y = static_cast<int>(p.y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void tait::Renderer::RenderSprite(const Texture2D& texture, const Rect& dst, const Rect& src) const
{
	Vector p = GetTransformedPosition(dst.x, dst.y);
	SDL_Rect _dst;
	_dst.x = (int)p.x;
	_dst.y = (int)p.y;
	_dst.h = (int)dst.h;
	_dst.w = (int)dst.w;
	SDL_Rect _src;
	_src.x = (int)src.x;
	_src.y = (int)src.y;
	_src.h = (int)src.h;
	_src.w = (int)src.w;
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &_src, &_dst);
}

tait::Vector tait::Renderer::GetTransformedPosition(float x, float y) const
{
	CameraComponent* cam = SceneManager::GetInstance().GetActiveScene().GetCamera();
	return Vector{ x,y } - cam->GetGameObject().GetTransform().GetPosition();
}
