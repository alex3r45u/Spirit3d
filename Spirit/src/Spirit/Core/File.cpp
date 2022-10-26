#include "sppch.h"
#include "File.h"
#include "Spirit/Application.h"

#define REGISTER_FILE(x, ...) m_ExtensionsFromFileType[x] = __VA_ARGS__;\
							for(std::string i : __VA_ARGS__) {m_FileTypeFromExtension[i] = x;}

bool Spirit::File::initialized;
std::unordered_map<Spirit::FileType, std::vector<std::string>> Spirit::File::m_ExtensionsFromFileType;
std::unordered_map<std::string, Spirit::FileType> Spirit::File::m_FileTypeFromExtension;


std::string Spirit::File::Read(const FileRegion& region, std::filesystem::path path)
{
#ifdef SP_BUILD

#endif
#ifndef SP_BUILD
	std::string regionPath;
	switch (region)
	{
	case FileRegion::Asset:
		regionPath = Application::Get().GetProject()->GetSettings().AssetPath.string();
		break;
	case FileRegion::Ressource:
		regionPath = Application::Get().GetProject()->GetSettings().RessourcePath.string();
		break;
	default:
		break;
	}
	std::string str = regionPath + "\\" + path.string();
	SP_CORE_INFO(str);
	std::filesystem::path p = std::filesystem::path(str);
	std::string result;
	std::ifstream in(p, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	return result;

#endif
}

Spirit::FileType Spirit::File::GetType(std::string fileExtension)
{
	if (!initialized) { Init(); }
	return m_FileTypeFromExtension[fileExtension];
}

std::vector<std::string> Spirit::File::GetExtensionsOutFileType(const FileType& type)
{
	if (!initialized) { Init(); }
	return m_ExtensionsFromFileType[type];
}

void Spirit::File::Init()
{
	REGISTER_FILE(FileType::Directory, { "" });
	REGISTER_FILE(FileType::Script, { ".cs" });
	REGISTER_FILE(FileType::Material, { ".spiritmaterial" });
	REGISTER_FILE(FileType::Image, { ".png" });
	REGISTER_FILE(FileType::Mesh, { ".fbx" });
	REGISTER_FILE(FileType::Font, { "" });
	REGISTER_FILE(FileType::Prefab, { ".spiritprefab" });
	REGISTER_FILE(FileType::Scene, { ".spiritscene" });
	REGISTER_FILE(FileType::Project, { ".spiritproject" });
	initialized = true;
}

std::filesystem::path Spirit::File::Merge2Paths(const std::filesystem::path& path1, const std::filesystem::path& path2)
{
	return std::filesystem::path(path1.string() + "\\" + path2.string());
}

std::filesystem::path Spirit::File::MergePaths(const std::vector<std::filesystem::path>& paths)
{
	std::filesystem::path result;

	for(auto path : paths) {
		result = std::filesystem::path(result.string() + path.string() + "\\");
	}
	return result;
}