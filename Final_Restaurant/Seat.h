#pragma once

#include <AI.h>
#include <REngine.h>

class Seat : public AI::Entity
{
public:
	Seat(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();
	void DebugRender();

	bool IsOccupied() const { return mOccupied; }
	void SetOccupied(bool seat) { mOccupied = seat; }
	void SetDrawFood(bool food) { mFood = food; }

private:
	bool mOccupied = false;
	bool mFood = false;
	Texture2D mTexture;
};