#include "PCH.h"
#include "Window.h"

bool CWindow::s_Keys[256] = { false };
std::array<int, 2> CWindow::s_Mouse = { 0 };

CWindow::CWindow()
	: m_Id(NULL), m_Instance(GetModuleHandle(NULL)), m_Style(WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_EX_TOPMOST | WS_VISIBLE)
{
	// Title
	m_Title = std::string("Owl Engine");

	// Screen's size
	m_Screen[0] = GetSystemMetrics(SM_CXSCREEN);
	m_Screen[1] = GetSystemMetrics(SM_CYSCREEN);

	// CWindow's size
	m_Size[0] = 800;
	m_Size[1] = 600;

	// CWindow's center
	m_Center[0] = m_Size[0] / 2;
	m_Center[1] = m_Size[1] / 2;

	// CWindow's position
	m_Position[0] = 0;
	m_Position[1] = 0;

	// CWindow's icon and cursor
	m_Icon = LoadIcon(m_Instance, MAKEINTRESOURCE(IDI_ICON));
	m_Cursor = LoadCursor(m_Instance, MAKEINTRESOURCE(IDC_CURSOR));

	// CWindow's display mode and background's color
	m_DisplayMode = EDisplayMode::WINDOWED;
	m_BackgroundColor = RGB(0, 0, 0);
}

bool CWindow::Create()
{
	// Create and define window's class
	WNDCLASSEX CWindow{ NULL };
	CWindow.cbSize = sizeof(CWindow);
	CWindow.lpfnWndProc = CWindow::Procedure;
	CWindow.style = CS_HREDRAW | CS_VREDRAW;
	CWindow.cbClsExtra = NULL;
	CWindow.cbWndExtra = NULL;
	CWindow.lpszMenuName = NULL;
	CWindow.hCursor = m_Cursor;
	CWindow.hIcon = m_Icon;
	CWindow.hIconSm = m_Icon;
	CWindow.hInstance = m_Instance;
	CWindow.hbrBackground = static_cast<HBRUSH>(CreateSolidBrush(m_BackgroundColor));
	CWindow.lpszClassName = L"BasicWindow";

	// Register window's class
	(!RegisterClassEx(&CWindow)) ? false : true;

	// Create window
	m_Id = CreateWindowEx
	(
		NULL,												  // CWindow's EXTRA style
		L"BasicWindow",										  // CWindow's class's name
		std::wstring(m_Title.begin(), m_Title.end()).c_str(), // CWindow's title
		m_Style,											  // CWindow's DEFAULT style
		m_Position[0], m_Position[1],						  // CWindow's position
		m_Size[0], m_Size[1],								  // CWindow's size
		NULL,												  // CWindow's parent
		NULL,												  // CWindow's menu
		m_Instance,											  // CWindow's instance (Id)
		NULL												  // CWindow's long pointer param
	);

	// Setup client area
	if (m_DisplayMode == EDisplayMode::WINDOWED)
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
		m_Position[0] = (m_Screen[0] / 2) - ((Rect.right - Rect.left) / 2);
		m_Position[1] = (m_Screen[1] / 2) - ((Rect.bottom - Rect.top) / 2);

		// Apply changes
		MoveWindow(m_Id, m_Position[0], m_Position[1], m_Size[0], m_Size[1], true);
	}
	
	return (m_Id) ? true : false;
}

void CWindow::SetSize(unsigned int Width, unsigned int Height)
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

void CWindow::SetDisplayMode(unsigned int DisplayMode)
{
	m_DisplayMode = DisplayMode;

	// Windowed mode
	if (m_DisplayMode == EDisplayMode::WINDOWED)
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

LRESULT CWindow::Procedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	/* ========== KEYBOARD ==================== */
	// If keyboard's key was pressed
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		s_Keys[wParam] = true;
		
		if (s_Keys[VK_F4])
		{
			// Ask if user want to close the window
			if (MessageBox(hWindow, L"Do you really want to close the window?", L"Window", MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES)
			{
				PostMessage(hWindow, WM_DESTROY, NULL, NULL);
				return 0;
			}

			else
			{
				s_Keys[VK_F4] = false;
				return 0;
			}
		}

		return 0;

	// If keyboard's key was released
	case WM_KEYUP:
	case WM_SYSKEYUP:
		s_Keys[wParam] = false;
		return 0;

	/* ========== MOUSE ==================== */
	// If mouse move
	case WM_MOUSEMOVE:
		s_Mouse[0] = GET_X_LPARAM(lParam);
		s_Mouse[1] = GET_Y_LPARAM(lParam);
		return 0;

	// If mouse's left button pressed
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		s_Keys[VK_LBUTTON] = true;
		return 0;

	// If mouse's left button released
	case WM_LBUTTONUP:
		s_Keys[VK_LBUTTON] = false;
		return 0;

	// If mouse's right button pressed
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		s_Keys[VK_RBUTTON] = true;
		return 0;

	// If mouse's right button released
	case WM_RBUTTONUP:
		s_Keys[VK_RBUTTON] = false;
		return 0;

	/* ========== WINDOW ==================== */
	// If window was closed
	case WM_QUIT:
	case WM_CLOSE:
		PostMessage(hWindow, WM_DESTROY, NULL, NULL);
		return 0;

	// If window was destroyed
	case WM_DESTROY:
		PostQuitMessage(NULL);
		return 0;

	// Else return default behavior
	default:
		return DefWindowProc(hWindow, uMessage, wParam, lParam);
	}
}
