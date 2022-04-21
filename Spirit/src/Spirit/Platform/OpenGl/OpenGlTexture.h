#pragma once
#include "Spirit/Render/Texture.h"

namespace Spirit::Render {
	class OpenGlTexture2d : public Texture2d {
	public:
		OpenGlTexture2d(const std::string& path);
		virtual ~OpenGlTexture2d();

		virtual void Bind(unsigned int slot) override;
		virtual unsigned int GetWidth() override { return m_Width; }
		virtual unsigned int GetHeight() override { return m_Height; }

	private:
		std::string m_Path;
		unsigned int m_Width, m_Height;
		unsigned int m_RendererID;
	};
}