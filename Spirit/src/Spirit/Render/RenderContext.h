#pragma once
#include <memory>

namespace Spirit::Render {
	class RenderContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		
		static std::unique_ptr<RenderContext> Create(void* window);
	};
}