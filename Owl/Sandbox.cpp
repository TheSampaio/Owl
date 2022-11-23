#include "PCH.h"
#include "Sandbox.h"

// Sandbox's constructor
Sandbox::Sandbox()
	: HeaderSouce{ nullptr }, Header01{ nullptr }, Header02{ nullptr }, Background{ nullptr }, Shank{ nullptr }
{
	PositionX = 0.0f;
	Speed = 150;
}

// Sandbox's start method
void Sandbox::Start()
{
	HeaderSouce = new Image("Resources/Shank/Logo.png");
	Header01 = new Sprite(HeaderSouce);
	Header02 = new Sprite(HeaderSouce);

	Background = new Sprite("Resources/Shank/Background.jpg");
	Shank = new Sprite("Resources/Shank/Shank.png");
}

// Sandbox's update method
void Sandbox::Update(Float& DeltaTime)
{
	if (GetInput()->GetKeyTaped(VK_ESCAPE)) { GetWindow()->Close(); }

	if (PositionX > GetWindow()->GetSize()[0])
	{
		PositionX = -static_cast<Float>(Shank->GetSize()[0]);
	}

	else
	{
		PositionX += 1 * (Speed * DeltaTime);
	}
}

// Sandbox's draw method
void Sandbox::Draw()
{
	Header01->Draw(40.0f, 60.0f, Layer::Upper);
	Header02->Draw(400.0f, 450.0f, Layer::Lower);

	Background->Draw(0.0f, 0.0f, Layer::Back);
	Shank->Draw(PositionX, 86.0f);
}

// Sandbox's finish method
void Sandbox::Finish()
{
	delete HeaderSouce;
	delete Header01;
	delete Header02;

	delete Background;
	delete Shank;
}