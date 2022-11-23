#pragma once

#include "Input.h"

class Window
{
public:
	enum EDisplayMode
	{
		IE_Bordless = 0,
		IE_Fullscreen,
		IE_Windowed
	};

	Window();

	// Main methods
	bool Create();	
	inline void Close() { PostMessage(m_Id, WM_DESTROY, NULL, NULL); }	

	// Get methods
	inline HWND& GetId()                  { return m_Id; }
	inline HINSTANCE& GetInstance()       { return m_Instance; }
	inline COLORREF& GetBackgroundColor() { return m_BackgroundColor; }

	inline std::string& GetTitle()                      { return m_Title; }
	inline std::array<unsigned short, 2>& GetScreen()   { return m_Screen; }
	inline std::array<unsigned short, 2>& GetSize()     { return m_Size; }
	inline std::array<unsigned short, 2>& GetPosition() { return m_Position; }
	inline std::array<unsigned short, 2>& GetCenter()   { return m_Center; }
	inline unsigned int GetDisplayMode()&               { return m_DisplayMode; }

	// Set methods
	void SetSize(unsigned short Width, unsigned short Height);
	void SetDisplayMode(unsigned short DisplayMode);

	inline void SetTitle(const std::string Title)      { m_Title = Title; }
	inline void SetIcon(const unsigned short Icon)     { m_Icon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(Icon)); };
	inline void SetCursor(const unsigned short Cursor) { m_Cursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(Cursor)); };

	inline void SetBackgroundColor(unsigned short Red, unsigned short Green, unsigned short Blue) { m_BackgroundColor = RGB(Red, Green, Blue); }

private:
	HWND m_Id;
	HINSTANCE m_Instance;

	HICON m_Icon;
	HCURSOR m_Cursor;
	COLORREF m_BackgroundColor;
	DWORD m_Style;

	std::string m_Title;
	std::array<unsigned short, 2> m_Screen;
	std::array<unsigned short, 2> m_Size;
	std::array<unsigned short, 2> m_Position;
	std::array<unsigned short, 2> m_Center;
	unsigned short m_DisplayMode;
};
