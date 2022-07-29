#pragma once

namespace Spirit::Scripting {
	class Parameter {
	public:
		Parameter() = default;
		Parameter(const Parameter& p) = default;
		Parameter& operator=(const Parameter& p) = default;

		virtual void* ptr() = 0;
		virtual ~Parameter() = default;
	};
}