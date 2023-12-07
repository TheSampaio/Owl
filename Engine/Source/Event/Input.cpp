#include "Engine.h"
#include "Header/Input.h"

#include "../Core/Header/Window.h"

void owl::Input::PollEvents()
{
	if (Window::GetInstance().m_Id)
		glfwPollEvents();
}
