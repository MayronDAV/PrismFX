#include "PrismFX/pfx_pch.h"
#include "PrismFX/scene/scene_stack.h"


namespace PFX
{
	SceneStack::SceneStack()
	{
		
	}

	SceneStack::~SceneStack()
	{
		Destroy();
	}

	void SceneStack::Destroy() noexcept
	{
		for (Scene* Scene : m_Scenes)
		{
			Scene->OnDetach();
			delete Scene;
		}

		m_Scenes.clear();
	}

	void SceneStack::PushScene(Scene* p_scene)
	{
		m_Scenes.emplace(m_Scenes.begin() + m_SceneInsertIndex, p_scene);
		m_SceneInsertIndex++;
	}

	void SceneStack::PopScene(Scene* p_scene)
	{
		auto it = std::find(m_Scenes.begin(), m_Scenes.begin() + m_SceneInsertIndex, p_scene);
		if (it != m_Scenes.begin() + m_SceneInsertIndex)
		{
			p_scene->OnDetach();
			m_Scenes.erase(it);
			m_SceneInsertIndex--;
		}
	}

}
