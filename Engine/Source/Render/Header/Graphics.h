#ifndef OWL_GRAPHICS
#define OWL_GRAPHICS

enum EVerticalSynchronizationMode
{
	Disabled = 0,
	Full,
	Half
};

namespace owl
{
	class Graphics
	{
	public:
		static void OWL_API SetVerticalSynchronization(EVerticalSynchronizationMode mode) { GetInstance().m_VSyncMode = mode; }

		// GET methods

		static std::array<u8, 2> OWL_API GetContextVersion() { return GetInstance().m_ContextVersion; }

		// SET methods

		static void OWL_API SetContextVersion(u8 major, u8 minor) { GetInstance().m_ContextVersion = { major, minor }; }

		friend class Application;

	protected:
		Graphics();

		// Deletes copy constructor and assigment operator
		Graphics(const Graphics&) = delete;
		Graphics operator=(const Graphics&) = delete;

		// Gets the class's static reference
		static Graphics& GetInstance() { static Graphics s_Instance; return s_Instance; }

	private:
		EVerticalSynchronizationMode m_VSyncMode;
		std::array<u8, 2> m_ContextVersion;

		bool Initialize();
		void ClearBuffers();
		void SwapBuffers();
	};
}

#endif // !OWL_GRAPHICS
