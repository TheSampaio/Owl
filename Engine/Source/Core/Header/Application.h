#ifndef OWL_APPLICATION
#define OWL_APPLICATION

namespace owl
{
	// Forward declarations
	class Game;

	class Application
	{
	public:
		static bool OWL_API Run(Game* game) { return GetInstance().IRun(*game); }

	protected:
		Application();
		~Application();

		// Deletes copy constructor and assigment operator
		Application(const Application&) = delete;
		Application operator=(const Application&) = delete;

		// Gets the class's static reference
		static Application& GetInstance() { static Application s_Instance; return s_Instance; }

	private:
		bool Initialize();
		bool IRun(Game& game);

		Game* m_Game;
	};
}

#endif // !OWL_APPLICATION
