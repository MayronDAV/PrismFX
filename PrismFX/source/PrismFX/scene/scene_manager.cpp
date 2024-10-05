#include "PrismFX/pfx_pch.h"
#include "scene_manager.h"
#include "scene_stack.h"

#include "PrismFX/core/application.h"



namespace PFX
{
	struct Data
	{
		Scene* Scene = nullptr;
		SceneStack m_Stack;
		LoadMode Mode = LoadMode::Singular;
	};
	static Data* s_Data = nullptr;


	void SceneManager::Init()
	{
		s_Data = new Data();
	}

	void SceneManager::Shutdown() noexcept
	{
		if (s_Data->Scene)
		{
			s_Data->Scene->OnDetach();
			delete s_Data->Scene;
		}

		s_Data->m_Stack.Destroy();

		delete s_Data;
	}

	void SceneManager::LoadScene(Scene* p_scene, LoadMode p_mode)
	{
		s_Data->Mode = p_mode;

		if (s_Data->Scene) 
		{
			s_Data->Scene->OnDetach();
			delete s_Data->Scene;
			s_Data->Scene = nullptr;
		}

		if (p_mode == LoadMode::Additive)
		{
			s_Data->m_Stack.PushScene(p_scene);
			p_scene->OnAttach();
			return;
		}

		s_Data->Scene = p_scene;
		s_Data->Scene->OnAttach();
	}

	void SceneManager::OnUpdate()
	{
		if (s_Data->Mode == LoadMode::Singular)
		{
			s_Data->Scene->OnUpdate();
		}
		else if (s_Data->Mode == LoadMode::Additive)
		{
			for (const auto& scene : s_Data->m_Stack)
			{
				scene->OnUpdate();
			}
		}
	}

	void SceneManager::OnEvent(Event& p_event)
	{
		if (s_Data->Mode == LoadMode::Singular)
		{
			s_Data->Scene->OnEvent(p_event);
		}
		else if (s_Data->Mode == LoadMode::Additive)
		{
			for (const auto& scene : s_Data->m_Stack)
			{
				scene->OnEvent(p_event);
			}
		}
	}

	void SceneManager::ClearSceneStack()
	{
		s_Data->m_Stack.Destroy();
	}

} // PFX