#pragma once
#include "Spirit/Core.h"


namespace Spirit::Render {
	class Texture {
	public:
		Texture() {}
		virtual ~Texture() {}
		virtual void Bind(unsigned int slot = 0) = 0;
		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;
	};

	class Texture2d : public Texture {
	public:
		static std::shared_ptr<Texture2d> Create(const std::string& path);
	};
}