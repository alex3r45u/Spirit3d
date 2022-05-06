#pragma once
#include "Spirit/Render/Framebuffer.h"

namespace Spirit::Render {
	class OpenGlFramebuffer : public Framebuffer {
	public:
		OpenGlFramebuffer(const FramebufferSettings settings);
		virtual ~OpenGlFramebuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		void Init();

		virtual unsigned int GetRendererID() const override { return m_ColorAttachment;  }

		virtual const FramebufferSettings& GetSettings() const override { return m_Settings; }

		virtual void Reseize(unsigned int width, unsigned int height) override;

	private:
		unsigned int m_RendererID = 0, m_ColorAttachment = 0, m_DepthAttachment = 0;
		FramebufferSettings m_Settings;
	};
}