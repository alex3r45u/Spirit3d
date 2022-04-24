#pragma once
#include "MaterialLibrary.h"
#include "ShaderLibrary.h"
#include "MeshLibrary.h"

namespace Spirit {
	class AssetLibrary {
	public:
		static MaterialLibrary s_MaterialLibrary;
		static ShaderLibrary s_ShaderLibrary;
		static MeshLibrary s_MeshLibrary;
	};
}