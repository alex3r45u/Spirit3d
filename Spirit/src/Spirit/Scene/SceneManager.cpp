#include "sppch.h"
#include "SceneManager.h"
#include "SceneSerializer.h"

std::shared_ptr<Spirit::Scene> Spirit::SceneManager::m_ActiveScene;
std::unordered_map<std::string, std::shared_ptr<Spirit::Scene>> Spirit::SceneManager::m_Scenes;


void Spirit::SceneManager::CreateScene(const std::filesystem::path& path)
{
	if (SceneExists) {
		SP_CORE_ASSERT(false, "Scene already exists");
	}
	m_Scenes[path.string()] = std::make_shared<Scene>(path);
}

void Spirit::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	if (SceneExists(scene->GetPath())) {
		SP_CORE_ASSERT(false, "Scene aleready exists");
		return;
	}
		
	m_Scenes[scene->GetPath().string()] = scene;
}

std::shared_ptr<Spirit::Scene> Spirit::SceneManager::GetActiveScene()
{
	return m_ActiveScene;
}

std::shared_ptr<Spirit::Scene> Spirit::SceneManager::GetScene(const std::filesystem::path& path)
{
	if (!SceneExists(path.string()))
		return nullptr;
	return m_Scenes[path.string()];
}

void Spirit::SceneManager::SetActiveScene(const std::filesystem::path& scene)
{
	if(!SceneExists(scene.string()))
		SP_CORE_ASSERT(false, "{0}, was not found", scene.string());


	m_ActiveScene = m_Scenes[scene.string()];
}


void Spirit::SceneManager::SetActiveScene(const std::shared_ptr<Scene>& scene)
{
	m_ActiveScene = scene;
}

bool Spirit::SceneManager::SceneExists(const std::filesystem::path& path)
{
	return m_Scenes.find(path.string()) != m_Scenes.end();
}


bool Spirit::SceneManager::SaveScene(const std::filesystem::path& path)
{
	if (!SceneExists(path.string()))
		return false;
	SceneSerializer ss = SceneSerializer(GetScene(path.string()));

	ss.Serialize(path);
	return true;
}


bool Spirit::SceneManager::SaveActiveScene(const std::filesystem::path& path)
{
	SceneSerializer ss = SceneSerializer(GetActiveScene());
	
	ss.Serialize(path);
	return true;
}

bool Spirit::SceneManager::LoadScene(const std::filesystem::path& path)
{
	if (SceneExists(path.string()))
		return false;
	CreateScene(path);
	Spirit::SceneSerializer ss = Spirit::SceneSerializer(GetScene(path.string()));
	ss.Deserialize(path);
	return true;
}