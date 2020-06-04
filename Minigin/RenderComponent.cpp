#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Font.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include "ResourceManager.h"

void dae::RenderComponent::Render() const
{
	const auto pos = m_GameObject.GetTransform().GetPosition();

	if (m_Texture)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
	if (m_TextTexture)
	{
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

void dae::RenderComponent::Update()
{
	if (m_NeedsUpdate)
	{
		if (!m_Font)
			m_Font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_FontColor);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::RenderComponent::SetText(std::string text, SDL_Color color)
{
	if (m_Text != text|| (color.r != m_FontColor.r || color.g != m_FontColor.g || color.b != m_FontColor.b || color.a != m_FontColor.a))
	{
		m_Text = text;
		m_NeedsUpdate = true;
		m_FontColor = color;
		if (m_TextTexture)
			m_TextTexture.reset();
	}
}


void dae::RenderComponent::SetTexture(std::string dataPath)
{
	if (m_Texture)
		m_Texture.reset();
	m_Texture = ResourceManager::GetInstance().LoadTexture(dataPath);
}

dae::RenderComponent::RenderComponent(GameObject& go)
	:Component(go)
{
}
