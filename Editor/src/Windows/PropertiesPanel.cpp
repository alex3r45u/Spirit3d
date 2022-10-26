#include "sppch.h"
#include "PropertiesPanel.h"
#include <imgui/imgui.h>
#include "Spirit/Scene/Components.h"
#include <filesystem>
#include "Spirit/ImGui/DragDropSystem.h"
#include <filesystem>
#include <typeinfo>
//#include "Spirit/Scene/SceneManager.h"
#include "Spirit/Scene/Scripting/ScriptClass.h"
#include "Spirit/Scene/Scripting/ScriptField.h"
#include "Spirit/Scene/Scripting/ScriptingECS.h"
#include "Spirit/Scene/Scripting/ScriptController.h"
#include "Spirit/Application.h"

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

	DrawComponent<CameraComponent>(entity, "Camera", [](auto& component) {
		ImGui::Checkbox("Is Main", &component.IsMain);
		switch (component.Type) {
		case CameraType::Perspective: {
			float zoom = std::static_pointer_cast<Render::PerspectiveCamera>(component.Camera)->GetZoom();
			ImGui::DragFloat("Zoom", &zoom);
			std::static_pointer_cast<Render::PerspectiveCamera>(component.Camera)->SetZoom(zoom);
			break;
		}
			
		case CameraType::Orthographic:
			break;
		}
		});

	DrawComponent<MeshRendererComponent>(entity, "Mesh", [](auto& component) {
		ImGui::Text(("Selected Mesh: " + component.Path.filename().string()).c_str());
		DragDropSystem::SetTarget<const char*>("MESH", [&](const char* c) {
			component.Path = c;
			});
		});
	
	
	DrawComponent<MaterialComponent>(entity, "Material", [](auto& component) {
		ImGui::ColorEdit3("Albedo", glm::value_ptr(component.Material->Albedo));
		ImGui::ColorEdit3("Normal", glm::value_ptr(component.Material->Normal));
		ImGui::SliderFloat("Roughness", &component.Material->Roughness, 0.0f, 1.0f);
		ImGui::SliderFloat("Metallic", &component.Material->Metallic, 0.0f, 1.0f);
		ImGui::SliderFloat("Ambient Occlusion", &component.Material->AO, 0.0f, 1.0f);
	
		});
	
	DrawComponent<DirectionalLightComponent>(entity, "Directional Light", [](auto& component) {
		ImGui::ColorEdit3("Color", glm::value_ptr(component.DirectionalLight->Color));
		ImGui::DragFloat("Intensity", &component.DirectionalLight->Intensity);
		});
	DrawComponent<PointLightComponent>(entity, "Point Light", [](auto& component) {
		ImGui::ColorEdit3("Color", glm::value_ptr(component.PointLight->Color));
		ImGui::DragFloat("Intensity", &component.PointLight->Intensity);
		ImGui::DragFloat("Radius", &component.PointLight->Radius);
		});
	DrawComponent<SpotLightComponent>(entity, "Spot Light", [](auto& component) {

		});

	PROJECT->GetActiveScene()->GetScriptingECS().DrawComponents(entity, [&](std::shared_ptr<Scripting::ScriptObject> component) {

		if (!component->GetTypeName().find("SpiritScript.")) {
			return;
		}
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

		bool open = ImGui::TreeNodeEx((void*)component->GetObjectPointer(), treeNodeFlags, component->GetTypeName().c_str());

		bool deleted = false;
		if (ImGui::IsItemClicked(1)) {
			ImGui::OpenPopup(component->GetTypeName().c_str());
		}
		if (ImGui::BeginPopup(component->GetTypeName().c_str())) {
			if (ImGui::Selectable("Delete")) {
				//todo
				deleted = true;
			}
			ImGui::EndPopup();
		}
		if (deleted) {
			PROJECT->GetActiveScene()->GetScriptingECS().RemoveComponent(entity, component->GetTypeName());
		}
		if (open) {
			if (!deleted) {
				Spirit::Scripting::ScriptClass& _class = component->GetClass();
				for (auto v : _class.GetFieldNames()) {
					Scripting::ScriptField& field = component->GetField(v);
					switch (field.GetType()) {
					case Scripting::FieldType::Bool: {
						bool b = field.GetValue<bool>();
						ImGui::Checkbox(v.c_str(), &b);
						field.SetValue(b);
					}
												   break;
					case Scripting::FieldType::Float: {
						float f = field.GetValue<float>();
						ImGui::DragFloat(v.c_str(), &f);
						field.SetValue(f);
					}
													break;
					case Scripting::FieldType::Int: {
						int i = field.GetValue<int>();
						ImGui::DragInt(v.c_str(), &i);
						field.SetValue(i);
					}
												  break;
					case Scripting::FieldType::String: {

					}
													 break;
					case Scripting::FieldType::UnsignedInt: {
						int ui = field.GetValue<int>();
						ImGui::DragInt(v.c_str(), &ui);
						field.SetValue(ui);
					}
														  break;
					case Scripting::FieldType::Vec2: {
						glm::vec2 vec2 = field.GetValue<glm::vec2>();
						ImGui::DragFloat2(v.c_str(), glm::value_ptr(vec2));
						field.SetValue(vec2);
					}
												   break;
					case Scripting::FieldType::Vec3: {
						glm::vec2 vec3 = field.GetValue<glm::vec3>();
						ImGui::DragFloat3(v.c_str(), glm::value_ptr(vec3));
						field.SetValue(vec3);
					}
												   break;
					case Scripting::FieldType::Vec4: {
						glm::vec4 vec4 = field.GetValue<glm::vec4>();
						ImGui::DragFloat4(v.c_str(), glm::value_ptr(vec4));
						field.SetValue(vec4);
					}
												   break;
					default:
						ImGui::Text(v.c_str(), ": ");
						DragDropSystem::SetTarget<int>("COMPONENT_DRAG_DROP", [&](int i) {
							if (PROJECT->GetActiveScene()->GetScriptingECS().HasComponent(i, component->GetTypeName())) {
								field.SetValue(PROJECT->GetActiveScene()->GetScriptingECS().GetComponent(i, component->GetTypeName()));
								return;
							}

							//TODO c++ components
							
							});
						break;
					}
				}
			}




			ImGui::TreePop();
		}



		
		});
	

	//for (auto i : entity.GetAllScripts()) {

	//}

	if (ImGui::Button("Add Component")) {
		ImGui::OpenPopup("COMPONENT_VIEWER");
	}
	Spirit::DragDropSystem::SetTarget<const char*>("COMPONENT", [&](const char* c) {
		PROJECT->GetActiveScene()->GetScriptingECS().AddComponent(entity, std::make_shared<Scripting::ScriptObject>(Scripting::ScriptController::GetDomain().GetClass(c).CreateInstance()));
		});
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
					entity.AddComponent<CameraComponent>();
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



