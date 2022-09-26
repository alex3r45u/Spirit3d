#pragma once
#include "Spirit/Project/Project.h"

namespace Spirit {
	class ScriptSolutionCreater {
	public:
		static void Create(const std::shared_ptr<Project>& project);
	};
}
