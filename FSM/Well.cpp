#include "Well.h"
#include "TypeId.h"


Well::Well(AI::AIWorld& world)
	:Entity(world, Types::WellID)
{}

void Well::Load()
{
	std::string WellFullPath;
	REng::ResourcesFullPath("Well.png", WellFullPath);
	mTexture = LoadTexture(WellFullPath.c_str());
}

void Well::Unload()
{
}

void Well::Update(float deltaTime)
{
}

void Well::Render()
{
	DrawTexture(mTexture, posX - mTexture.width * 0.5f, posY - mTexture.height * 0.5f, WHITE);
}