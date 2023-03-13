#pragma once

#include "Entity.h"
#include "EMath.h"

namespace AI
{
	class Agent;
	using AgentPtrs = std::vector<Agent*>;

	class Agent : public Entity
	{
	public:
		Agent(AIWorld& world, uint32_t typeID);
		~Agent() override = default;

		void SetAgentTarget(Agent* _target);

		EMath::Matrix3  GetWorldTransform() const;

		std::vector<Agent*> neighbors;
		float velX = 0.f;
		float velY = 0.f;
		float destX = 0.f;
		float destY = 0.f;
		Agent* agentTarget;

		float maxSpeed = 100.0f;
		float mass = 1.0f;
	};
}