#pragma once
#include <filesystem>
#include <memory>
#include <unordered_map>
#include "Scene.h"

namespace Spirit {
//	class Scene;
	class SceneManager {
	public:
		static void CreateScene(const std::filesystem::path &path);
		static void AddScene(std::shared_ptr<Scene> scene);
		static std::shared_ptr<Scene> GetActiveScene();
		static std::shared_ptr<Scene> GetScene(const std::filesystem::path& path);
		static void SetActiveScene(const std::filesystem::path& scene);
		static void SetActiveScene(const std::shared_ptr<Scene>& scene);

		static bool SceneExists(const std::filesystem::path& name);

		static bool SaveScene(const std::filesystem::path& path);
		static bool SaveActiveScene(const std::filesystem::path& path);
		static bool LoadScene(const std::filesystem::path& path);
	private:
		static std::shared_ptr<Scene> m_ActiveScene;
		static std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;
	};
}