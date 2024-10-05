#pragma once

#include "PrismFX/core/base.h"
#include "PrismFX/scene/scene.h"

// std
#include <vector>



namespace PFX
{
	class PFX_API SceneStack
	{
		public:
			SceneStack();
			~SceneStack();

			void Destroy() noexcept;

			void PushScene(Scene* p_scene);
			void PopScene(Scene* p_scene);

			std::vector<Scene*>::iterator begin() { return m_Scenes.begin(); }
			std::vector<Scene*>::iterator end() { return m_Scenes.end(); }
			std::vector<Scene*>::reverse_iterator rbegin() { return m_Scenes.rbegin(); }
			std::vector<Scene*>::reverse_iterator rend() { return m_Scenes.rend(); }

			std::vector<Scene*>::const_iterator begin() const { return m_Scenes.begin(); }
			std::vector<Scene*>::const_iterator end()	const { return m_Scenes.end(); }
			std::vector<Scene*>::const_reverse_iterator rbegin() const { return m_Scenes.rbegin(); }
			std::vector<Scene*>::const_reverse_iterator rend() const { return m_Scenes.rend(); }

		private:
			std::vector<Scene*> m_Scenes;
			unsigned int m_SceneInsertIndex = 0;
	};

}