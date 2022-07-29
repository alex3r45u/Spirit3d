#pragma once

#include "Entity.h"
#include "Spirit/Core/TimeStep.h"

namespace Spirit {
	class TransformComponent;
	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {}

		Entity entity;
		TransformComponent& transform;
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(TimeStep ts) {}
		virtual void ImGui() {}
	private:
		friend class Scene;
	};

}