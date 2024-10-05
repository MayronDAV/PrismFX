#include "PrismFX/pfx_pch.h"
#include "input.h"

#include "PrismFX/core/engine.h"

#include "PrismFX/platform/glfw/glfw_input.h"



namespace PFX
{
	Input* Input::s_Instance = nullptr;

	void Input::Init(void* p_window_handle)
	{
		if (s_Instance)
			delete s_Instance;

		switch (Engine::GetWinAPI())
		{
			case WindowAPI::GLFW:
				s_Instance = new GLFWInput(p_window_handle);
				break;
			default:
				PFX_CORE_ERROR("Unknown window api!");
				break;
		}
	}

	bool Input::IsKeyPressed(int p_keycode)
	{
		PFX_CORE_ASSERT(s_Instance, "Did you call Init()?")
		return s_Instance->IsKeyPressed_impl(p_keycode); 
	}

	bool Input::IsMouseButtonPressed(int p_button)
	{
		PFX_CORE_ASSERT(s_Instance, "Did you call Init()?")
		return s_Instance->IsMouseButtonPressed_impl(p_button);
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		PFX_CORE_ASSERT(s_Instance, "Did you call Init()?")
		return s_Instance->GetMousePosition_impl();
	}

	float Input::GetMouseX()
	{
		PFX_CORE_ASSERT(s_Instance, "Did you call Init()?")
		auto [x, y] = s_Instance->GetMousePosition_impl();
		return x;
	}

	float Input::GetMouseY()
	{
		PFX_CORE_ASSERT(s_Instance, "Did you call Init()?")
		auto [x, y] = s_Instance->GetMousePosition_impl();
		return y;
	}


} // PFX
