#include "PrismFX/core/application.h"
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
			std::cout << "Hello " << i++ << "\n";
		};
	}

} // PFX