#ifndef OWL_DEBUG
#define OWL_DEBUG

enum EDebugMode
{
	Information = 0,
	Warning,
	Error,
};

namespace owl
{
	class Debug
	{
	public:
		static void OWL_API Log(EDebugMode mode, const char* text, bool bBreakLine = true, bool bUseTag = true) { GetInstance().ILog(mode, text, bBreakLine, bUseTag); }

	protected:
		Debug() {};

		// Deletes copy constructor and assigment operator
		Debug(const Debug&) = delete;
		Debug operator=(const Debug&) = delete;

		// Gets the class's static reference
		static Debug& GetInstance() { static Debug sInstance; return sInstance; }

	private:
		void ILog(EDebugMode mode, const char* text, bool bBreakLine, bool bUseTag);
	};
}

#endif // !OWL_DEBUG
