#include "sppch.h"
#include "SceneSerializer.h"
#include <functional>
#include "Components.h"
#include <fstream>
#include <typeinfo>
#include "Spirit/Scene/Scripting/ScriptClass.h"
#include "Spirit/Scene/Scripting/ScriptField.h"
#include "Spirit/Scene/Scripting/ScriptController.h"
#include <memory>

#define yaml(y) << YAML::##y
#define value << YAML::Value <<
#define key << YAML::Key <<

#define DESERIALIZE_SCRIPT(type) if(script["Fields"][field]["type"].as<std::string>() == #type) {scriptfield.SetValue(script["Fields"][field]["value"].as<##type>());}
#define SERIALIZE_SCRIPT(type, field) if(script->GetField(string).GetType() == ##field) {out key "value" value script->GetField(string).GetValue<##type>(); out key "type" value #type;}


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

	template<>
	struct convert<glm::vec2> {
		static Node encode(const glm::vec2& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs) {
			if (!node.IsSequence() || node.size() != 2) return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4> {
		static Node encode(const glm::vec4& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs) {
			if (!node.IsSequence() || node.size() != 4) return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
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
		out yaml(BeginSeq);
		for (auto& script : scriptingECS.GetAllScripts(entity)) {
			out yaml(BeginMap);
			out key "Name" value script->GetTypeName();
			out key "Fields" yaml(BeginMap);
			for (auto string : script->GetClass().GetFieldNames()) {

				out key string yaml(BeginMap);
				SERIALIZE_SCRIPT(bool, Spirit::Scripting::FieldType::Bool);
				SERIALIZE_SCRIPT(float, Spirit::Scripting::FieldType::Float);
				SERIALIZE_SCRIPT(int, Spirit::Scripting::FieldType::Int);
				SERIALIZE_SCRIPT(std::string, Spirit::Scripting::FieldType::String);
				SERIALIZE_SCRIPT(unsigned int, Spirit::Scripting::FieldType::UnsignedInt);
				SERIALIZE_SCRIPT(glm::vec2, Spirit::Scripting::FieldType::Vec2);
				SERIALIZE_SCRIPT(glm::vec3, Spirit::Scripting::FieldType::Vec3);
				SERIALIZE_SCRIPT(glm::vec4, Spirit::Scripting::FieldType::Vec4);
				//TODO unkown
			}
			out << YAML::EndMap;
			out << YAML::EndMap;
			out << YAML::EndMap;
		}
		out << YAML::EndSeq;
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
			out key "Path" value c.Path.string();
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
		out key "Entities" value YAML::BeginSeq;
		m_Scene->m_Registry.each([&](auto entityID) {
			Entity entity = Entity(entityID, m_Scene.get());
			SerializeEntity(out, entity);
			});
		out yaml(EndSeq);
		out yaml(EndMap);


		std::ofstream fout(filepath.string());
		fout << out.c_str();
		fout.close();
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
					
					
					std::string cameraType = cameraComponent["Type"].as<std::string>();
					if(cameraType == "Perspective") {
						deserializedEntity.AddComponent<CameraComponent>(CameraType::Perspective);
						deserializedEntity.GetComponent<CameraComponent>().Type == CameraType::Perspective;
						std::static_pointer_cast<Render::PerspectiveCamera>(deserializedEntity.GetComponent<CameraComponent>().Camera)->SetZoom(cameraComponent["Zoom"].as<float>());
					}
					else if (cameraType == "Orthographic") {
						deserializedEntity.AddComponent<CameraComponent>(CameraType::Orthographic);
						deserializedEntity.GetComponent<CameraComponent>().Type == CameraType::Orthographic;
					}
					deserializedEntity.GetComponent<CameraComponent>().IsMain = cameraComponent["IsMain"].as<bool>();
				}


				auto meshComponent = entity[typeid(MeshRendererComponent).name()];
				if (meshComponent) {
					deserializedEntity.AddComponent<MeshRendererComponent>();
					deserializedEntity.GetComponent<MeshRendererComponent>().Path =meshComponent["Path"].as<std::string>();
				}




				auto scripts = entity["Scripts"];
				if (scripts) {
					for (auto script : scripts) {
						std::shared_ptr<Scripting::ScriptObject> component = std::make_shared<Scripting::ScriptObject>(Scripting::ScriptController::GetDomain().GetClass(script["Name"].as<std::string>()).CreateInstance());
						m_Scene->m_ScriptingECS.AddComponent((unsigned int)deserializedEntity, component);
						
						Scripting::ScriptClass& _class = component->GetClass();
						for (auto field : _class.GetFieldNames()) {
							if (script["Fields"][field]) {
								SP_CORE_INFO(field);
								Scripting::ScriptField& scriptfield = component->GetField(field);
								SP_CORE_INFO(script["Fields"][field]["type"].as<std::string>());
								DESERIALIZE_SCRIPT(bool);
								DESERIALIZE_SCRIPT(float);
								DESERIALIZE_SCRIPT(int);
								DESERIALIZE_SCRIPT(std::string);
								DESERIALIZE_SCRIPT(unsigned int);
								DESERIALIZE_SCRIPT(glm::vec2);
								DESERIALIZE_SCRIPT(glm::vec3);
								DESERIALIZE_SCRIPT(glm::vec4);
							}
							
						}
						
					}
				}
			}
		}
	}

		
