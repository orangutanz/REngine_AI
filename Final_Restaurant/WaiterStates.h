#pragma once
#include "Waiter.h"
#include "Customer.h"
#include "Kitchen.h"
/*
Idle,
GetFood,
DeliverFood
*/

class WaiterIdle : public AI::State<Waiter>
{
public:
	void Enter(Waiter& agent) override;
	void Update(Waiter& agent, float deltaTime) override;
	void Exit(Waiter& agent) override;

private:
	float mWaitTime = 1.0f;
	float IdleX = 160;
	float IdleY = 280;
};

class WaiterGetFood : public AI::State<Waiter>
{
public:
	void Enter(Waiter& agent) override;
	void Update(Waiter& agent, float deltaTime) override;
	void Exit(Waiter& agent) override;

private:
	float mWaitTime = 1.0f;
	Kitchen* mKitchen;
};

class WaiterDeliverFood : public AI::State<Waiter>
{
public:
	void Enter(Waiter& agent) override;
	void Update(Waiter& agent, float deltaTime) override;
	void Exit(Waiter& agent) override;

private:
	Customer* mCustomer;
};