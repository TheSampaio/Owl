#include "PCH.h"
#include "Application.h"

// Initialize window's static pointer
GGame* CApplication::s_Game = nullptr;
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
int CApplication::Start(GGame* World)
{
	s_Game = World;
	s_Game->SetWindow(s_Window);

	// Create window and verify if was succeed
	if (!s_Window->Create())
	{
		MessageBox(NULL, L"Failed to create window.", L"Owl Engine", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	// Runs the application
	timeBeginPeriod(1);
	int State = Run();
	timeBeginPeriod(1);

	// Returns current engine's state
	return State;
}

// Runs the application
int CApplication::Run()
{
	MSG Message{ NULL };

	s_Game->Start();

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
			s_Game->Update(1.0f);
			// TODO: Renderer->Clear();

			s_Game->Draw();
			// TODO: Renderer->Show();

			// """V-Sync"""
			Sleep(16);
		}
	} while (Message.message != WM_QUIT);

	s_Game->Finish();

	return static_cast<int>(Message.wParam);
}