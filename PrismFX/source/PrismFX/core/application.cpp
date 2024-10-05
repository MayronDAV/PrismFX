#include "PrismFX/core/application.h"
#include "PrismFX/core/log.h"

// std
#include <iostream>


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