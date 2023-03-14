#include "Kitchen.h"
#include "TypeId.h"


Kitchen::Kitchen(AI::AIWorld& world)
	:Entity(world, Types::KitchenID)
{
	std::string filePath;
	REng::ResourcesFullPath("Kitchen.png", filePath);
	mTexture = LoadTexture(filePath.c_str());
	
	posY = 339;
}


void Kitchen::Load()
{
}

void Kitchen::Unload()
{
}

void Kitchen::Update(float deltaTime)
{

}

void Kitchen::Render()
{
	DrawTexture(mTexture, posX, posY - (mTexture.height / 2) , WHITE);
}

void Kitchen::DebugRender()
{
}
