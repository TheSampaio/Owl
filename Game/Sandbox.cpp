#include "Sandbox.h"

using namespace owl;

Sandbox::Sandbox()
{
	Window::SetTitle("Sandbox");
	Window::SetSize(1360, 768);
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
