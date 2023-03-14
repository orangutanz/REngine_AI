#pragma once

#include <AI.h>
#include <REngine.h>

class Seat;
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
	void Load(const Texture2D& Sprite);
	void Unload();
	void Update(float deltaTime);
	void Render();
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

	//getters
	bool GetActive() { return mIsActive; }
	bool IsSeated() { return !(mSeat == nullptr); }
	bool DoesHaveFood() { return mHaveFood; }
	bool FoodOdered() { return mOrderFood; }

	void LeaveSeat();
private:

	std::unique_ptr<AI::StateMachine<Customer>> mStateMachine;

	Texture2D mCustomerSprite;
	Seat* mSeat = nullptr;
	bool mOrderFood = false;
	bool mHaveFood = false;
	bool mIsActive = false;

};