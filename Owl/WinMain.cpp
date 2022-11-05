#include "PCH.h"
#include "Application.h"

#include "Game.h"
using namespace OwlTypes;

// Main game's class
class GMainGame : public GGame
{
public:
	void Start();
	void Update(Float& DeltaTime);
	void Draw();
	void Finish();

private:
	Bool Button = false;
};

// Main game's start method
void GMainGame::Start()
{
	MessageBox(GetWindow()->GetId(), L"Started!", L"Main Game", MB_OK | MB_ICONINFORMATION);
}

// Main game's update method
void GMainGame::Update(Float& DeltaTime)
{
	if (GetWindow()->GetKeyPressed(VK_ESCAPE)) { Button = true; }

	if (Button)
	{
		if (GetWindow()->GetKeyReleased(VK_ESCAPE))
		{
			Button = false;
			GetWindow()->Close();
		}
	}
}

// Main game's draw method
void GMainGame::Draw()
{
}

// Main game's finish method
void GMainGame::Finish()
{
	MessageBox(GetWindow()->GetId(), L"Finished!", L"Main Game", MB_OK | MB_ICONINFORMATION);
}

/* ========== ENTRY POINT ========== */
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ INT nCmdShow)
{
	CApplication Application;

	// Setup window
	Application.GetWindow()->SetSize(1024, 720);
	Application.GetWindow()->SetTitle("Super Game");
	Application.GetWindow()->SetBackgroundColor(255, 253, 186);
	Application.GetWindow()->SetDisplayMode(CWindow::EDisplayMode::WINDOWED);

	// Setup Graphics
	Application.GetGraphics()->SetVerticalSynchronization(true);

	// Starts the engine
	return Application.Start(new GMainGame);
}
