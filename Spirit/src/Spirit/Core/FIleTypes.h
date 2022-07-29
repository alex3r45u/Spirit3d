#pragma once

enum FileCategorys {
	Directory,
	Script,
	Material,
	Image,
	Object,
	Font,
	Prefab,
	Scene,
};

class FileTypes {
public:
	static FileCategorys GetCategory();
	static bool isValid(const std::string& fileType);
};