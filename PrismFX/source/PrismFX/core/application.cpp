#include "PrismFX/pfx_pch.h"
#include "PrismFX/core/application.h"
#include "PrismFX/core/asserts.h"

#include "PrismFX/scene/scene_manager.h"


namespace PFX
{
	Application::Application()
	{
		SceneManager::Init();
	}

	Application::~Application()
	{
		SceneManager::Shutdown();
		delete m_Window;
	}

	void Application::Init()
	{
		PFX_CORE_ASSERT(m_Window, "Must be called SetWindow()!");
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	void Application::Run()
	{
		PFX_CORE_ASSERT(m_Window, "Must be called SetWindow()!");

		while(m_Running)
		{
			SceneManager::OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& p_event)
	{
		EventDispatcher dispatcher(p_event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		SceneManager::OnEvent(p_event);
	}

	bool Application::OnWindowClose(WindowCloseEvent& p_event)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& p_event)
	{
		if (p_event.GetWidth() == 0 || p_event.GetHeight() == 0)
		{
			m_Minimized = true;
			return true;
		}

		m_Minimized = false;
		return true;
	}

} // PFX