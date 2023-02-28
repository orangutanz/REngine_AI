#include "Crop.h"
#include "TypeId.h"


Crop::Crop(AI::AIWorld& world)
	:Entity(world, Types::CropID)
{}

void Crop::Load()
{
	std::string cropFullPath;
	REng::ResourcesFullPath("Corn.png", cropFullPath);
	mTexture = LoadTexture(cropFullPath.c_str());
}

void Crop::Unload()
{
}

void Crop::Update(float deltaTime)
{
	if (mWater > 0)
	{
		mWater -= mDryingSpeed;

		DrawText(std::to_string(mWater).c_str(), posX + 50, posY - 150.f, 24, WHITE);
	}

}

void Crop::Render()
{
	DrawTexture(mTexture, posX, posY, WHITE);
}