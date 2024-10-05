#include "PrismFX/pfx_pch.h"
#include "glfw_input.h"



namespace PFX
{
	GLFWInput::GLFWInput(void* p_window_handle)
		: m_WindowHandle((GLFWwindow*)p_window_handle)
	{
		PFX_CORE_ASSERT(m_WindowHandle, "Window Handle is null, did you call Init() correctly?");
	}

	bool GLFWInput::IsKeyPressed_impl(int p_keycode)
	{
		auto state = glfwGetKey(m_WindowHandle, p_keycode);
		return state == GLFW_PRESS;
	}

	bool GLFWInput::IsMouseButtonPressed_impl(int p_button)
	{
		auto state = glfwGetMouseButton(m_WindowHandle, p_button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> GLFWInput::GetMousePosition_impl()
	{
		double xpos, ypos;
		glfwGetCursorPos(m_WindowHandle, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

} // PFX
