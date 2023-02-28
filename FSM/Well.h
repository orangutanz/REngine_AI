#pragma once

#include <AI.h>
#include <REngine.h>

class Well : public AI::Entity
{
public:
	Well(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	float GetWater() { return 200.0f; }

private:
	Texture2D mTexture;
};