#include "sppch.h"
#include "ProjectSettingsPanel.h"
#include <imgui/imgui.h>


Spirit::ProjectSettingsPanel::ProjectSettingsPanel(const std::shared_ptr<Scene>& scene, const std::shared_ptr<Spirit::Project>& project)
	: m_Project(project)
{
}

void Spirit::ProjectSettingsPanel::ImGuiRender()
{
	ImGui::Begin("Project Settings");

	
	ImGui::End();
}

void Spirit::ProjectSettingsPanel::SetProject(const std::shared_ptr<Spirit::Project>& project)
{
}

