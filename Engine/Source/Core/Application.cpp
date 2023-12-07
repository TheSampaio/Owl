#include "Engine.h"
#include "Header/Application.h"

#include "Header/Window.h"
#include "../Event/Header/Debug.h"
#include "../Event/Header/Input.h"
#include "../Logic/Header/Game.h"
#include "../Render/Header/Graphics.h"


owl::Application::Application()
	: m_Game(nullptr)
{
}

owl::Application::~Application()
{
	delete m_Game;
}

bool owl::Application::Initialize()
{
	if (!Window::GetInstance().Create())
	{
		Debug::Log(Error, "Failed to create window.");
		return false;
	}

	else if (!Graphics::GetInstance().Initialize())
	{
		Debug::Log(Error, "Failed to initialize graphics.");
		return false;
	}

	return true;
}

bool owl::Application::IRun(Game& game)
{
	m_Game = &game;

	if (!Initialize())
	{
		Debug::Log(Error, "Failed to initialize Owl engine.");
		return false;
	}

	// TODO: Timer.Update();
	m_Game->OnStart();

	// Main loop (Game loop)
	do
	{
		Input::GetInstance().PollEvents();

		m_Game->OnUpdate();

		Graphics::GetInstance().ClearBuffers();

		m_Game->OnDraw();

		// TODO: Renderer.Render();

		Graphics::GetInstance().SwapBuffers();

	} while (!Window::Close());

	m_Game->OnFinalize();

	return true;
}
