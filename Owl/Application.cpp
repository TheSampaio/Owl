#include "PCH.h"
#include "Application.h"

// Initialize window's static pointer
GGame* CApplication::s_Game = nullptr;
RGraphics* CApplication::s_Graphics = nullptr;
CWindow* CApplication::s_Window = nullptr;

// Dynamic alocates memory
CApplication::CApplication()
{
	s_Graphics = new RGraphics;
	s_Window = new CWindow;
}

// Deletes alocated memory
CApplication::~CApplication()
{
	delete s_Graphics;
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

	// Initializes graphics and verify if was succeed
	if (!s_Graphics->Initialize(s_Window))
	{
		MessageBox(NULL, L"Failed to initilize graphic device.", L"Owl Engine", MB_OK | MB_ICONERROR);
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
			// Updates the game and clear back buffer
			s_Game->Update(1.0f);
			s_Graphics->ClearBackBuffer();

			// Draw on screen and swap screen's buffers
			s_Game->Draw();
			s_Graphics->SwapBuffers();

			// """V-Sync"""
			Sleep(16);
		}
	} while (Message.message != WM_QUIT);

	// Finishes the game
	s_Game->Finish();
	return static_cast<int>(Message.wParam);
}