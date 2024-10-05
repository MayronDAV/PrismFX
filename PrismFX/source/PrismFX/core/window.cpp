#include "PrismFX/pfx_pch.h"
#include "PrismFX/core/window.h"

#include "PrismFX/platform/glfw/glfw_window.h"

namespace PFX
{
	Window* Window::Create(const WindowCreateInfo& p_info)
	{
		// For now it's just GLFW, maybe in the future directx and win32 window will be added
		return new GLFWWindow(p_info); 
	}

} // PFX