#pragma once

#include "PrismFX/core/definitions.h"



namespace PFX
{
	class Engine
	{
		public:
			static void SetAPI(RenderAPI p_api) { s_API = p_api; }
			static void SetWinAPI(WindowAPI p_api) { s_WinAPI = p_api; }

			static RenderAPI GetAPI() { return s_API; }
			static WindowAPI GetWinAPI() { return s_WinAPI; }

		private:
			static RenderAPI s_API;
			static WindowAPI s_WinAPI;
	};


} // PFX
