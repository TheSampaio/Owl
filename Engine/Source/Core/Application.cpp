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
	// Create a window
	if (!Window::GetInstance().Create())
	{
		Debug::Log(Error, "Failed to create window.");
		return false;
	}

	// Initialize graphics
	else if (!Graphics::GetInstance().Initialize())
	{
		Debug::Log(Error, "Failed to initialize graphics.");
		return false;
	}

	return true;
}

bool owl::Application::IRun(Game& game)
{
	// Create the game
	m_Game = &game;

	// Initialize the engine's components
	if (!Initialize())
	{
		Debug::Log(Error, "Failed to initialize Owl engine.");
		return false;
	}

	// Start the game
	// TODO: Timer.Update();
	m_Game->OnStart();

	// Main loop (Game loop)
	do
	{
		// Process all window's events
		Input::GetInstance().PollEvents();

		// Update the game
		m_Game->OnUpdate();

		// Clear the window's buffers and draw on the screen
		Graphics::GetInstance().ClearBuffers();
		m_Game->OnDraw();
		// TODO: Renderer.Render();

		// Swap the window's buffers with an interval
		Graphics::GetInstance().SwapBuffers();

	} while (!Window::Close());

	// Finilize the game
	m_Game->OnFinalize();
	return true;
}
