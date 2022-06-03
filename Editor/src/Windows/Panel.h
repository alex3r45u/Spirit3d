#pragma once
#include "Spirit/Scene/Scene.h"

namespace Spirit {
	class Panel {
	public:
		Panel() = default;
		Panel(const std::shared_ptr<Scene>& scene) { SetScene(scene); }
		void SetScene(const std::shared_ptr<Scene>& scene) { m_Scene = scene; }
		virtual void ImGuiRender() = 0;
	protected:
		std::shared_ptr<Scene> m_Scene;
	};
}