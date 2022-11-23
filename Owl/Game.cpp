#include "PCH.h"
#include "Game.h"
#include "Application.h"

Input*&  Game::s_Input  = Application::s_Input;
Window*& Game::s_Window = Application::s_Window;

void Game::OnPause()
{
	Sleep(10);
}
