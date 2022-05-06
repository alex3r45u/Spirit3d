#pragma once
#include <memory>

namespace Spirit::Render {

	struct FramebufferSettings {
		unsigned int Width, Height;
	};

	class Framebuffer {
	public:
		Framebuffer() {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual unsigned int GetRendererID() const = 0;

		virtual const FramebufferSettings& GetSettings() const = 0;

		virtual void Reseize(unsigned int width, unsigned int height) = 0;

		static std::shared_ptr<Framebuffer> Create(const FramebufferSettings settings);
	};
}