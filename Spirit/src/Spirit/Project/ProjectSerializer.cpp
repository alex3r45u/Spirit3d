#include "sppch.h"
#include "ProjectSerializer.h"
#include <yaml-cpp/yaml.h>
#include "Spirit/Scene/Scene.h"
#include "Spirit/Core/File.h"
#include "Spirit/Scene/SceneSerializer.h"
#define yaml(y) << YAML::##y
#define value << YAML::Value <<
#define key << YAML::Key <<

Spirit::ProjectSerializer::ProjectSerializer(const std::shared_ptr<Spirit::Project>& project)
	: m_Project(project)
{
}


std::shared_ptr<Spirit::Project> Spirit::ProjectSerializer::CreateProject(const std::filesystem::path& filePath, const std::filesystem::path& ressourcePath)
{
	std::filesystem::path assetPath = File::Merge2Paths(filePath.parent_path(), "assets");
	std::filesystem::create_directory(assetPath);
	ProjectSettings settings;
	settings.Path = filePath.parent_path();
	settings.AssetPath = assetPath;
	settings.RessourcePath = ressourcePath;
	settings.ProjectName = filePath.stem().string();
	
	std::shared_ptr<Project> project = std::make_shared<Project>(settings);
	project->SetScene(std::make_shared<Spirit::Scene>(Spirit::File::Merge2Paths(project->GetSettings().AssetPath, "Example.spiritscene")));
	auto s = project->GetSettings();
	s.StartScene = project->GetActiveScene()->GetPath();
	project->SetSettings(s);
	ProjectSerializer serializer(project);
	serializer.Serialize(filePath);
	SceneSerializer sceneSerializer(project->GetActiveScene());
	sceneSerializer.Serialize(project->GetActiveScene()->GetPath());
	
	return project;
}



void Spirit::ProjectSerializer::Serialize(const std::filesystem::path& filepath)
{
	YAML::Emitter out;

	out yaml(BeginMap);
	out key "Settings" yaml(BeginMap);
	//Settings
	out key "StartScene" value m_Project->GetSettings().StartScene.string();
	out key "ProjectName" value m_Project->GetSettings().ProjectName;
	out yaml(EndMap);
	out yaml(EndMap);

	std::ofstream fout(filepath.string());
	fout << out.c_str();
	fout.close();
}

bool Spirit::ProjectSerializer::Deserialize(const std::filesystem::path& filepath)
{

	std::ifstream stream(filepath);
	std::stringstream strStream;
	strStream << stream.rdbuf();

	YAML::Node data = YAML::Load(strStream.str());

	if (data["Settings"]) {
		YAML::Node settings = data["Settings"];
		ProjectSettings projectSettings;
		projectSettings.Path = filepath.parent_path();
		projectSettings.RessourcePath = std::filesystem::path(std::filesystem::current_path().string() + "\\ressources");
		projectSettings.StartScene = settings["StartScene"].as<std::string>();
		projectSettings.ProjectName = settings["ProjectName"].as<std::string>();
		projectSettings.AssetPath = File::Merge2Paths(projectSettings.Path, "assets");
		m_Project->SetSettings(projectSettings);
	}
	return true;
}
