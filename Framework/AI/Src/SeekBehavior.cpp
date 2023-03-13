#pragma once
#include "stdafx.h"
#include "Precompiled.h"
#include "SeekBehavior.h"

#include "Agent.h"

using namespace AI;

EMath::Vector2 SeekBehavior::Calculate(Agent& agent)
{
	const EMath::Vector2 agentToDestination = { agent.destX - agent.posX ,agent.destY - agent.posY };
	const float distToDestination = EMath::Magnitude(agentToDestination);

	if (distToDestination <= 0.0f)
	{
		return{};
	}

	const auto desiredVelocity = (agentToDestination / distToDestination) * agent.maxSpeed;
	const auto seekForce = desiredVelocity - EMath::Vector2(agent.velX, agent.velY);

	//if (IsDebug())
	//{
	//	DrawLine(agent.position.x, agent.position.y, agent.position.x + desiredVelocity.x, agent.position.y + desiredVelocity.y, YELLOW);
	//	DrawLine(agent.position.x, agent.position.y, agent.position.x + agent.velocity.x, agent.position.y + agent.velocity.y, GREEN);
	//}


	return seekForce;
}