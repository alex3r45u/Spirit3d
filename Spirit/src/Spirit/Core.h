#pragma once
#include <memory>



#ifdef SP_PLATFORM_WINDOWS
	
#else
	#error SPIRIT only supports Windows!
#endif

#ifdef SP_DEBUG
//#define SP_ENABLE_ASSERTS
#endif

#ifdef SP_ENABLE_ASSERTS
#define SP_ASSERT(x, ...) { if(!(x)) { SP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define SP_CORE_ASSERT(x, ...) { if(!(x)) { SP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define SP_ASSERT(x, ...)
#define SP_CORE_ASSERT(x, ...)
#endif



#define BIT(x) (1 << x)

#define SP_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define SP_ASSET_PATH "C:\\Users\\ap\\source\\repos\\Spirit3d\\Editor\\assets"

namespace Spirit {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}

namespace Spirit::Render {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}