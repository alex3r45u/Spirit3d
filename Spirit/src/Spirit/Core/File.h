#pragma once
#include <filesystem>
#include "FileType.h"
#include <vector>

namespace Spirit {
	enum class FileRegion {
		None = 0,
		Asset,
		Ressource
	};
	class File {
	public:
		static std::string Read(const FileRegion& region, std::filesystem::path path);
		static FileType GetType(std::string fileExtension);
		static std::vector<std::string> GetExtensionsOutFileType(const FileType& type);
		static std::filesystem::path Merge2Paths(const std::filesystem::path& path1, const std::filesystem::path& path2);
		static std::filesystem::path MergePaths(const std::vector<std::filesystem::path>& paths);

	private:
		static std::unordered_map<FileType, std::vector<std::string>> m_ExtensionsFromFileType;
		static std::unordered_map<std::string, FileType> m_FileTypeFromExtension;
		static void Init();
		static bool initialized;
	};
}