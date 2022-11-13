#include "PCH.h"
#include "Application.h"

// Initialize window's static attributes
Input*	  Application::s_Input = nullptr;
Game*     Application::s_Game = nullptr;
Graphics* Application::s_Graphics = nullptr;
Renderer* Application::s_Renderer = nullptr;
Window*   Application::s_Window = nullptr;

Timer Application::s_Timer;
float  Application::s_DeltaTime = 0.0f;
bool   Application::s_bIsPaused = false;

// Dynamic alocates memory
Application::Application()
{
	s_Graphics = new Graphics;
	s_Renderer = new Renderer;
	s_Input = new Input;
	s_Window = new Window(s_Input);
}

// Deletes alocated memory
Application::~Application()
{
	delete s_Game;
	delete s_Graphics;
	delete s_Renderer;
	delete s_Input;
	delete s_Window;
}

// Start the application
int Application::Start(Game* World)
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

	if (!s_Renderer->Initialize(s_Window, s_Graphics))
	{
		MessageBox(NULL, L"Failed to initilize renderer.", L"Owl Engine", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	// Runs the application
	timeBeginPeriod(1);
	int State = Run();
	timeBeginPeriod(1);

	// Returns current engine's state
	return State;
}

void Application::Pause()
{
	s_bIsPaused = true;
	s_Timer.Stop();
}

void Application::Resume()
{
	s_bIsPaused = false;
	s_Timer.Start();
}

// Runs the application
int Application::Run()
{
	bool bPauseControl = true;
	MSG Message{ NULL };

	s_Timer.Start();
	s_Game->Start();

	// === Main Loop (Gameloop)
	do
	{
		// Process window's events
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		else
		{
			// Window's pause contrller
			if (bPauseControl)
			{
				if (s_Input->GetKeyTaped(VK_PAUSE))
				{
					s_bIsPaused = !s_bIsPaused;
					bPauseControl = !bPauseControl;
					(s_bIsPaused) ? s_Timer.Stop() : s_Timer.Start();
				}
			}

			else
			{
				bPauseControl = true;
			}

			if (!s_bIsPaused)
			{				
				// Updates the game and clear back buffer
				s_Game->Update(GetDeltaTime());
				s_Graphics->ClearBackBuffer();

				// Draw on screen and swap screen's buffers
				s_Game->Draw();
				s_Renderer->Render();
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

float& Application::GetDeltaTime()
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
