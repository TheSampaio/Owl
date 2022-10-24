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

void GGame::SetWindow(CWindow*& Window)
{
	s_Window = Window;
}

CWindow*& GGame::GetWindow()
{
	return s_Window;
}
