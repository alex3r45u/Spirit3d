#include "sppch.h"
#include "SceneSerializer.h"
#include <functional>
#include "Components.h"
#include <fstream>
#include <typeinfo>
#include "Spirit/Scene/Scripting/ScriptClass.h"
#include "Spirit/Scene/Scripting/ScriptField.h"
#include <memory>

#define yaml(y) << YAML::##y
#define value << YAML::Value <<
#define key << YAML::Key <<



namespace YAML {
	template<>
	struct convert<glm::vec3> {
		static Node encode(const glm::vec3& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs) {
			if (!node.IsSequence() || node.size() != 3) return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};
}


YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v) {
	out yaml(Flow);
	out yaml(BeginSeq) << v.x << v.y << v.z yaml(EndSeq);
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v) {
	out yaml(Flow);
	out yaml(BeginSeq) << v.x << v.y yaml(EndSeq);
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v) {
	out yaml(Flow);
	out yaml(BeginSeq) << v.x << v.y << v.z << v.w yaml(EndSeq);
	return out;
}

Spirit::SceneSerializer::SceneSerializer(const std::shared_ptr<Spirit::Scene>& scene)
	: m_Scene(scene)
{
	YAML::Emitter out;
}



	
	template<typename T>
	static void ComponentSerialize(Spirit::Entity entity, YAML::Emitter& out, std::function<void(T)> func) {
		if (entity.HasComponent<T>()) {
			out << YAML::Key << typeid(T).name();
			out << YAML::BeginMap;
			func(entity.GetComponent<T>());
			out << YAML::EndMap;
		}
	}


	static void ScriptSerialize(Spirit::Entity entity, YAML::Emitter& out, Spirit::Scripting::ScriptingECS& scriptingECS) {
		out key "Scripts";
		out yaml(BeginMap);
		for (auto& script : scriptingECS.GetAllScripts(entity)) {
			out key script->GetTypeName();
			out yaml(BeginMap);
			for (auto string : script->GetClass().GetFieldNames()) {

				out key string;
				out yaml(Value);
				switch (script->GetField(string).GetType()) {
				case Spirit::Scripting::FieldType::Bool:
					out << script->GetField(string).GetValue<bool>();
					break;
				case Spirit::Scripting::FieldType::Float:
					out << script->GetField(string).GetValue<float>();
					break;
				case Spirit::Scripting::FieldType::Int:
					out << script->GetField(string).GetValue<int>();
					break;
				case Spirit::Scripting::FieldType::String:
					out << script->GetField(string).GetValue<std::string>();
					break;
				case Spirit::Scripting::FieldType::UnsignedInt:
					out << script->GetField(string).GetValue<unsigned int>();
					break;
				case Spirit::Scripting::FieldType::Vec2:
					out << script->GetField(string).GetValue<glm::vec2>();
					break;
				case Spirit::Scripting::FieldType::Vec3:
					out << script->GetField(string).GetValue<glm::vec2>();
					break;
				case Spirit::Scripting::FieldType::Vec4:
					out << script->GetField(string).GetValue<glm::vec2>();
					break;
				case Spirit::Scripting::FieldType::Unknown:
					//TODO
					break;
					
				}
			}
			out << YAML::EndMap;
		}
		out << YAML::EndMap;
	}

	void Spirit::SceneSerializer::SerializeEntity(YAML::Emitter& out, Spirit::Entity entity) {
		out yaml(BeginMap);
		out key "Entity" value "1";

		ComponentSerialize<Spirit::TransformComponent>(entity, out, [&](auto c) {
			out key "Position" value c.Position;
			out key "Rotation" value c.Rotation;
			out key "Scale" value c.Scale;
			});
		ComponentSerialize<Spirit::TagComponent>(entity, out, [&](auto c) {
			out key "Tag" value c.Tag;
			});
		ComponentSerialize<Spirit::CameraComponent>(entity, out, [&](auto c) {
			out key "IsMain" value c.IsMain;
			out key "Type";
			switch (c.Type) {
			case CameraType::Perspective: {
				out value "Perspective";
				out key "Zoom" value std::static_pointer_cast<Render::PerspectiveCamera>(c.Camera)->GetZoom();
				break;
			}
			case CameraType::Orthographic: {
				out value "Orthographic";
				break;
			}
			}
			});
		ComponentSerialize<Spirit::MeshRendererComponent>(entity, out, [&](auto c) {
			out key "Path" value c.Mesh->GetPath().string();
			});
		ComponentSerialize<Spirit::MaterialComponent>(entity, out, [&](auto c) {
			//TODO
			});


		ScriptSerialize(entity, out, m_Scene->GetScriptingECS());

		out yaml(EndMap);
	}


	void Spirit::SceneSerializer::Serialize(const std::filesystem::path& filepath)
	{
		YAML::Emitter out;
		out yaml(BeginMap);
		out key "Scene" value m_Scene->GetPath().string();
		out key "Entites" value YAML::BeginSeq;
		m_Scene->m_Registry.each([&](auto entityID) {
			Entity entity = Entity(entityID, m_Scene.get());
			SerializeEntity(out, entity);
			});
		out yaml(EndSeq);
		out yaml(EndMap);


		std::ofstream fout(filepath.string());
		fout << out.c_str();
	}

	bool Spirit::SceneSerializer::Deserialize(const std::filesystem::path& filepath)
	{
		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();


		auto entities = data["Entities"];
		if (entities) {
			for (auto entity : entities) {
				uint64_t uuid = entity["Entity"].as<uint64_t>(); //Not done

				std::string name;
				auto tagComponent = entity[typeid(TagComponent).name()];
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();

				Entity deserializedEntity = m_Scene->CreateEntity(name);

				auto transformComponent = entity[typeid(TransformComponent).name()];
				if (transformComponent) {
					deserializedEntity.GetComponent<TransformComponent>().Position = transformComponent["Position"].as<glm::vec3>();
					deserializedEntity.GetComponent<TransformComponent>().Rotation = transformComponent["Rotation"].as<glm::vec3>();
					deserializedEntity.GetComponent<TransformComponent>().Scale = transformComponent["Scale"].as<glm::vec3>();
				}

				auto cameraComponent = entity[typeid(CameraComponent).name()];
				if (cameraComponent) {
					deserializedEntity.AddComponent<CameraComponent>();
					deserializedEntity.GetComponent<CameraComponent>().IsMain = cameraComponent["IsMain"].as<bool>();
					std::string cameraType = cameraComponent["Type"].as<std::string>();
					if(cameraType == "Perspective") {
						deserializedEntity.GetComponent<CameraComponent>().Type == CameraType::Perspective;
						std::static_pointer_cast<Render::PerspectiveCamera>(deserializedEntity.GetComponent<CameraComponent>().Camera)->SetZoom(cameraComponent["Zoom"].as<float>());
					}
					else if (cameraType == "Orthographic") {
						deserializedEntity.GetComponent<CameraComponent>().Type == CameraType::Orthographic;
					}
				}


				auto meshComponent = entity[typeid(MeshRendererComponent).name()];
				if (meshComponent) {
					deserializedEntity.AddComponent<MeshRendererComponent>();
					deserializedEntity.GetComponent<MeshRendererComponent>().Mesh = AssetLibrary::GetMeshRegistry().GetMember({ meshComponent["Path"].as<std::string>() });
				}




				auto scripts = entity["Scripts"];
				if (scripts) {
					for (auto script : scripts) {

					}
				}
			}
		}
	}

		
