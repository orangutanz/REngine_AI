#pragma once

#include "EMath.h"

namespace AI
{
	class Agent;
	class SteeringBehavior
	{
	public:
		virtual ~SteeringBehavior() = default;

		virtual EMath::Vector2 Calculate(Agent& agent) = 0;

		void SetActive(bool active) { mActive = active; }
		bool IsActive() const { return mActive; }

		void ShowDebug(bool debug) { mDebug = debug; }
		bool IsDebug() const { return mDebug; }

		void SetWeight(float weight) { mWeight = weight; }
		float GetWeight() const { return mWeight; }

	private:
		bool mActive = false;
		bool mDebug = false;
		float mWeight = 1.0f;
	};
}