#pragma once

#include <AI.h>
#include <REngine.h>

class Crop : public AI::Entity
{
public:
	Crop(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	float GetWater() const { return mWater; }
	bool IsDry() const { return mWater < 50.f; }
	void WaterCrop(float amount) { mWater += amount; }
	void SetWater(float amount) { mWater = amount; }

private:
	float mDryingSpeed = 0.01f;
	float mWater = 100.f;
	Texture2D mTexture;
};