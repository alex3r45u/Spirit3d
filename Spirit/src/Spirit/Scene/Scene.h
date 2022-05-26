#pragma once
#include "entt.hpp"
#include "Spirit/Core/Timestep.h"

namespace Spirit {
	class Entity;

	class Scene {
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name);

		void OnUpdate(TimeStep ts);
		void OnReseize(unsigned int width, unsigned int height);
	private:
		entt::registry m_Registry;
		friend class Entity;
	};
}