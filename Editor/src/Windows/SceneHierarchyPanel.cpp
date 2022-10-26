#include "sppch.h"
#include "SceneHierarchyPanel.h"
#include "Spirit/Scene/Components.h"
#include <imgui/imgui.h>
#include "Spirit/ImGui/DragDropSystem.h"


void Spirit::SceneHierarchyPanel::ImGuiRender()
{
	ImGui::Begin("Hierarchie");
	if (ImGui::Button("+")) {
		ImGui::OpenPopup("ADD_POPUP");
	}

	if (ImGui::BeginPopup("ADD_POPUP"))
	{
		if (ImGui::BeginMenu("Meshes")) {
			if (ImGui::MenuItem("Cube")) {
				auto g = m_Scene->CreateEntity("Cube");
				//Add Cube REnder
			}
			
			if (ImGui::MenuItem("Sphere")) {
				auto g = m_Scene->CreateEntity("Sphere");
				//Add Cube REnder
			}
			if (ImGui::MenuItem("Cylinder")) {
				auto g = m_Scene->CreateEntity("Cylinder");
				//Add Cube REnder
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Cameras")) {
			if (ImGui::MenuItem("Perspective")) {
				auto g = m_Scene->CreateEntity("Camera");
				g.AddComponent<CameraComponent>(Spirit::CameraType::Perspective);
			}
			if (ImGui::MenuItem("Orthocraphic")) {
				auto g = m_Scene->CreateEntity("Camera");
				g.AddComponent<CameraComponent>(Spirit::CameraType::Orthographic);
				//add component
			}
			ImGui::EndMenu();
		}
		if (ImGui::Selectable("Empty")) {
			auto g = m_Scene->CreateEntity("Empty");
		}
		
		ImGui::EndPopup();
	}

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
	if (ImGui::IsItemClicked(1)) {
		ImGui::OpenPopup((const char*)&entity);
	}

	if (ImGui::BeginPopup((const char*)&entity))
	{
		if (ImGui::Selectable("Delete")) {
			m_IsSelected = false;
			m_Scene->RemoveEntity(entity);
		}		
		ImGui::EndPopup();
	}
	
	DragDropSystem::SetSource<int>("ENTITY", (uint32_t)entity);
	if (opened)
	{
		//ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		//bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
		//if (opened)
		//	ImGui::TreePop();
		ImGui::TreePop();
	}
}
