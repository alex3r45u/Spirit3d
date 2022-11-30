#pragma once;
#include "sppch.h"
#include "ScriptSolution.h"
#include "Spirit/Application.h"
#include <filesystem>
#include "Spirit/Core/File.h"
#include "Spirit/Scene/Scripting/ScriptController.h"
#include "Spirit/Scene/Scene.h"


void Spirit::ScriptSolution::Open(const std::shared_ptr<Project>& project)
{
	auto path = PROJECT->GetActiveScene()->GetPath();
	PROJECT->SaveActiveScene(path);
	Scripting::ScriptController::Unload();
	std::filesystem::path projectPath = Spirit::Application::Get().GetProject()->GetSettings().Path;
	std::string solutionName = Spirit::Application::Get().GetProject()->GetSettings().ProjectName;
	system((File::Merge2Paths(projectPath, solutionName+".sln")).string().c_str());
	Scripting::ScriptController::Load();
	PROJECT->SetLoadScene(path);
}
