#pragma once
#include "Spirit/Project/Project.h"

namespace Spirit {
	class ScriptSolution {
	public:
		static void Create(const std::shared_ptr<Project>& project);
		static void Open(const std::shared_ptr<Project>& project);
	};
}
