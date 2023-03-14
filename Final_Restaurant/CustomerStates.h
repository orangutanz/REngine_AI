#pragma once
#include "Seat.h"
#include "Customer.h"

class CustomerLookingForSeat : public AI::State<Customer>
{
public:
	void Enter(Customer& agent) override;
	void Update(Customer& agent, float deltaTime) override;
	void Exit(Customer& agent) override;

private:
	Seat* mTarget;
	float mWaitTime = 2.0f;
};

class CustomerWaitingForFood : public AI::State<Customer>
{
public:
	void Enter(Customer& agent) override;
	void Update(Customer& agent, float deltaTime) override;
	void Exit(Customer& agent) override;

private:
	float mWaitTime = 1.0f;
};

class CustomerEating : public AI::State<Customer>
{
public:
	void Enter(Customer& agent) override;
	void Update(Customer& agent, float deltaTime) override;
	void Exit(Customer& agent) override;

private:

	float mEatingTime = 6.0f;
};

class CustomerLeaving : public AI::State<Customer>
{
public:
	void Enter(Customer& agent) override;
	void Update(Customer& agent, float deltaTime) override;
	void Exit(Customer& agent) override;

private:
	float mExitX = 550.0f;
	float mExitY = 762.0f;
};