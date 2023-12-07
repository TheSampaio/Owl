#include "Engine.h"
#include "Header/Graphics.h"

#include "../Core/Header/Window.h"
#include "../Event/Header/Debug.h"

owl::Graphics::Graphics()
{
	m_VSyncMode = EVerticalSynchronizationMode::Full;
	m_ContextVersion = { 4, 0 };
}

bool owl::Graphics::Initialize()
{
	if (!Window::GetInstance().m_Id)
		return false;

	else if (!glewInit())
	{
		Debug::Log(Error, "Failed to initialize GLEW.");
		return false;
	}

	glfwMakeContextCurrent(Window::GetInstance().m_Id);
	glViewport(0, 0, Window::GetSize()[0], Window::GetSize()[1]);

	Debug::Log(Information, "Graphics Card: ", false);
	Debug::Log(Information, reinterpret_cast<const char*>(glGetString(GL_RENDERER)), true, false);
	Debug::Log(Information, "Graphics API: ", false);
	Debug::Log(Information, reinterpret_cast<const char*>(glGetString(GL_VERSION)), true, false);
	Debug::Log(Information, "===", true, false);

	return true;
}

void owl::Graphics::ClearBuffers()
{
	glClearColor(Window::GetBackgroundColour()[0] / 255.0f,
		Window::GetBackgroundColour()[1] / 255.0f,
		Window::GetBackgroundColour()[2] / 255.0f,
		1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
}

void owl::Graphics::SwapBuffers()
{
	glfwSwapInterval(m_VSyncMode);
	glfwSwapBuffers(Window::GetInstance().m_Id);
}
