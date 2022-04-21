#pragma once

namespace Spirit::Render {
	class Light {
	public:
		Light() {}
		virtual void UploadUniforms() = 0;
		virtual void Submit() = 0;
	};
}