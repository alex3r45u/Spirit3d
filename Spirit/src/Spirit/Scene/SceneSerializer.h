#pragma once
#include <memory>
#include <filesystem>
//#include "Scene.h"
#include "Entity.h"
#include "yaml-cpp/yaml.h"


namespace Spirit {
	class Scene;
	class SceneSerializer {
	public:
		SceneSerializer(const std::shared_ptr<Scene>& scene);

		void Serialize(const std::filesystem::path& filepath);
		//void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::filesystem::path& filepath);
		//bool DeserializeRuntime(const std::string& filepath);
	private:
		void SerializeEntity(YAML::Emitter& out, Spirit::Entity entity);
	private:
		std::shared_ptr<Scene> m_Scene;
	};
}