#pragma once
#include "Farmer.h"
#include "Crop.h"
#include "Well.h"

//Idle state
class FarmerIdle : public AI::State<Farmer>
{
public:
	void Enter(Farmer& agent) override;
	void Update(Farmer& agent, float deltaTime) override;
	void Exit(Farmer& agent) override;

private:
	float mWaitTime = 0.0f;
};


//GetWater state
class Well;
class FarmerGetWater : public AI::State<Farmer>
{
public:
	void Enter(Farmer& agent) override;
	void Update(Farmer& agent, float deltaTime) override;
	void Exit(Farmer& agent) override;

	Well* mTarget;
};

//WaterCrop state
class Crop;
class FarmerWaterCrop : public AI::State<Farmer>
{
public:
	void Enter(Farmer& agent) override;
	void Update(Farmer& agent, float deltaTime) override;
	void Exit(Farmer& agent) override;

private:
	Crop* mTarget;
};