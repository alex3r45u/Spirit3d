#pragma once
#include "ScriptObject.h"



namespace Spirit::Scripting {
	class ScriptComponent {
	public:
		ScriptComponent(ScriptObject& object);
		bool GetDisplay();
		void GetDisplay(bool value);
		ScriptObject& GetScriptObject();

		operator ScriptObject() const { return m_ScriptObject; }
	private:
		bool m_Display;
		ScriptObject m_ScriptObject;
	};
}