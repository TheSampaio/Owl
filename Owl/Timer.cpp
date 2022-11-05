#include "PCH.h"
#include "Timer.h"

ITimer::ITimer()
	: m_bStoped(false)
{
	QueryPerformanceFrequency(&m_Frequency);

	ZeroMemory(&m_Start, sizeof(m_Start));
	ZeroMemory(&m_End, sizeof(m_End));
}

void ITimer::Start()
{
	if (m_bStoped)
	{
		long long ElapsedTime = m_End.QuadPart - m_Start.QuadPart;

		QueryPerformanceCounter(&m_Start);
		m_Start.QuadPart -= ElapsedTime;
		m_bStoped = false;
	}

	else
	{
		QueryPerformanceCounter(&m_Start);
	}
}

void ITimer::Stop()
{
	if (!m_bStoped)
	{
		QueryPerformanceCounter(&m_End);
		m_bStoped = true;
	}
}

float ITimer::Reset()
{
	long long ElapsedTime = 0;

	if (m_bStoped)
	{
		ElapsedTime = m_End.QuadPart - m_Start.QuadPart;
		QueryPerformanceCounter(&m_Start);
		m_bStoped = false;
	}

	else
	{
		QueryPerformanceCounter(&m_End);
		ElapsedTime = m_End.QuadPart - m_Start.QuadPart;
		m_Start = m_End;
	}

	return static_cast<float>(ElapsedTime / static_cast<double>(m_Frequency.QuadPart));
}

float ITimer::GetElapsedTime()
{
	long long ElapsedTime = 0;

	if (m_bStoped)
	{
		ElapsedTime = m_End.QuadPart - m_Start.QuadPart;
	}

	else
	{
		QueryPerformanceCounter(&m_End);
		ElapsedTime = m_End.QuadPart - m_Start.QuadPart;
	}

	return static_cast<float>(ElapsedTime / static_cast<double>(m_Frequency.QuadPart));
}
