#include "Engine.h"
#include "Header/Window.h"

#include "../Event/Header/Debug.h"
#include "../Render/Header/Graphics.h"

owl::Window::Window()
	: m_Id(nullptr), m_Monitor(nullptr)
{
	// Initialize GLFW
	if (!glfwInit())
		Debug::Log(Error, "Failed to initialize GLFW.");

	// Initialize window's attributes
	m_Monitor = glfwGetPrimaryMonitor();
	m_Screen = { static_cast<ushort>(glfwGetVideoMode(m_Monitor)->width), static_cast<ushort>(glfwGetVideoMode(m_Monitor)->height) };
	m_Size = { m_Screen[0], m_Screen[1] };
	m_Position = { 0, 0 };
	m_BackgroundColour = { 0, 0, 0 };
	m_DisplayMode = EWindowDisplayMode::Bordless;
	m_Title = "Owl Engine | Window";
	m_bMaximized = true;
}

owl::Window::~Window()
{
	glfwDestroyWindow(m_Id);
	glfwTerminate();
}

bool owl::Window::Create()
{
	// Set-up OpenGL's version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Graphics::GetContextVersion()[0]);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Graphics::GetContextVersion()[1]);

	// Set-up OpenGL's compatibility mode
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

	if (m_DisplayMode != Windowed)
	{
		m_Position = { 0, 0 };

		// Create a bordless window
		if (m_DisplayMode == EWindowDisplayMode::Bordless)
		{
			glfwWindowHint(GLFW_DECORATED, false);

			m_Size = { m_Screen[0], m_Screen[1] };
			m_Id = glfwCreateWindow(m_Size[0], m_Size[1], m_Title.c_str(), nullptr, nullptr);
		}

		// Create a fullscreen window
		else
			m_Id = glfwCreateWindow(m_Size[0], m_Size[1], m_Title.c_str(), m_Monitor, nullptr);
	}

	// Create a windowed window
	else
	{
		m_Id = glfwCreateWindow(m_Size[0], m_Size[1], m_Title.c_str(), nullptr, nullptr);

		if (m_Id)
		{
			m_Position = { static_cast<ushort>(m_Screen[0] / 2 - m_Size[0] / 2), static_cast<ushort>(m_Screen[1] / 2 - m_Size[1] / 2) };
			glfwSetWindowPos(m_Id, m_Position[0], m_Position[1]);

			if (m_bMaximized)
				glfwMaximizeWindow(m_Id);
		}
	}

	return (!m_Id) ? false : true;
}

bool owl::Window::IClose()
{
	return glfwWindowShouldClose(m_Id);
}
