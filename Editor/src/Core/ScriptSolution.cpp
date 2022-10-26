#pragma once;
#include "sppch.h"
#include "ScriptSolution.h"
#include "Spirit/Application.h"
#include <filesystem>
#include "Spirit/Core/File.h"
#include "Spirit/Scene/Scripting/ScriptController.h"
#include "Spirit/Scene/Scene.h"

void Spirit::ScriptSolution::Create(const std::shared_ptr<Project>& project)
{
	const std::string projPath = Spirit::Application::Get().GetProject()->GetSettings().Path.string();
	const std::string assets = Spirit::Application::Get().GetProject()->GetSettings().AssetPath.generic_string();
	const std::string currentPath = std::filesystem::current_path().generic_string();
	const std::string  ScriptSolutionName = Spirit::Application::Get().GetProject()->GetSettings().ProjectName;
	const std::string premakePath = projPath + "/" + "premake5.lua";
	//const std::string batPath = Spirit::Application::Get().GetProject()->GetSettings().Path.parent_path().generic_string() + "/" + "WinBuild.bat";

	std::ofstream stream(premakePath);
	stream << "workspace \"" << ScriptSolutionName << "\"" << std::endl;
	stream << "	architecture \"x64\"" << std::endl;
	stream << R"(	configurations
	{
		"Release",
	})" << std::endl;
	stream << "	project \"" << ScriptSolutionName << "\"" << std::endl;
	stream << "		kind \"SharedLib\"" << std::endl;
	stream << "		language \"C#\"" << std::endl;
	stream << "		files { \"" << assets << "/**.cs\"}" << std::endl;
	stream << "		links {\"" << currentPath << "/SpiritScript.dll\" }" << std::endl;
	stream << "		targetdir(\"\")" << std::endl;
	stream.close();

	//batStream << "/vendor/bin/premake/premake5.exe --file=" << scriptSolution << "/premake5.lua vs2022";

	system((currentPath +"/vendor/bin/premake/premake5.exe --file=" + projPath + "/premake5.lua vs2022").c_str());
}

void Spirit::ScriptSolution::Open(const std::shared_ptr<Project>& project)
{
	auto path = PROJECT->GetActiveScene()->GetPath();
	PROJECT->SaveActiveScene(path);
	Scripting::ScriptController::Unload();
	Spirit::ScriptSolution::Create(Spirit::Application::Get().GetProject());
	std::filesystem::path projectPath = Spirit::Application::Get().GetProject()->GetSettings().Path;
	std::string solutionName = Spirit::Application::Get().GetProject()->GetSettings().ProjectName;
	system((File::Merge2Paths(projectPath, solutionName+".sln")).string().c_str());
	Scripting::ScriptController::Load();
	PROJECT->SetLoadScene(path);
}
