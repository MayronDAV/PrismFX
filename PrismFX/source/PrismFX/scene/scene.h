#pragma once

#include "PrismFX/core/base.h"
#include "PrismFX/events/event.h"



namespace PFX
{
	class PFX_API Scene
	{
		public:
			Scene(const std::string& p_tag = "Scene");
			virtual ~Scene();

			virtual void OnAttach() {}
			virtual void OnDetach() {}
			virtual void OnUpdate() {}
			virtual void OnEvent(Event& p_event) {}

			inline const std::string& GetTag() const { return m_Tag; }

		protected:
			std::string m_Tag;
	};
}