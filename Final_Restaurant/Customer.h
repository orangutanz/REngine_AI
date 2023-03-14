#pragma once

#include <AI.h>
#include <REngine.h>

class Seat;
class TileMap;
class Customer : public AI::Agent
{
public:
	enum State
	{
		LookingForSeat,
		WaitingForFood,
		Eating,
		Leaving
	};

	Customer(AI::AIWorld& world);
	void Load(const Texture2D& Sprite,TileMap& tileMap);
	void Unload();
	void Update(float deltaTime);
	void Render();
	void DebugRender(bool debug = true);
	void ChangeState(State state);

	//setters
	void Reset() {
		ChangeState(LookingForSeat);
		mSeat = nullptr;
		mOrderFood = false;
		mHaveFood = false;
		mIsActive = false;
	}
	void SetActive(bool active = true) { mIsActive = active; }
	void SetSeat(Seat* seat) {  mSeat = seat; }
	void SetHaveFood(bool food);
	void SetFoodOrder(bool order) { mOrderFood = order; }
	void SetUsePathFind(bool usage) { mUsePathFinding = usage; }

	//getters
	bool GetActive() { return mIsActive; }
	bool IsSeated() { return !(mSeat == nullptr); }
	bool DoesHaveFood() { return mHaveFood; }
	bool FoodOdered() { return mOrderFood; }
	bool GetUsePathfind() { return mUsePathFinding; }

	void FindPathBFSTo(float endX, float endY);

	void LeaveSeat();
private:

	Texture2D mCustomerSprite;
	std::unique_ptr<AI::StateMachine<Customer>> mStateMachine;
	TileMap* mTileMap;
	Seat* mSeat = nullptr;
	bool mOrderFood = false;
	bool mHaveFood = false;
	bool mIsActive = false;
	bool mUsePathFinding = true;
	bool mDebug = false;
	std::vector<REng::Math::Vector2> mPath;



};