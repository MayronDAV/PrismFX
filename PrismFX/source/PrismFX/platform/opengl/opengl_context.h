#pragma once

#include "PrismFX/renderer/graphics_context.h"



namespace PFX
{
	class OpenGLContext : public GraphicsContext
	{
		public:
			OpenGLContext(GLFWwindow* p_window_handle);
			~OpenGLContext() override = default;

			void Init() override;

			void SwapBuffer() override;

			void SetVsync(bool p_enable) override;

		private:
			GLFWwindow* m_WindowHandle = nullptr;
	};


} //  PFX
