#pragma once
#include "Singleton.h"
#include "Structs.h"
#include <map>

struct SDL_Window;
struct SDL_Renderer;

namespace tait
{
	class Texture2D;

	enum RenderLayers
	{
		Background_0 = 0,
		MainLayer_0 = 100,
		ForeGround_0 = 200
	};

	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, const Vector& p) const;
		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, const Rect& r) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderSprite(const Texture2D& texture, const Rect& dst, const Rect& src) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};

		Vector GetTransformedPosition(float x, float y) const;
	};
}

