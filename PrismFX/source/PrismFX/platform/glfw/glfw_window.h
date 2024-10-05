#pragma once

#include "PrismFX/core/window.h"

// Lib
#include <glfw/glfw3.h>



namespace PFX
{
	class GLFWWindow : public Window
	{
		public:
			GLFWWindow(const WindowCreateInfo& p_info);
			virtual ~GLFWWindow();

			void OnUpdate() override;

			inline unsigned int GetWidth() const override { return m_Data.Width; }
			inline unsigned int GetHeight() const override { return m_Data.Height; }

			// Window attributes
			inline void SetEventCallback(const EventCallbackFn& p_callback) override { m_Data.EventCallback = p_callback; }
			void SetVsync(bool p_enabled) override;
			bool IsVsync() const override;

			inline virtual void* GetNativeWindow() const override { return m_Window; }

			virtual void SetCursorMode(CursorMode p_mode) override;

		private:
			void Init(const WindowCreateInfo& p_info);
			void Shutdown() noexcept;

		private:
			GLFWwindow* m_Window = nullptr;

			struct WindowData
			{
				std::string Title;
				unsigned int Width;
				unsigned int Height;
				bool Vsync;

				EventCallbackFn EventCallback;
			};

			WindowData m_Data;
	};

}