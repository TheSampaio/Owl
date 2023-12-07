#include "Engine.h"
#include "Header/Window.h"

#include "../Event/Header/Debug.h"
#include "../Render/Header/Graphics.h"

owl::Window::Window()
	: m_Id(nullptr)
{
	if (!glfwInit())
		Debug::Log(Error, "Failed to initialize GLFW.");

	m_Title = "Owl Engine | Window";
	m_Size = { 800, 600 };
	m_Screen = { 800, 600 };
	m_Position = { 0, 0 };
	m_BackgroundColour = { 0, 0, 0 };
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

	m_Id = glfwCreateWindow(m_Size[0], m_Size[1], m_Title.c_str(), nullptr, nullptr);

	if (m_Id)
	{

	}

	return (!m_Id) ? false : true;
}

bool owl::Window::IClose()
{
	return glfwWindowShouldClose(m_Id);
}
