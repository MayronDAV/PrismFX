#include "PrismFX/pfx_pch.h"
#include "PrismFX/core/application.h"


namespace PFX
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		int i = 0;
		while(true)
		{
			PFX_CORE_TRACE("Hello {}", i++)
		};
	}

} // PFX