#include "Sandbox.h"

using namespace owl;

Sandbox::Sandbox()
{
	Window::SetSize(800, 600);
	Window::SetTitle("Sandbox");
	Window::SetDisplayMode(Windowed);
	Window::SetInitializeMaximized(false);
	Window::SetBackgroundColour(80, 0, 160);

	Graphics::SetContextVersion(4, 0);
	Graphics::SetVerticalSynchronization(Disabled);
}

void Sandbox::OnStart()
{
	Debug::Log(Information, "Game initialized.");
}

void Sandbox::OnUpdate()
{
}

void Sandbox::OnDraw()
{
}

void Sandbox::OnFinalize()
{
	Debug::Log(Information, "Game finalized.");
}

// === ENTRY POINT ===

int main()
{
	Application::Run(new Sandbox());
}
