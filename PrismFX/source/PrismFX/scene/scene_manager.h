#pragma once

#include "PrismFX/core/base.h"

#include "scene.h"

#include "PrismFX/events/event.h"



namespace PFX
{
	class PFX_API Application;

	enum class LoadMode
	{
		Singular = 0, Additive
	};

	class PFX_API SceneManager
	{
		public:
			static void LoadScene(Scene* p_scene, LoadMode p_mode = LoadMode::Singular);

			static void ClearSceneStack();

		private:
			static void Init();
			static void Shutdown() noexcept;

			static void OnUpdate();

			static void OnEvent(Event& p_event);

			friend class Application;

	};

} // PFX
