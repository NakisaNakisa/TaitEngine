#pragma once
#include "Component.h"
#include "SDL.h"

namespace tait
{
	class CameraComponent final : public Component
	{
	public:
		explicit CameraComponent(GameObject& go);
		virtual ~CameraComponent() = default;
		CameraComponent(const CameraComponent& other) = delete;
		CameraComponent(CameraComponent&& other) = delete;
		CameraComponent& operator=(const CameraComponent& other) = delete;
		CameraComponent& operator=(CameraComponent&& other) = delete;
	private:

	};
}
