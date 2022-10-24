#include "PCH.h"
#include "Application.h"

// Initialize window's static pointer
CWindow* CApplication::s_Window = nullptr;

CApplication::CApplication()
{
	s_Window = new CWindow;
}

CApplication::~CApplication()
{
	delete s_Window;
}

// Start the application
int CApplication::Start()
{
	// Create window and verify if was succeed
	if (!s_Window->Create())
	{
		MessageBox(NULL, L"Failed to create window.", L"CApplication", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	// Runs the application
	return Update();
}

CWindow*& CApplication::GetWindow()
{
	return s_Window;
}

// Runs the application
int CApplication::Update()
{
	MSG Message{ NULL };

	// TODO: Game->Start();

	// === Main Loop (Gameloop)
	do
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		else
		{
			// TODO: Game->Update();
			// TODO: Renderer->Clear();

			// TODO: Game->Draw();
			// TODO: Renderer->Show();

			// """V-Sync"""
			Sleep(16);
		}
	} while (Message.message != WM_QUIT);

	// TODO: Game->End();

	return static_cast<int>(Message.wParam);
}