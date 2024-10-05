#pragma once

#include "PrismFX/core/definitions.h"



namespace PFX
{
	class Engine
	{
		public:
			static void SetAPI(RenderAPI p_api) { s_API = p_api; }

			static RenderAPI GetAPI() { return s_API; }

		private:
			static RenderAPI s_API;
	};


} // PFX
