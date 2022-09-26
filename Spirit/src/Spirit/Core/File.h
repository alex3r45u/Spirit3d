#pragma once
#include <filesystem>


namespace Spirit {
	enum class FileRegion {
		None = 0,
		Asset,
		Ressource
	};
	class File {
	public:
		static std::string Read(const FileRegion& region, std::filesystem::path path);
	};
}