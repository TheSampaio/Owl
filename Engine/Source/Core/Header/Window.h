#ifndef OWL_WINDOW
#define OWL_WINDOW

enum EWindowDisplayMode
{
	Bordless = 0,
	Fullscreen,
	Windowed
};

namespace owl
{
	class Window
	{
	public:
		static OWL_API bool Close() { return GetInstance().IClose(); }

		// GET methods

		static std::string OWL_API GetTitle() { return GetInstance().m_Title; }
		static std::array<u16, 2> OWL_API GetSize() { return GetInstance().m_Size; }
		static std::array<u16, 2> OWL_API GetScreen() { return GetInstance().m_Screen; }
		static std::array<u16, 2> OWL_API GetPosition() { return GetInstance().m_Position; }
		static std::array<u8, 3> OWL_API GetBackgroundColour() { return GetInstance().m_BackgroundColour; }

		// SET methods

		static void OWL_API SetTitle(const std::string& title) { GetInstance().m_Title = title; }
		static void OWL_API SetSize(u16 width, u16 height) { GetInstance().m_Size = { width, height }; }
		static void OWL_API SetDisplayMode(EWindowDisplayMode mode) { GetInstance().m_DisplayMode = mode; }
		static void OWL_API SetBackgroundColour(u8 red, u8 green, u8 blue) { GetInstance().m_BackgroundColour = { red, green, blue }; }
		static void OWL_API SetInitializeMaximized(bool maximize) { GetInstance().m_bMaximized = maximize; }

		// Friends
		friend class Application;
		friend class Input;
		friend class Graphics;

	protected:
		Window();
		~Window();

		// Deletes copy constructor and assigment operator
		Window(const Window&) = delete;
		Window operator=(const Window&) = delete;

		// Gets the class's static reference
		static Window& GetInstance() { static Window sInstance; return sInstance; }

	private:
		GLFWwindow* m_Id;
		GLFWmonitor* m_Monitor;

		std::string m_Title;
		std::array<u16, 2> m_Size;
		std::array<u16, 2> m_Screen;
		std::array<u16, 2> m_Position;
		std::array<u8, 3> m_BackgroundColour;

		EWindowDisplayMode m_DisplayMode;
		bool m_bMaximized;

		bool Create();
		bool IClose();
	};
}

#endif // !OWL_WINDOW
