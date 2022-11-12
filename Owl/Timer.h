#ifndef OWL_TIMER_H
#define OWL_TIMER_H

class Timer
{
public:
	Timer();

	void Start();
	void Stop();
	float Reset();
	float GetElapsedTime();

private:
	bool m_bStoped;
	LARGE_INTEGER m_Start, m_End, m_Frequency;
};

#endif // !OWL_TIMER_H
