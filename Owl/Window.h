#ifndef OWL_WINDOW_H
#define OWL_WINDOW_H

#include "Default.h"
#include "Input.h"

class Window
{
public:
	enum EDisplayMode
	{
		BORDLESS = 0,
		FULLSCREEN,
		WINDOWED
	};

	Window(Input*& Input);

	// Main methods
	bool Create();	
	inline void Close() { PostMessage(m_Id, WM_DESTROY, NULL, NULL); }	

	// Get methods
	inline HWND GetId()	const								{ return m_Id; }
	inline HINSTANCE GetInstance() const					{ return m_Instance; }
	inline COLORREF GetBackgroundColor() const				{ return m_BackgroundColor; }
	inline std::string GetTitle() const						{ return m_Title; }
	inline std::array<unsigned int, 2> GetScreen() const	{ return m_Screen; }
	inline std::array<unsigned int, 2> GetSize() const		{ return m_Size; }
	inline std::array<unsigned int, 2> GetPosition() const	{ return m_Position; }
	inline std::array<unsigned int, 2> GetCenter() const	{ return m_Center; }
	inline unsigned int GetDisplayMode() const				{ return m_DisplayMode; }
	inline Input*& GetInput() { return s_Input; }

	// Set methods
	void SetSize(unsigned int Width, unsigned int Height);
	void SetDisplayMode(unsigned int DisplayMode);

	inline void SetTitle(const std::string Title)	 { m_Title = Title; }
	inline void SetIcon(const unsigned int Icon)	 { m_Icon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(Icon)); };
	inline void SetCursor(const unsigned int Cursor) { m_Cursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(Cursor)); };
	inline void SetBackgroundColor(unsigned int Red, unsigned int Green, unsigned int Blue) { m_BackgroundColor = RGB(Red, Green, Blue); }

private:
	HWND m_Id;
	HINSTANCE m_Instance;

	HICON m_Icon;
	HCURSOR m_Cursor;
	COLORREF m_BackgroundColor;
	DWORD m_Style;

	std::string m_Title;
	std::array<unsigned int, 2> m_Screen;
	std::array<unsigned int, 2> m_Size;
	std::array<unsigned int, 2> m_Position;
	std::array<unsigned int, 2> m_Center;

	unsigned int m_DisplayMode;
	
	static Input* s_Input;
};

#endif // !OWL_WINDOW_H
