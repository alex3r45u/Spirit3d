#pragma once
#include <memory>
#include <vector>
#include "Parameter.h"

namespace Spirit::Scripting {
	class ParameterList {
	public:
		ParameterList() = default;
		ParameterList(const ParameterList& rhs) = default;
		ParameterList& operator=(const ParameterList & rhs) = default;

		ParameterList& Append(int value);
		ParameterList& Append(float value);
		ParameterList& Append(double value);
		ParameterList& Append(const char* value);

		void Reserve(int size);
		int Size() const;
		void** GetArgs();

		~ParameterList();
	private:
		std::vector<std::shared_ptr<Parameter>> m_Parameters;
		std::vector<void*> m_Raw;
	};
}