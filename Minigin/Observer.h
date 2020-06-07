#pragma once
#include "Component.h"
#include "EventSystem.h"

namespace tait
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const Component& source, Event e) = 0;
	};
}