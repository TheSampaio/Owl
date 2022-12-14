#include "PCH.h"
#include "Window.h"

#include "Application.h"

Window::Window()
	: m_Id{ nullptr }, m_Icon{ nullptr }, m_Cursor{ nullptr }, m_Instance{ GetModuleHandle(nullptr) }
{
	// Default style
	m_Style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_EX_TOPMOST | WS_VISIBLE;

	// Title
	m_Title = std::string("Owl Engine");

	// Screen's size
	m_Screen[0] = GetSystemMetrics(SM_CXSCREEN);
	m_Screen[1] = GetSystemMetrics(SM_CYSCREEN);

	// Window's size
	m_Size[0] = 800;
	m_Size[1] = 600;

	// Window's center
	m_Center[0] = m_Size[0] / 2;
	m_Center[1] = m_Size[1] / 2;

	// Window's position
	m_Position[0] = 0;
	m_Position[1] = 0;

	// Window's display mode and background's color
	m_DisplayMode = EDisplayMode::IE_Windowed;
	m_BackgroundColor = RGB(0, 0, 0);
}

bool Window::Create()
{
	// Create and define window's class
	WNDCLASSEX WindowClass{ NULL };
	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.lpfnWndProc = Application::s_Input->Procedure;
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.cbClsExtra = NULL;
	WindowClass.cbWndExtra = NULL;
	WindowClass.lpszMenuName = NULL;
	WindowClass.hCursor = m_Cursor;
	WindowClass.hIcon = m_Icon;
	WindowClass.hIconSm = m_Icon;
	WindowClass.hInstance = m_Instance;
	WindowClass.hbrBackground = static_cast<HBRUSH>(CreateSolidBrush(m_BackgroundColor));
	WindowClass.lpszClassName = L"BasicWindow";

	// Register window's class
	(!RegisterClassEx(&WindowClass)) ? false : true;

	// Create window
	m_Id = CreateWindowEx
	(
		NULL,												  // Window's EXTRA style
		L"BasicWindow",										  // Window's class's name
		std::wstring(m_Title.begin(), m_Title.end()).c_str(), // Window's title
		m_Style,											  // Window's DEFAULT style
		m_Position[0], m_Position[1],						  // Window's position
		m_Size[0], m_Size[1],								  // Window's size
		NULL,												  // Window's parent
		NULL,												  // Window's menu
		m_Instance,											  // Window's instance (Id)
		NULL												  // Window's long pointer param
	);

	// Setup client area
	if (m_DisplayMode == EDisplayMode::IE_Windowed)
	{
		// Create new rect
		RECT Rect{ 0, 0, static_cast<LONG>(m_Size[0]), static_cast<LONG>(m_Size[1]) };

		// Change current window's rect to the new one
		AdjustWindowRectEx
		(
			&Rect,
			GetWindowStyle(m_Id),
			GetMenu(m_Id) != NULL,
			GetWindowStyle(m_Id)
		);

		// Update window's position
		m_Position[0] = (m_Screen[0] / 2) - static_cast<unsigned short>((Rect.right - Rect.left) / 2);
		m_Position[1] = (m_Screen[1] / 2) - static_cast<unsigned short>((Rect.bottom - Rect.top) / 2);

		// Apply changes
		MoveWindow(m_Id, m_Position[0], m_Position[1], m_Size[0], m_Size[1], true);
	}
	
	return (m_Id) ? true : false;
}

void Window::SetSize(unsigned short Width, unsigned short Height)
{
	// Window's size
	m_Size[0] = Width;
	m_Size[1] = Height;

	// Window's center
	m_Center[0] = m_Size[0] / 2;
	m_Center[1] = m_Size[1] / 2;

	// Adust window to screen's center
	m_Position[0] = (GetSystemMetrics(SM_CXSCREEN) / 2) - (m_Size[0] / 2);
	m_Position[1] = (GetSystemMetrics(SM_CYSCREEN) / 2) - (m_Size[1] / 2);
}

void Window::SetDisplayMode(unsigned short DisplayMode)
{
	m_DisplayMode = DisplayMode;

	// Windowed mode
	if (m_DisplayMode == EDisplayMode::IE_Windowed)
	{
		m_Style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_EX_TOPMOST | WS_VISIBLE;
	}

	// Bordless or fullscreen modes
	else
	{
		// Resizes window
		m_Size[0] = m_Screen[0];
		m_Size[1] = m_Screen[1];


		// Setup window's new position
		m_Position[0] = 0;
		m_Position[1] = 0;

		m_Style = WS_POPUP | WS_EX_TOPMOST | WS_VISIBLE;
	}
}
