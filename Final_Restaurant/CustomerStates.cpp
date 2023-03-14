#include "CustomerStates.h"
#include "TypeId.h"

void CustomerLookingForSeat::Enter(Customer& agent)
{
	mWaitTime = 2.0f;
	mTarget = nullptr;
}

void CustomerLookingForSeat::Update(Customer& agent, float deltaTime)
{
	if (mTarget)
	{
		//Change this part to using pathfinding
		const float distance = sqrtf((agent.posX - mTarget->posX) * (agent.posX - mTarget->posX) + (agent.posY - mTarget->posY) * (agent.posY - mTarget->posY));
		if (distance > 64.0f + agent.radius)
		{
			//	using pathfinding
			if (!agent.GetUsePathfind())
			{
				agent.velX = (mTarget->posX - agent.posX) * 2.f;
				agent.velY = (mTarget->posY - agent.posY) * 2.f;
				agent.posX += agent.velX * deltaTime;
				agent.posY += agent.velY * deltaTime;
			}
		}
		else
		{
			agent.SetSeat(mTarget);
			agent.ChangeState(Customer::State::WaitingForFood);
		}
	}
	else
	{
		mWaitTime -= deltaTime;
		if (mWaitTime <= 0.0f)
		{
			//Find empty seat
			std::vector<AI::Entity*> seats = agent.world.GetAllEntitiesOfType(Types::SeatID);
			std::vector<AI::Entity*> emptySeats;
			for (auto i : seats)
			{
				auto seat = static_cast<Seat*>(i);
				if (!seat->IsOccupied())
				{
					emptySeats.emplace_back(i);
				}
			}
			float minDistance = FLT_MAX;
			for (auto entity : emptySeats)
			{
				float distanceSqr = (agent.posX - entity->posX) * (agent.posX - entity->posX) + (agent.posY - entity->posY) * (agent.posY - entity->posY);
				if (distanceSqr < minDistance)
				{
					minDistance = distanceSqr;
					mTarget = static_cast<Seat*>(entity);
				}
			}
			if (mTarget)
			{
				mTarget->SetOccupied(true);
				agent.FindPathBFSTo(mTarget->posX, mTarget->posY);
			}
			mWaitTime = 2.0f;
		}
	}	

	DrawText("LookForSeat", agent.posX + 20.f, agent.posY - 100.f, 24, WHITE);
}

void CustomerLookingForSeat::Exit(Customer& agent)
{
}

void CustomerWaitingForFood::Enter(Customer& agent)
{
}

void CustomerWaitingForFood::Update(Customer& agent, float deltaTime)
{
	mWaitTime -= deltaTime;
	if (mWaitTime <= 0.0f)
	{
		if (agent.DoesHaveFood())
		{
			agent.ChangeState(Customer::State::Eating);
		}
		mWaitTime = 1.0f;
	}
	DrawText("WaitForFood", agent.posX + 20.f, agent.posY - 100.f, 24, GOLD);
}

void CustomerWaitingForFood::Exit(Customer& agent)
{
}

void CustomerEating::Enter(Customer& agent)
{

}

void CustomerEating::Update(Customer& agent, float deltaTime)
{
	mEatingTime -= deltaTime;
	if (mEatingTime <= 0.0f)
	{
		if (agent.DoesHaveFood())
		{
			agent.ChangeState(Customer::State::Leaving);
		}
	}
	DrawText("Eating", agent.posX + 20.f, agent.posY - 100.f, 24, YELLOW);
}

void CustomerEating::Exit(Customer& agent)
{
}

void CustomerLeaving::Enter(Customer& agent)
{
	agent.LeaveSeat();
	agent.FindPathBFSTo(mExitX, mExitY);
}

void CustomerLeaving::Update(Customer& agent, float deltaTime)
{
	//Change this part to using pathfinding
	const float distance = sqrtf((agent.posX - mExitX) * (agent.posX - mExitX) + (agent.posY - mExitY) * (agent.posY - mExitY));
	if (distance > 64.0f + agent.radius)
	{	
		//using pathfinding
		if (!agent.GetUsePathfind())
		{
			agent.velX = (mExitX - agent.posX) * 2.f;
			agent.velY = (mExitY - agent.posY) * 2.f;
			agent.posX += agent.velX * deltaTime;
			agent.posY += agent.velY * deltaTime;
		}
	}
	else
	{
		agent.Reset();
	}
	DrawText("Leaving", agent.posX + 20.f, agent.posY - 100.f, 24, GREEN);
}

void CustomerLeaving::Exit(Customer& agent)
{
}
