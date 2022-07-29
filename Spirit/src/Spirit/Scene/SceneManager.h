#pragma once
#include <memory>
#include <unordered_map>
#include <string>

namespace Spirit {
	class Scene;
	class SceneManager {
	public:
		static void AddScene(std::shared_ptr<Scene> scene);
		static std::shared_ptr<Scene> GetActiveScene();
		static void SetActiveScene(const std::string& scene);
	private:
		static std::shared_ptr<Scene> m_ActiveScene;
		static std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;
	};
}