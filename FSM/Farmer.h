#pragma once

#include <AI.h>
#include <REngine.h>

class Farmer : public AI::Agent
{
public:
	enum State
	{
		Idle,
		GettingWater,
		WateringCrop
	};

	Farmer(AI::AIWorld& world);
	void Load();
	void Unload();

	void ChangeState(State state);

	void Update(float deltaTime);
	void Render();

	float WaterCrop(float useWater)
	{
		if (mCarriedWater < useWater)
		{
			float waterAmount = mCarriedWater;
			mCarriedWater = 0;
			return waterAmount;
		}
		mCarriedWater -= useWater;
		return useWater;
	}
	bool OutOfWater() { return mCarriedWater <= 20.0f; }
	void GetWater(float amount) { mCarriedWater += amount; }

private:
	std::unique_ptr<AI::StateMachine<Farmer>> mStateMachine;

	Texture2D mFarmerSprite;
	//Rectangle mTextureRect;

	float mCarriedWater = 0.f;
};