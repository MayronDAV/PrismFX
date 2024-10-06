#include "PrismFX/pfx_pch.h"
#include "scene_manager.h"
#include "scene_stack.h"

#include "PrismFX/core/application.h"



namespace PFX
{
	struct Data
	{
		Scene* SceneObj = nullptr;
		SceneStack Stack;
		LoadMode Mode = LoadMode::Singular;
	};
	static Data* s_Data = nullptr;


	void SceneManager::Init()
	{
		s_Data = new Data();
	}

	void SceneManager::Shutdown() noexcept
	{
		if (s_Data->SceneObj)
		{
			s_Data->SceneObj->OnDetach();
			delete s_Data->SceneObj;
		}

		s_Data->Stack.Destroy();

		delete s_Data;
	}

	void SceneManager::LoadScene(Scene* p_scene, LoadMode p_mode)
	{
		s_Data->Mode = p_mode;

		if (s_Data->SceneObj) 
		{
			s_Data->SceneObj->OnDetach();
			delete s_Data->SceneObj;
			s_Data->SceneObj = nullptr;
		}

		if (p_mode == LoadMode::Additive)
		{
			s_Data->Stack.PushScene(p_scene);
			p_scene->OnAttach();
			return;
		}

		s_Data->SceneObj = p_scene;
		s_Data->SceneObj->OnAttach();
	}

	void SceneManager::OnUpdate()
	{
		if (s_Data->Mode == LoadMode::Singular)
		{
			s_Data->SceneObj->OnUpdate();
		}
		else if (s_Data->Mode == LoadMode::Additive)
		{
			for (const auto& scene : s_Data->Stack)
			{
				scene->OnUpdate();
			}
		}
	}

	void SceneManager::OnEvent(Event& p_event)
	{
		if (s_Data->Mode == LoadMode::Singular)
		{
			s_Data->SceneObj->OnEvent(p_event);
		}
		else if (s_Data->Mode == LoadMode::Additive)
		{
			for (const auto& scene : s_Data->Stack)
			{
				scene->OnEvent(p_event);
			}
		}
	}

	void SceneManager::ClearSceneStack()
	{
		s_Data->Stack.Destroy();
	}

} // PFX