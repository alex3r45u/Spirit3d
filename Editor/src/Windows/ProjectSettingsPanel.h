#pragma once
#include "Panel.h"
#include <filesystem>
#include "Spirit/Project/Project.h"

namespace Spirit {
	class ProjectSettingsPanel : public Panel {
	public:
		ProjectSettingsPanel() = default;
		ProjectSettingsPanel(const std::shared_ptr<Scene>& scene, const std::shared_ptr<Spirit::Project>& project);

		virtual void ImGuiRender() override;
		void SetProject(const std::shared_ptr<Spirit::Project>& project);

	private:
		std::shared_ptr<Spirit::Project> m_Project;
	};
}