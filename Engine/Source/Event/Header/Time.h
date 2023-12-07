#ifndef OWL_TIME
#define OWL_TIME

namespace owl
{
	class Time
	{
	public:
		// === GET methods ===

		// Gets the time passed in real life of a frame to another
		static float GetDeltaTime() { return GetInstance().m_DeltaTime; }

		// === Friends ===

		friend class Application;

	protected:
		Time();
		~Time();

		// Deletes copy constructor and assigment operator
		Time(const Time&) = delete;
		Time operator=(const Time&) = delete;

		// Gets the class's static reference
		static Time& GetInstance() { static Time s_Instance; return s_Instance; }

	private:
		// Attributes
		class Timer* m_pTimer;
		float m_DeltaTime;

		// === MAIN methods ===

		void DeltaTimeMonitor();
	};
}

#endif // !OWL_TIME
