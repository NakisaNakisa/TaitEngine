#pragma once
#include "Component.h"
#include "SDL.h"

namespace tait
{
	class Font;
	class Texture2D;
	class RenderComponent final : public Component
	{
	public:
		void Render() const override;
		void Update() override;

		Vector GetSize() const;

		void SetPosition(const Vector& s);
		void SetSize(const Vector& s);
		void SetDestRect(const Rect& r);
		void SetText(const std::string& text, SDL_Color color = SDL_Color{ 255,255,0,255 });
		void SetTexture(const std::string& dataPath);

		explicit RenderComponent(GameObject& go);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		SDL_Color m_FontColor;
		std::shared_ptr<Texture2D> m_TextTexture;
		std::shared_ptr<Texture2D> m_Texture;
		Rect m_DestRect{};
	};
}
