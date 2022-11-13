#include "PCH.h"
#include "Application.h"

// Game includes
#include "Game.h"
#include "Sprite.h"
#include "Image.h"

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
	Image* m_HeaderSouce = nullptr;
	Sprite* m_Header01 = nullptr;
	Sprite* m_Header02 = nullptr;

	Sprite* m_Background = nullptr;	
	Sprite* m_Shank = nullptr;

	Float m_PositionX = 50;
	UInt m_Speed = 120;
};

// Main game's start method
void MainGame::Start()
{
	m_HeaderSouce = new Image("Resources/Logo.png");
	m_Header01 = new Sprite(m_HeaderSouce);
	m_Header02 = new Sprite(m_HeaderSouce);

	m_Background = new Sprite("Resources/Background.jpg");
	m_Shank = new Sprite("Resources/Shank.png");
}

// Main game's update method
void MainGame::Update(Float& DeltaTime)
{
	if (GetInput()->GetKeyTaped(VK_ESCAPE)) { GetWindow()->Close(); }
		
	if (m_PositionX > GetWindow()->GetSize()[0])
	{
		m_PositionX = 0.0f - static_cast<Float>(m_Shank->GetSize()[0]);
	}

	else
	{
		m_PositionX += 1 * (m_Speed * DeltaTime);
	}
}

// Main game's draw method
void MainGame::Draw()
{
	m_Header01->Draw(40.0f, 60.0f, Layer::Upper);
	m_Header02->Draw(400.0f, 450.0f, Layer::Lower);

	m_Background->Draw(0.0f, 0.0f, Layer::Back);
	m_Shank->Draw(m_PositionX, 86.0f);
}

// Main game's finish method
void MainGame::Finish()
{
	delete m_HeaderSouce;
	delete m_Header01;
	delete m_Header02;

	delete m_Background;
	delete m_Shank;
}

/* ========== ENTRY POINT ========== */
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ INT nCmdShow)
{
	Application Application;

	// Setup window
	Application.GetWindow()->SetSize(800, 600);
	Application.GetWindow()->SetTitle("Shank Demo");
	Application.GetWindow()->SetBackgroundColor(0, 0, 0);
	Application.GetWindow()->SetDisplayMode(Window::EDisplayMode::WINDOWED);

	// Setup Graphics
	Application.GetGraphics()->SetVerticalSynchronization(false);
		
	// Starts the engine
	return Application.Start(new MainGame);
}
