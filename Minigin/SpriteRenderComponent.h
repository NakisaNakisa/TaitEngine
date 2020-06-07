#pragma once
#include "Component.h"
#include "SDL.h"

namespace tait
{
	class Texture2D;
	class SpriteRenderComponent final : public Component
	{
	public:
		void Render() const override;
		void Update() override;

		void SetSprite(const std::string& texturePath, int xAmount, int yAmount, float frameDuration, int amount);
		void SetSize(const Vector& size);
		void SetAmount(int amount) { m_Amount = amount; }
		void SetStartFrame(int startFrame);

		explicit SpriteRenderComponent(GameObject& go);
		virtual ~SpriteRenderComponent() = default;
		SpriteRenderComponent(const SpriteRenderComponent& other) = delete;
		SpriteRenderComponent(SpriteRenderComponent&& other) = delete;
		SpriteRenderComponent& operator=(const SpriteRenderComponent& other) = delete;
		SpriteRenderComponent& operator=(SpriteRenderComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_Texture;
		float m_Timer, m_FrameDuration;
		int m_Amount, m_XAmount, m_YAmount, m_CurrentFrame, m_StartFrame;
		Rect m_SrcRect, m_DstRect;

		void SetSpriteValues(int xAmount, int yAmount, float frameDuration, int amount);
	};
}
