#pragma once
#include "PrismFX/core/base.h"



namespace PFX
{
	class PFX_API Application
	{
		public:
			Application();
			virtual ~Application();

			void Run();
	};

	// Must be defined by the client
	Application* CreateApplication();

} // PFX
