#include "sppch.h"
#include "SceneHierarchyPanel.h"
#include "Spirit/Scene/Components.h"
#include <imgui/imgui.h>


void Spirit::SceneHierarchyPanel::ImGuiRender()
{
	ImGui::Begin("Hierarchie");
	m_Scene->m_Registry.each([&](auto entityID)
		{
			Entity entity{ entityID , m_Scene.get() };
			DrawNode(entity);
		});
	ImGui::End();
}

void Spirit::SceneHierarchyPanel::DrawNode(Entity& entity)
{
	auto& tag = entity.GetComponent<TagComponent>().Tag;

	ImGuiTreeNodeFlags flags = ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
	if (ImGui::IsItemClicked())
	{
		m_SelectedEntity = entity;
		m_IsSelected = true;
	}

	if (opened)
	{
		//ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		//bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
		//if (opened)
		//	ImGui::TreePop();
		ImGui::TreePop();
	}
}
