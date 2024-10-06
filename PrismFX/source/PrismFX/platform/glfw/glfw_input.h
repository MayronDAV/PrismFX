#pragma once

#include "PrismFX/core/input.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


namespace PFX
{
	class GLFWInput : public Input
	{
		public:
			GLFWInput(void* p_window_handle);
			~GLFWInput() = default;

		protected:
			bool IsKeyPressed_impl(int p_keycode) override;
			bool IsMouseButtonPressed_impl(int p_button) override;
			std::pair<float, float> GetMousePosition_impl() override;

		private:
			GLFWwindow* m_WindowHandle = nullptr;
	};
} // PFX
