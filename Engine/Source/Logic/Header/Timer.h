#ifndef OWL_TIMER
#define OWL_TIMER

namespace owl
{
	class Timer
	{
	public:
		Timer();

		// === MAIN methods ======

		// Starts the timer
		void OWL_API Start();

		// Stops the timer
		void OWL_API Stop();

		// Resets the timer
		f32 OWL_API Reset();

		// === GET methods ======

		// Gets the elapsed time since the timer's start
		f32 OWL_API GetElapsedTime();

	private:
		// Attributes
		std::chrono::steady_clock::time_point m_Start;
		std::chrono::steady_clock::time_point m_End;

		bool m_bPaused;
	};
}

#endif // !OWL_TIMER
