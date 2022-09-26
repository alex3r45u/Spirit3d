#pragma once;
#include "sppch.h"
#include "ScriptSolutionCreater.h"
#include "Spirit/Application.h"
#include <filesystem>


void Spirit::ScriptSolutionCreater::Create(const std::shared_ptr<Project>& project)
{
	const std::string scriptSolution = Spirit::Application::Get().GetProject()->GetSettings().ScriptSoulutionPath.string();
	const std::string assets = Spirit::Application::Get().GetProject()->GetSettings().AssetPath.string();
	const std::string currentPath = std::filesystem::current_path().generic_string();
	const std::string name = Spirit::Application::Get().GetProject()->GetSettings().Path.stem().string();
	const std::string path = scriptSolution + "/" + "premake5.lua";


	std::ofstream stream(path);
	stream << "workspace \"" << name << "\"" << std::endl;
	stream << "	architecture \"x64\"" << std::endl;
	stream << R"(	configurations
	{
		"Release",
	})" << std::endl;
	stream << "	project \"" << name << "\"" << std::endl;
	stream << "		kind \"SharedLib\"" << std::endl;
	stream << "		language \"C#\"" << std::endl;
	stream << "		files { \"" << assets << "/**.cs\"}" << std::endl;
	stream << "		links {\"" << currentPath << "/SpiritScript.dll\" }" << std::endl;
	stream << "		targetdir(\"\")" << std::endl;
	stream.close();

	system("WindowsBuildProject.bat");
}