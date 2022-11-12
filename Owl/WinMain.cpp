#include "PCH.h"
#include "Application.h"

#include "Game.h"

using namespace OwlTypes;

// Main game's class
class MainGame : public Game
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
void MainGame::Start()
{
	MessageBox(GetWindow()->GetId(), L"Started!", L"Main Game", MB_OK | MB_ICONINFORMATION);
}

// Main game's update method
void MainGame::Update(Float& DeltaTime)
{
	if (GetInput()->GetKeyTaped(VK_ESCAPE)) { GetWindow()->Close(); }
	if (GetInput()->GetKeyTaped(VK_SPACE))  { MessageBox(GetWindow()->GetId(), L"Thank you!", L"Yes baby!", MB_ICONINFORMATION | MB_OK); }
}

// Main game's draw method
void MainGame::Draw()
{
}

// Main game's finish method
void MainGame::Finish()
{
	MessageBox(GetWindow()->GetId(), L"Finished!", L"Main Game", MB_OK | MB_ICONINFORMATION);
}

/* ========== ENTRY POINT ========== */
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ INT nCmdShow)
{
	Application Application;

	// Setup window
	Application.GetWindow()->SetSize(1280, 800);
	Application.GetWindow()->SetTitle("Super Game");
	Application.GetWindow()->SetBackgroundColor(255, 253, 186);
	Application.GetWindow()->SetDisplayMode(Window::EDisplayMode::WINDOWED);

	// Setup Graphics
	Application.GetGraphics()->SetVerticalSynchronization(true);

	// Starts the engine
	return Application.Start(new MainGame);
}
