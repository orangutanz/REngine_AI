#include "WaiterStates.h"
#include "TypeId.h"

void WaiterIdle::Enter(Waiter& agent)
{
	mWaitTime = 1.0f;
}

void WaiterIdle::Update(Waiter& agent, float deltaTime)
{
	mWaitTime -= deltaTime;
	const float distance = sqrtf((agent.posX - IdleX) * (agent.posX - IdleX) + (agent.posY - IdleY) * (agent.posY - IdleY));
	if (distance > 20.0f + agent.radius)
	{
		agent.velX = (IdleX - agent.posX) * 2.f;
		agent.velY = (IdleY - agent.posY) * 2.f;
		agent.posX += agent.velX * deltaTime;
		agent.posY += agent.velY * deltaTime;
	}
	if (mWaitTime <= 0.0f)
	{
		std::vector<AI::Entity*> entities = agent.world.GetAllEntitiesOfType(Types::CustomerID);
		for (auto entity : entities)
		{
			auto customer = static_cast<Customer*>(entity);
			if (customer->GetActive() && customer->IsSeated() && !customer->FoodOdered() && !customer->DoesHaveFood())
			{
				agent.SetAgentTarget(customer);
				agent.ChangeState(Waiter::State::GetFood);
				break;
			}
		}
	}

	DrawText("Waiting", agent.posX + 20.f, agent.posY - 100.f, 24, WHITE);
}

void WaiterIdle::Exit(Waiter& agent)
{
}

void WaiterDeliverFood::Enter(Waiter& agent)
{
	mCustomer = static_cast<Customer*>(agent.agentTarget);
}

void WaiterDeliverFood::Update(Waiter& agent, float deltaTime)
{
	//Change this part to using pathfinding
	const float distance = sqrtf((agent.posX - mCustomer->posX) * (agent.posX - mCustomer->posX) + (agent.posY - mCustomer->posY) * (agent.posY - mCustomer->posY));
	if (distance > 20.0f + agent.radius)
	{
		agent.velX = (mCustomer->posX - agent.posX) * 2.f;
		agent.velY = (mCustomer->posY - agent.posY) * 2.f;
		agent.posX += agent.velX * deltaTime;
		agent.posY += agent.velY * deltaTime;
	}
	else
	{
		mCustomer->SetHaveFood(true);
		agent.SetFood(false);
		agent.ChangeState(Waiter::State::Idle);
	}
	DrawText("DeliverFood", agent.posX + 20.f, agent.posY - 100.f, 24, WHITE);

}

void WaiterDeliverFood::Exit(Waiter& agent)
{
	mCustomer = nullptr;
}

void WaiterGetFood::Enter(Waiter& agent)
{
	std::vector<AI::Entity*> entities = agent.world.GetAllEntitiesOfType(Types::KitchenID);
	for (auto entity : entities)
	{
		mKitchen = static_cast<Kitchen*>(entity);
	}
	if (mKitchen)
	{
		auto customer = static_cast<Customer*>(agent.agentTarget);
		customer->SetFoodOrder(true);
	}
	else
	{
		agent.ChangeState(Waiter::State::Idle);
	}
}

void WaiterGetFood::Update(Waiter& agent, float deltaTime)
{
	//Change this part to using pathfinding
	const float distance = sqrtf((agent.posX - mKitchen->posX) * (agent.posX - mKitchen->posX) + (agent.posY - mKitchen->posY) * (agent.posY - mKitchen->posY));
	if (distance > 20.0f + agent.radius)
	{
		agent.velX = (mKitchen->posX - agent.posX) * 2.f;
		agent.velY = (mKitchen->posY - agent.posY) * 2.f;
		agent.posX += agent.velX * deltaTime;
		agent.posY += agent.velY * deltaTime;
	}
	else
	{
		agent.SetFood(true);
		agent.ChangeState(Waiter::State::DeliverFood);
	}

	DrawText("GetFood", agent.posX + 20.f, agent.posY - 100.f, 24, WHITE);
}

void WaiterGetFood::Exit(Waiter& agent)
{
	mKitchen = nullptr;
}
