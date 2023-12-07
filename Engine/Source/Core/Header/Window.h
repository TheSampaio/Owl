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
		static std::array<ushort, 2> OWL_API GetSize() { return GetInstance().m_Size; }
		static std::array<ushort, 2> OWL_API GetScreen() { return GetInstance().m_Screen; }
		static std::array<ushort, 2> OWL_API GetPosition() { return GetInstance().m_Position; }
		static std::array<ushort, 3> OWL_API GetBackgroundColour() { return GetInstance().m_BackgroundColour; }

		// SET methods

		static void OWL_API SetTitle(std::string_view title) { GetInstance().m_Title = title; }
		static void OWL_API SetSize(ushort width, ushort height) { GetInstance().m_Size = { width, height }; }
		static void OWL_API SetBackgroundColour(ushort red, ushort green, ushort blue) { GetInstance().m_BackgroundColour = { red, green, blue }; }

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
		std::string m_Title;
		std::array<ushort, 2> m_Size;
		std::array<ushort, 2> m_Screen;
		std::array<ushort, 2> m_Position;
		std::array<ushort, 3> m_BackgroundColour;

		bool Create();
		bool IClose();
	};
}

#endif // !OWL_WINDOW
