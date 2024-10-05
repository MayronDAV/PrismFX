#pragma once

#include "PrismFX/core/base.h"
#include "PrismFX/events/key_event.h"


namespace PFX
{
	class PFX_API Input
	{
		public:
			virtual ~Input() { delete s_Instance; }

			static void Init(void* p_window_handle);

			// the key event is propagated to each scene with the same key check
			static bool IsKeyPressed(int p_keycode);
			// the mouse button event is propagated to each scene with the same button check
			static bool IsMouseButtonPressed(int p_button);

			static std::pair<float, float> GetMousePosition();
			static float GetMouseX();
			static float GetMouseY();

		protected:
			virtual bool IsKeyPressed_impl(int p_keycode) = 0;
			virtual bool IsMouseButtonPressed_impl(int p_button) = 0;
			virtual std::pair<float, float> GetMousePosition_impl() = 0;

		private:
			static Input* s_Instance;
	};
}