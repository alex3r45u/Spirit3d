#pragma once
#include "MaterialLibrary.h"
#include "ShaderLibrary.h"

namespace Spirit {
	class AssetLibrary {
	public:
		static MaterialLibrary s_MaterialLibrary;
		static ShaderLibrary s_ShaderLibrary;
	};
}