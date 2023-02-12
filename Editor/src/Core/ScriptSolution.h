#pragma once


namespace Spirit {
	class Project;
	class ScriptSolution {
	public:
		static void Open(const std::shared_ptr<Project>& project);
		static void Reload(const std::shared_ptr<Project>& project);
	};
}
