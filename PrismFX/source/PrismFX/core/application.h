#pragma once
#include "PrismFX/core/base.h"

#include "PrismFX/events/event.h"
#include "PrismFX/events/application_event.h"

#include "PrismFX/core/window.h"


namespace PFX
{
	class PFX_API Application
	{
		public:
			Application();
			virtual ~Application();

			void Init();

			void Run();

			void OnEvent(Event& p_event);

			void SetWindow(Window* p_window) { m_Window = p_window; }

		private:
			bool OnWindowClose(WindowCloseEvent& p_event);
			bool OnWindowResize(WindowResizeEvent& p_event);

		private:
			Window* m_Window = nullptr;
			bool m_Running = true;
			bool m_Minimized = true;
	};

	// Must be defined by the client
	Application* CreateApplication();

} // PFX
