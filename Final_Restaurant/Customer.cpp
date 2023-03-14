#include "Customer.h"
#include "CustomerStates.h"
#include "Seat.h"
#include "TileMap.h"

#include "TypeId.h"


Customer::Customer(AI::AIWorld& world)
	: Agent(world, Types::CustomerID)
{}

void Customer::Load(const Texture2D& Sprite, TileMap& tileMap)
{
	//Setup state machine
	mStateMachine = std::make_unique<AI::StateMachine<Customer>>(*this);
	mStateMachine->AddState<CustomerLookingForSeat>();
	mStateMachine->AddState<CustomerWaitingForFood>();
	mStateMachine->AddState<CustomerEating>();
	mStateMachine->AddState<CustomerLeaving>();

	mTileMap = &tileMap;
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
		if (mUsePathFinding && !mPath.empty())
		{
			auto pathPos = mPath.front();
			const float distance = sqrtf((posX - pathPos.x) * (posX - pathPos.x) + (posY - pathPos.y) * (posY - pathPos.y));
			if (distance > 20.0f + radius)
			{
				velX = (pathPos.x - posX) * 10.f;
				velY = (pathPos.y - posY) * 10.f;
				posX += velX * deltaTime;
				posY += velY * deltaTime;
			}
			else
			{
				mPath.erase(mPath.begin());
			}
		}
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

void Customer::DebugRender(bool debug)
{
	if (debug && mUsePathFinding)
	{
		mTileMap->RenderPath(mPath);
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

void Customer::FindPathBFSTo(float endX, float endY)
{			
	mPath = mTileMap->FindPathBFS(posX, posY, endX, endY);
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

