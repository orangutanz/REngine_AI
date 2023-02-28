#include "FarmerStates.h"
#include "TypeId.h"

void FarmerIdle::Enter(Farmer& agent)
{
	mWaitTime = 1.0f;
}

void FarmerIdle::Update(Farmer& agent, float deltaTime)
{
	mWaitTime -= deltaTime;
	if (mWaitTime <= 0.0f)
	{
		if (agent.OutOfWater())
		{
			agent.ChangeState(Farmer::State::GettingWater);
		}
		else
		{
			agent.ChangeState(Farmer::State::WateringCrop);
		}
	}

	DrawText(agent.OutOfWater() ? "Is Dry" : "Have Water" , agent.posX + 50.0f, agent.posY - 200.0f, 24, agent.OutOfWater() ? YELLOW : WHITE);
	DrawText(std::to_string(mWaitTime).c_str(), agent.posX + 50.f, agent.posY - 170.0f, 16, WHITE);
	DrawText("Idle", agent.posX + 50.f, agent.posY - 150.f, 24, WHITE);
	
}

void FarmerIdle::Exit(Farmer& agent)
{
}

void FarmerGetWater::Enter(Farmer& agent)
{
	std::vector<AI::Entity*> entities = agent.world.GetAllEntitiesOfType(Types::WellID);
	float minDistance = FLT_MAX;
	for (auto entity : entities)
	{
		float distanceSqr = (agent.posX - entity->posX) * (agent.posX - entity->posX) + (agent.posY - entity->posY) * (agent.posY - entity->posY);
		if (distanceSqr < minDistance)
		{
			minDistance = distanceSqr;
			mTarget = static_cast<Well*>(entity);
		}
	}
}

void FarmerGetWater::Update(Farmer& agent, float deltaTime)
{
	if (mTarget)
	{
		const float distance = sqrtf((agent.posX - mTarget->posX) * (agent.posX - mTarget->posX) + (agent.posY - mTarget->posY) * (agent.posY - mTarget->posY));
		if (distance > 50.0f + agent.radius)
		{	
			agent.velX = (mTarget->posX - agent.posX) * 10.f;
			agent.velY = (mTarget->posY - agent.posY) * 10.f;
			agent.posX += agent.velX * deltaTime;
			agent.posY += agent.velY * deltaTime;
		}
		else
		{
			agent.GetWater(mTarget->GetWater());
			mTarget = nullptr;

			agent.ChangeState(Farmer::State::Idle);
		}
		DrawText(agent.OutOfWater() ? "Is Dry" : "Have Water" , agent.posX + 50.0f, agent.posY - 200.0f, 24, agent.OutOfWater() ? YELLOW : WHITE);
		DrawText("Getting Water", agent.posX + 50.f, agent.posY - 150.f, 24, WHITE);
	}
	else
	{
		agent.ChangeState(Farmer::State::Idle);
	}
}

void FarmerGetWater::Exit(Farmer& agent)
{
}

void FarmerWaterCrop::Enter(Farmer& agent)
{
	std::vector<AI::Entity*> entities = agent.world.GetAllEntitiesOfType(Types::CropID);
	for (auto entity : entities)
	{
		auto crop = static_cast<Crop*>(entity);
		if (crop->IsDry())
		{
			mTarget = crop;
			return;
		}
	}
}

void FarmerWaterCrop::Update(Farmer& agent, float deltaTime)
{
	if (mTarget)
	{
		const float distance = sqrtf((agent.posX - mTarget->posX) * (agent.posX - mTarget->posX) + (agent.posY - mTarget->posY) * (agent.posY - mTarget->posY));
		if (distance > 50.0f + agent.radius)
		{
			const auto directionX = mTarget->posX - agent.posX / distance;
			const auto directionY = mTarget->posY - agent.posY / distance;

			agent.velX = (mTarget->posX - agent.posX) * 10.f;
			agent.velY = (mTarget->posY - agent.posY) * 10.f;
			agent.posX += agent.velX * deltaTime;
			agent.posY += agent.velY * deltaTime;
		}
		else
		{
			float waterAmount = 100 - mTarget->GetWater();
			waterAmount = agent.WaterCrop(waterAmount);			
			mTarget->WaterCrop(waterAmount);
			mTarget = nullptr;

			agent.ChangeState(Farmer::State::Idle);
		}
		DrawText(agent.OutOfWater() ?  "Is Dry" : "Have Water" , agent.posX + 50.0f, agent.posY - 200.0f, 24, agent.OutOfWater() ? YELLOW : WHITE);
		DrawText("Watering Crop", agent.posX + 50.f, agent.posY - 150.f, 24, WHITE);
	}
	else
	{
		agent.ChangeState(Farmer::State::Idle);
	}
}

void FarmerWaterCrop::Exit(Farmer& agent)
{
}
