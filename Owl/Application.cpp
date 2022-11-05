#include "PCH.h"
#include "Application.h"

// Initialize window's static attributes
GGame*     CApplication::s_Game = nullptr;
RGraphics* CApplication::s_Graphics = nullptr;
CWindow*   CApplication::s_Window = nullptr;

ITimer CApplication::s_Timer;
float  CApplication::s_DeltaTime = 0.0f;
bool   CApplication::s_bIsPaused = false;

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

void CApplication::Pause()
{
	s_bIsPaused = true;
	s_Timer.Stop();
}

void CApplication::Resume()
{
	s_bIsPaused = false;
	s_Timer.Start();
}

// Runs the application
int CApplication::Run()
{
	bool bPauseControl = true;
	MSG Message{ NULL };

	s_Timer.Start();
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
			if (bPauseControl)
			{
				if (s_Window->GetKeyPressed(VK_PAUSE))
				{
					s_bIsPaused = !s_bIsPaused;
					bPauseControl = false;

					(s_bIsPaused) ? s_Timer.Stop() : s_Timer.Start();
				}
			}

			else
			{
				if (s_Window->GetKeyReleased(VK_PAUSE)) { bPauseControl = true; }
			}

			if (!s_bIsPaused)
			{				
				// Updates the game and clear back buffer
				s_Game->Update(GetDeltaTime());
				s_Graphics->ClearBackBuffer();

				// Draw on screen and swap screen's buffers
				s_Game->Draw();
				s_Graphics->SwapBuffers();
			}

			else
			{
				s_Game->OnPause();
			}
		}

	} while (Message.message != WM_QUIT);

	// Finishes the game
	s_Game->Finish();
	return static_cast<int>(Message.wParam);
}

float& CApplication::GetDeltaTime()
{
#ifdef _DEBUG
	static float s_TotalTime = 0.0f;
	static unsigned int s_FrameCount = 0;
#endif // _DEBUG

	s_DeltaTime = s_Timer.Reset();

#ifdef _DEBUG
	s_TotalTime += s_DeltaTime;
	s_FrameCount++;

	if (s_TotalTime >= 1.0f)
	{
		std::stringstream TitleStream;
		TitleStream << std::fixed;
		TitleStream.precision(1);
		TitleStream << s_Window->GetTitle().c_str() << " | " << "Direct3D 11" << " | " << "FPS: " << s_FrameCount << " | " << "MS: " << s_DeltaTime * 1000;

		std::string TitleString = TitleStream.str();
		SetWindowText(s_Window->GetId(), std::wstring(TitleString.begin(), TitleString.end()).c_str());

		s_FrameCount = 0;
		s_TotalTime -= 1.0f;
	}

#endif // _DEBUG

	return s_DeltaTime;
}
