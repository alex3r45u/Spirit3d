#include "sppch.h"
#include "PropertiesPanel.h"
#include <imgui/imgui.h>
#include "Spirit/Scene/Components.h"
#include <filesystem>

template<typename T>
static void DrawComponent(Spirit::Entity& entity, const std::string& name, std::function<void(T& component)> function) {

	const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

	if (entity.HasComponent<T>()) {
		auto& component = entity.GetComponent<T>();
		bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
		if (open) {
			function(component);
			ImGui::TreePop();
		}
	}
}


void Spirit::PropertiesPanel::ImGuiRender()
{
	ImGui::Begin("Properties");
	if (m_SceneHierarchy->m_IsSelected) {
		DrawComponents(m_SceneHierarchy->m_SelectedEntity);
	}
	ImGui::End();
}

void Spirit::PropertiesPanel::SetSceneHierarchy(SceneHierarchyPanel* hierarchy)
{
	m_SceneHierarchy = hierarchy;
}

void Spirit::PropertiesPanel::DrawComponents(Entity& entity)
{
	if (entity.HasComponent<TagComponent>()) {
		auto& tag = entity.GetComponent<TagComponent>();

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy(buffer, tag.Tag.c_str());

		if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
			tag.Tag = std::string(buffer);
		}
	}

	DrawComponent<TransformComponent>(entity, "Transform", [](auto& component) {
		ImGui::DragFloat3("Position", glm::value_ptr(component.Position));
		ImGui::DragFloat3("Rotation", glm::value_ptr(component.Rotation));
		ImGui::DragFloat3("Scale", glm::value_ptr(component.Scale));
		});

	DrawComponent<PerspectiveCameraComponent>(entity, "Perspective Camera", [](auto& component) {
		float zoom = component.Camera.GetZoom();
		if (ImGui::DragFloat("Zoom", &zoom)) {
			component.Camera.SetZoom(zoom);
		}
		});

	DrawComponent<MeshRendererComponent>(entity, "Mesh", [](auto& component) {
		if (ImGui::Button(component.FileName.c_str())) {

		}
		if (ImGui::BeginDragDropTarget()) {
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE_EXPLORER")) {
				const wchar_t* path = (const wchar_t*)payload->Data;
				std::filesystem::path p(path);
				component.Mesh = AssetLibrary::s_MeshLibrary.Get(p.string());
				component.FileName = p.filename().string();
				ImGui::EndDragDropTarget();
			}

		}
		});
}



