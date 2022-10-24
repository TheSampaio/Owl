#include "PCH.h"
#include "Game.h"
#include "Application.h"

CWindow* GGame::s_Window = nullptr;

GGame::GGame()
{
}

GGame::~GGame()
{
}

void GGame::OnPause()
{
	Sleep(10);
}
