#pragma once

#include <AI.h>
#include <REngine.h>

class Waiter : public AI::Agent
{
public:
	enum State
	{
		Idle,
		GetFood,
		DeliverFood
	};
	Waiter(AI::AIWorld& world);
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();
	void ChangeState(State state);


	//Getters
	bool HaveFood() { return mHaveFood; }

	//Setters
	void SetFood(bool food) { mHaveFood = food; }

private:
	std::unique_ptr<AI::StateMachine<Waiter>> mStateMachine;

	Texture2D mWaiterSprite;
	bool mHaveFood = false;

};