#include "PCH.h"
#include "Game.h"
#include "Application.h"

Input* Game::s_Input = nullptr;
Window* Game::s_Window = nullptr;

Game::Game()
{
}

Game::~Game()
{
}

void Game::OnPause()
{
	Sleep(10);
}
