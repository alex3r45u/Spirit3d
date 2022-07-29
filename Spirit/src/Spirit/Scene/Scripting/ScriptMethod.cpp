#include "sppch.h"
#include "ScriptMethod.h"



void Spirit::Scripting::ScriptMethod::Invoke(ParameterList params, ScriptObject* object)
{
	MonoObject* obj = nullptr;

	if (object != nullptr)
		obj = object->GetObjectPointer();

	MonoObject* exception = nullptr;
	mono_runtime_invoke(m_Method, obj, params.GetArgs(), &exception);
}
