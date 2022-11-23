#include "PCH.h"
#include "Application.h"

// Game's inlcudes
#include "Assets.h"
#include "Sandbox.h"

/* ========== ENTRY POINT ========== */
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ INT nCmdShow)
{
	Application Engine;

	// Setup window
	Engine.GetWindow()->SetSize(800, 600);
	Engine.GetWindow()->SetTitle("Shank Demo");
	Engine.GetWindow()->SetBackgroundColor(0, 0, 0);
	Engine.GetWindow()->SetDisplayMode(Window::EDisplayMode::IE_Windowed);

	// Setup window's icon and cursor
	Engine.GetWindow()->SetIcon(IDI_ICON);
	Engine.GetWindow()->SetCursor(IDC_CURSOR);

	// Setup Graphics
	Engine.GetGraphics()->SetVerticalSynchronization(true);
		
	// Starts the engine
	return Engine.Start(new Sandbox);
}
