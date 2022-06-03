#pragma once
#include "Spirit/Scene/Scene.h"
#include "Panel.h"
#include "SceneHierarchyPanel.h"

namespace Spirit {
	class PropertiesPanel : public Panel {
	public:
		PropertiesPanel() = default;
		PropertiesPanel(const std::shared_ptr<Scene>& scene, SceneHierarchyPanel* hierarchy) : Panel(scene), m_SceneHierarchy(hierarchy) {}
		virtual void ImGuiRender() override;
		void SetSceneHierarchy(SceneHierarchyPanel* hierarchy);
	private:
		void DrawComponents(Entity& entity);
	private:
		SceneHierarchyPanel* m_SceneHierarchy;
	};
}