#include "TaitPCH.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include <SDL.h>
#include "Time.h"
#include "GameObject.h"

void tait::SpriteRenderComponent::Render() const
{
	if (m_Texture)
		Renderer::GetInstance().RenderSprite(*m_Texture, m_DstRect, m_SrcRect);
}

void tait::SpriteRenderComponent::Update()
{
	m_DstRect.x = m_GameObject.GetTransform().GetPosition().x;
	m_DstRect.y = m_GameObject.GetTransform().GetPosition().y;
	if (!m_IsUpdating)
		return;
	m_Timer += Time::GetInstance().GetDeltaTime();
	if (m_Timer >= m_FrameDuration)
	{
		m_CurrentFrame++;
		if (m_CurrentFrame >= m_Amount + m_StartFrame)
			m_CurrentFrame = m_StartFrame;
		m_Timer -= m_FrameDuration;
		m_SrcRect.x = (m_CurrentFrame % m_XAmount) * m_SrcRect.w;
		m_SrcRect.y = (m_CurrentFrame / m_XAmount) * m_SrcRect.h;
	}
}

void tait::SpriteRenderComponent::SetSprite(const std::string& texturePath, int xAmount, int yAmount, float frameDuration, int amount)
{
	if (m_Texture)
		m_Texture.reset();
	m_Texture = ResourceManager::GetInstance().LoadTexture(texturePath);
	SetSpriteValues(xAmount, yAmount, frameDuration, amount);
}

void tait::SpriteRenderComponent::SetSize(const Vector& size)
{
	m_DstRect.w = size.x;
	m_DstRect.h = size.y;
}

void tait::SpriteRenderComponent::SetStartFrame(int startFrame)
{ 
	if (m_StartFrame != startFrame)
	{
		m_StartFrame = startFrame;
		m_CurrentFrame = m_StartFrame;
	}
}

tait::SpriteRenderComponent::SpriteRenderComponent(GameObject& go)
	: Component(go)
	, m_SrcRect{}
	, m_DstRect{}
{
}

void tait::SpriteRenderComponent::SetSpriteValues(int xAmount, int yAmount, float frameDuration, int amount)
{
	if (amount > -1)
		m_Amount = amount;
	else
		m_Amount = xAmount * yAmount;
	m_YAmount = yAmount;
	m_XAmount = xAmount;
	m_FrameDuration = frameDuration;
	int w, h;
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &w, &h);
	m_SrcRect.w = (float)w / m_XAmount;
	m_SrcRect.h = (float)h / m_YAmount;
}
