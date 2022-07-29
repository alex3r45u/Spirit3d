#include "sppch.h"
#include "SceneManager.h"
#include "Scene.h"

std::shared_ptr<Spirit::Scene> Spirit::SceneManager::m_ActiveScene;
std::unordered_map<std::string, std::shared_ptr<Spirit::Scene>> Spirit::SceneManager::m_Scenes;

void Spirit::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_Scenes[scene->GetName()] = scene;
}

std::shared_ptr<Spirit::Scene> Spirit::SceneManager::GetActiveScene()
{
	return m_ActiveScene;
}

void Spirit::SceneManager::SetActiveScene(const std::string& scene)
{
	auto iter = m_Scenes.find(scene);

	if (iter == m_Scenes.end()) {
		SP_CORE_ASSERT(false, "{0}, was not found", scene);
	}

	m_ActiveScene = iter->second;
}
