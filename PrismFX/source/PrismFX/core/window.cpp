#include "PrismFX/pfx_pch.h"
#include "PrismFX/core/window.h"

#include "PrismFX/platform/glfw/glfw_window.h"
#include "PrismFX/core/engine.h"



namespace PFX
{
	Window* Window::Create(const WindowCreateInfo& p_info)
	{
		// For now it's just GLFW, maybe in the future directx and win32 window will be added
		switch (Engine::GetWinAPI())
		{
			case WindowAPI::GLFW:
				return new GLFWWindow(p_info); 
			default:
				PFX_CORE_ERROR("Unknown window api!");
				return nullptr;
		}
	}

} // PFX