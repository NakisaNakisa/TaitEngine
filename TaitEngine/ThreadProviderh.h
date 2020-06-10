#pragma once
#include <thread>
#include "Singleton.h"

namespace tait
{
	class ThreadProvider : public Singleton<ThreadProvider>
	{
	public:
		void CleanUp();
		int CreateThread();
		std::thread* GetThread(int id) const;
	private:
		std::vector<std::thread*> m_Threads{};
		int m_ThreadAmount;
	};
}