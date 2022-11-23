#pragma once

// Sandbox's includes
#include "Game.h"
#include "Sprite.h"
#include "Image.h"

using namespace OwlTypes;

// Sandbox's class
class Sandbox : public Game
{
public:
	Sandbox();

	void Start();
	void Update(Float& DeltaTime);
	void Draw();
	void Finish();

private:
	Image* HeaderSouce;
	Sprite* Header01;
	Sprite* Header02;

	Sprite* Background;
	Sprite* Shank;

	Float PositionX;
	UInt Speed;
};
