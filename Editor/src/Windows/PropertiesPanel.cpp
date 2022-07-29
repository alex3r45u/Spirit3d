#include "sppch.h"
#include "PropertiesPanel.h"
#include <imgui/imgui.h>
#include "Spirit/Scene/Components.h"
#include <filesystem>
#include "Spirit/ImGui/DragDropSystem.h"
#include <filesystem>
#include <typeinfo>

template<typename T>
static void DrawComponent(Spirit::Entity& entity, const std::string& name, std::function<void(T& component)> function) {
	const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

	if (entity.HasComponent<T>()) {
		auto& component = entity.GetComponent<T>();
		bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
		
		bool deleted = false;
		if (ImGui::IsItemClicked(1)) {
			ImGui::OpenPopup((const char*)typeid(T).name());
		}
		if (ImGui::BeginPopup((const char*)typeid(T).name())) {
			if (ImGui::Selectable("Delete")) {
				entity.RemoveComponent<T>();
				deleted = true;
			}
			ImGui::EndPopup();
		}
		if (open) {
			if(!deleted)
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
		if (ImGui::Button(component.Mesh->GetPath().filename().string().c_str())) {
	
		}
		DragDropSystem::SetTarget("FILE_EXPLORER", [&](auto c) {
			component.Mesh = AssetLibrary::s_MeshLibrary.Get(c);
			});
		});
	
	
	DrawComponent<MaterialComponent>(entity, "Material", [](auto& component) {
		ImGui::ColorEdit3("Ambient", glm::value_ptr(component.Material->Ambient));
		ImGui::Checkbox("Has Texture##1", &component.Material->HasAmbientTexture);
		if (component.Material->HasAmbientTexture) {
			if (component.Material->GetAmbientPath() == "") {
				ImGui::Text("Drag Texture");
			}
			else {
				ImGui::Text(component.Material->GetAmbientPath().filename().string().c_str());
			}
			DragDropSystem::SetTarget("FILE_EXPLORER", [&](auto c) {
				component.Material->SetAmbientPath(std::filesystem::path(c));
				});
	
		}
	
		ImGui::ColorEdit3("Deffuse", glm::value_ptr(component.Material->Deffuse));
		ImGui::Checkbox("Has Texture##2", &component.Material->HasDeffuseTexture);
		if (component.Material->HasDeffuseTexture) {
			if (component.Material->GetDeffusePath() == "") {
				ImGui::Text("Drag Texture");
			}
			else {
				ImGui::Text(component.Material->GetDeffusePath().filename().string().c_str());
			}
			DragDropSystem::SetTarget("FILE_EXPLORER", [=](auto c) {
				component.Material->SetDeffusePath(std::filesystem::path(c));
				});
	
		}
	
		ImGui::ColorEdit3("Specular", glm::value_ptr(component.Material->Specular));
		ImGui::Checkbox("Has Texture##3", &component.Material->HasSpecularTexture);
		if (component.Material->HasSpecularTexture) {
			if (component.Material->GetSpecularPath() == "") {
				ImGui::Text("Drag Texture");
			}
			else {
				ImGui::Text(component.Material->GetSpecularPath().filename().string().c_str());
			}
			DragDropSystem::SetTarget("FILE_EXPLORER", [=](auto c) {
				component.Material->SetSpecularPath(std::filesystem::path(c));
				});
	
		}
	
		ImGui::DragFloat("Shininess", &component.Material->Shininess);
	
	
		});
	
	DrawComponent<DirectionalLightComponent>(entity, "Directional Light", [](auto& component) {
		ImGui::ColorEdit3("Color", glm::value_ptr(component.DirectionalLight->color));
		});
	DrawComponent<PointLightComponent>(entity, "Point Light", [](auto& component) {
		ImGui::ColorEdit3("Color", glm::value_ptr(component.PointLight->color));
		ImGui::DragFloat("K0", &component.PointLight->k0);
		ImGui::DragFloat("K1", &component.PointLight->k1);
		ImGui::DragFloat("K2", &component.PointLight->k2);
		});
	DrawComponent<SpotLightComponent>(entity, "Spot Light", [](auto& component) {
		ImGui::ColorEdit3("Color", glm::value_ptr(component.SpotLight->color));
	
		ImGui::DragFloat("Cut Off", &component.SpotLight->cutOff);
		ImGui::DragFloat("Outer Cut Off", &component.SpotLight->outerCutOff);
	
		ImGui::DragFloat("K0", &component.SpotLight->k0);
		ImGui::DragFloat("K1", &component.SpotLight->k1);
		ImGui::DragFloat("K2", &component.SpotLight->k2);
		});
	

	//for (auto i : entity.GetAllScripts()) {

	//}

	if (ImGui::Button("Add Component")) {
		ImGui::OpenPopup("COMPONENT_VIEWER");
	}
	if (ImGui::BeginPopup("COMPONENT_VIEWER")) {
		ImGui::Text("Select Component");
		ImGui::Separator();
		if (ImGui::BeginMenu("Render")) {
			if (ImGui::MenuItem("Mesh")) {
				entity.AddComponent<MeshRendererComponent>();
			}
			if (ImGui::MenuItem("Cube")) {

			}
			if (ImGui::MenuItem("Sphere")) {

			}
			if (ImGui::MenuItem("Cylinder")) {

			}
			if (ImGui::MenuItem("Sprite")) {

			}
			if (ImGui::MenuItem("Material")) {
				entity.AddComponent<MaterialComponent>();
			}
			ImGui::EndMenu();
		}
			
			if (ImGui::BeginMenu("Cameras")) {
				if (ImGui::MenuItem("Perspective")) {
					entity.AddComponent<PerspectiveCameraComponent>();
				}
				if (ImGui::MenuItem("Orthographic")) {
					//TODO
				}
	
				ImGui::EndMenu();
	
			}
			if(ImGui::BeginMenu("Lights")) {
				if (ImGui::MenuItem("Directional")) {
					entity.AddComponent<DirectionalLightComponent>();
				}
				if (ImGui::MenuItem("Point")) {
					entity.AddComponent<PointLightComponent>();
				}
				if (ImGui::MenuItem("Spot")) {
					entity.AddComponent<SpotLightComponent>();
				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
	}
}



