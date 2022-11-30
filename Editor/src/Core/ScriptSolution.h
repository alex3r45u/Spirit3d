#pragma once
#include "Spirit/Project/Project.h"

namespace Spirit {
	class ScriptSolution {
	public:
		static void Open(const std::shared_ptr<Project>& project);
	};
}
