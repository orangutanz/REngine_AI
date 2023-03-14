#include "Customer.h"
#include "CustomerStates.h"
#include "Seat.h"

#include "TypeId.h"


Customer::Customer(AI::AIWorld& world)
	: Agent(world, Types::CustomerID)
{}

void Customer::Load(const Texture2D& Sprite)
{
	//Setup state machine
	mStateMachine = std::make_unique<AI::StateMachine<Customer>>(*this);
	mStateMachine->AddState<CustomerLookingForSeat>();
	mStateMachine->AddState<CustomerWaitingForFood>();
	mStateMachine->AddState<CustomerEating>();
	mStateMachine->AddState<CustomerLeaving>();

	mCustomerSprite = Sprite;
}

void Customer::Unload()
{

}

void Customer::Update(float deltaTime)
{
	mIsActive;
	if (mIsActive)
	{
		mStateMachine->Update(deltaTime);
	}
}

void Customer::Render()
{
	if (mIsActive)
	{
		float halfWidth = mCustomerSprite.width * 0.5f;
		float halfHeight = mCustomerSprite.height * 0.5f;
		DrawTexture(mCustomerSprite, posX - halfWidth, posY - halfHeight, WHITE);
		//DrawCircle(destX, destY, 6.0f, GREEN);

	}
}

void Customer::SetHaveFood(bool food)
{
	mHaveFood = food;
	if (food && mSeat)
	{
		mSeat->SetDrawFood(true);
	}
}

void Customer::LeaveSeat()
{
	if (mSeat)
	{
		mSeat->SetDrawFood(false);
		mSeat->SetOccupied(false);
		mSeat = nullptr;
	}
}


void Customer::ChangeState(State state)
{
	mStateMachine->ChangeState(state);
}

