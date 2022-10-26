#include "sppch.h"
#include "AssetViewer.h"
#include <filesystem>
#include "Spirit/Core/File.h"

Spirit::AssetViewer::AssetViewer(const std::filesystem::path& path, FileType type)
	: m_Path(path)
{
	m_Extensions = File::GetExtensionsOutFileType(type);
}







std::vector<std::string> Spirit::AssetViewer::GetAllFiles()
{
	return std::vector<std::string>();
}
