#pragma once
#include <filesystem>
//#include "Spirit/Scene/SceneManager.h"

namespace Spirit {
	class Scene;
	struct ProjectSettings {
		std::filesystem::path StartScene;
		std::filesystem::path Path;
		std::filesystem::path AssetPath;
		std::filesystem::path RessourcePath;
		std::string ProjectName;
		//TODO
	};
	class Project {
	public:
		Project();
		Project(const ProjectSettings& settings);
		void SetSettings(const ProjectSettings& settings);
		const ProjectSettings& GetSettings();
		void SetScene(const std::shared_ptr<Scene>& scene);
		void SetLoadScene(const std::filesystem::path& path);
		void SaveActiveScene(const std::filesystem::path& path);
		std::shared_ptr<Scene> GetActiveScene();


	private:
		std::shared_ptr<Scene> m_ActiveScene;
		ProjectSettings m_ProjectSettings;
		
	};
}