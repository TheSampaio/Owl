#include "Engine.h"
#include "Header/Timer.h"

using namespace std::chrono;

owl::Timer::Timer()
{
	// Initializes all class's attributes
	m_Start = steady_clock::time_point();
	m_End = steady_clock::time_point();

	m_bPaused = false;
}

void owl::Timer::Start()
{
	if (m_bPaused)
	{
		// Calculates elapsed time
		duration elapsedTime = m_End - m_Start;

		// Starts time considering the elapsed time
		m_Start = steady_clock::now();
		m_Start -= elapsedTime;
		m_bPaused = false;
	}

	else
	{
		// Starts timer's count
		m_Start = steady_clock::now();
	}
}

void owl::Timer::Stop()
{
	if (!m_bPaused)
	{
		// Sets timer's stop
		m_End = steady_clock::now();
		m_bPaused = true;
	}
}

float owl::Timer::Reset()
{
	duration elapsedTime = nanoseconds(0);

	if (m_bPaused)
	{
		// Gets elapsed time before stops
		elapsedTime = m_End - m_Start;

		// Reset timer's count
		m_Start = steady_clock::now();
		m_bPaused = false;
	}

	else
	{
		// Stops timer's count and get the elapsed time
		m_End = steady_clock::now();
		elapsedTime = m_End - m_Start;

		// Resets timer's count
		m_Start = m_End;
	}

	// Returns time in seconds
	return static_cast<float>(duration<double>(elapsedTime).count());
}

float owl::Timer::GetElapsedTime()
{
	duration elapsedTime = nanoseconds(0);

	if (m_bPaused)
	{
		// Calculates elapsed time
		elapsedTime = m_End - m_Start;
	}

	else
	{
		// Stops timer's count and get the elapsed time
		m_End = steady_clock::now();
		elapsedTime = m_End - m_Start;
	}

	// Returns time in seconds
	return static_cast<float>(duration<double>(elapsedTime).count());
}
