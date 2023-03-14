#include "Waiter.h"
#include "WaiterStates.h"
#include "Customer.h"
#include "Seat.h"

#include "TypeId.h"


Waiter::Waiter(AI::AIWorld& world)
	: Agent(world, Types::CustomerID)
{}

void Waiter::Load()
{	
	//Setup state machine
	mStateMachine = std::make_unique<AI::StateMachine<Waiter>>(*this);
	mStateMachine->AddState<WaiterIdle>();
	mStateMachine->AddState<WaiterGetFood>();
	mStateMachine->AddState<WaiterDeliverFood>();
	mStateMachine->ChangeState(Waiter::State::Idle);

	std::string filePath;
	REng::ResourcesFullPath("Waiter.png", filePath);
	mWaiterSprite = LoadTexture(filePath.c_str());

	posX = 160;
	posY = 280;
}

void Waiter::Unload()
{
}

void Waiter::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Waiter::Render()
{
	float halfWidth = mWaiterSprite.width * 0.5f;
	float halfHeight = mWaiterSprite.height * 0.5f;
	DrawTexture(mWaiterSprite, posX - halfWidth, posY - halfHeight, WHITE);
	//DrawCircle(destX, destY, 6.0f, GREEN);
}

void Waiter::ChangeState(State state)
{
	mStateMachine->ChangeState(state);
}