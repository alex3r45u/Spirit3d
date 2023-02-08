#pragma once
#include <memory>
#include "Panel.h"
#include "Spirit/Scene/Entity.h"

namespace Spirit {
	class SceneHierarchyPanel : public Panel {
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const std::shared_ptr<Scene>& scene) : Panel(scene) {}
		virtual void ImGuiRender() override;
		void Deselect();
	private:
		void DrawNode(Entity& entity);
	private:
		Entity m_SelectedEntity;
		bool m_IsSelected = false;
		friend class PropertiesPanel;
	};
}