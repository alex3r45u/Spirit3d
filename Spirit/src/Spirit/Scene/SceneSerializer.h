#pragma once
#include "Scene.h"

namespace Spirit {
	class SceneSerializer {
		static void SerializeText(const std::shared_ptr<Scene>& scene);
	};
}