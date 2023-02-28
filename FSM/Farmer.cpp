#include "Farmer.h"
#include "FarmerStates.h"

#include "TypeId.h"

Farmer::Farmer(AI::AIWorld& world)
	: Agent(world, Types::FarmerID)
{}

void Farmer::Load()
{
	//Setup state machine
	mStateMachine = std::make_unique<AI::StateMachine<Farmer>>(*this);
	mStateMachine->AddState<FarmerIdle>();
	mStateMachine->AddState<FarmerGetWater>();
	mStateMachine->AddState<FarmerWaterCrop>();
	mStateMachine->ChangeState(Idle);

	std::string farmerPath;
	REng::ResourcesFullPath("Farmer.png", farmerPath);
	mFarmerSprite = LoadTexture(farmerPath.c_str());

	posX = 100.f;
	posY = 100.f;
}

void Farmer::Unload()
{

}

void Farmer::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Farmer::Render()
{
	float halfWidth = mFarmerSprite.width * 0.5f;
	float halfHeight = mFarmerSprite.height * 0.5f;
	DrawTexture(mFarmerSprite, posX - halfWidth, posY - halfHeight, WHITE);
	DrawCircle(destX, destY, 6.0f, GREEN);
}


void Farmer::ChangeState(State state)
{
	mStateMachine->ChangeState(state);
}

