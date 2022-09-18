#include "sppch.h"
#include "AssetViewer.h"
#include <filesystem>


static std::vector<std::string> GetFileExtensionsOutFileType(Spirit::FileType type) {
	switch (type)
	{
	case Spirit::FileType::Directory:
		return {""};
	case Spirit::FileType::Script:
		return {"cs"};
	case Spirit::FileType::Material:
		return {"spiritmaterial"};
	case Spirit::FileType::Image:
		return {"png"};
	case Spirit::FileType::Mesh:
		return {"fbx"};
	case Spirit::FileType::Font:
		return {};
	case Spirit::FileType::Prefab:
		return {"spiritprefab"};
	case Spirit::FileType::Scene:
		return {"spiritscene"};
	default:
		break;
	}
}

Spirit::AssetViewer::AssetViewer(const std::filesystem::path& path, FileType type)
	: m_Path(path)
{
	m_Extensions = GetFileExtensionsOutFileType(type);
}







std::vector<std::string> Spirit::AssetViewer::GetAllFiles()
{
	return std::vector<std::string>();
}
