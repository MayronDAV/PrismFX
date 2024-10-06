#pragma once 

#include "PrismFX/core/base.h"

// Lib
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


namespace PFX
{
	class GraphicsContext
	{
		public:
			virtual ~GraphicsContext() = default;

			virtual void Init() = 0;

			virtual void SwapBuffer() = 0;

			virtual void SetVsync(bool p_enable) = 0;

			static GraphicsContext* Create(GLFWwindow* p_window_handle);
	};

} // PFX