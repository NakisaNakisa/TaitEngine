#include "TaitPCH.h"
#include "ThreadProviderh.h"

void tait::ThreadProvider::CleanUp()
{
	for (std::thread* thread : m_Threads)
	{
		if (thread->joinable())
			thread->join();
		delete thread;
	}
	m_Threads.clear();
}

int tait::ThreadProvider::CreateThread()
{
	m_Threads.push_back(new std::thread());
	int id = m_ThreadAmount;
	m_ThreadAmount++;
	return id;
}

std::thread* tait::ThreadProvider::GetThread(int id) const
{
	if(id < m_ThreadAmount)
		return m_Threads[id];
	return nullptr;
}
