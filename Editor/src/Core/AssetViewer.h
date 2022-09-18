#pragma once
#include <filesystem>
#include "Spirit/Core/FileType.h"

namespace Spirit {
	class AssetViewer {
	public:
		AssetViewer(const std::filesystem::path& path, FileType type);
		std::vector<std::string> GetAllFiles();
	private:
		std::filesystem::path m_Path;
		std::vector<std::string> m_Extensions;
	};
}