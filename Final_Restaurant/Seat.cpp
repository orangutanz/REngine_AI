#include "Seat.h"
#include "TypeId.h"


Seat::Seat(AI::AIWorld& world)
	:Entity(world, Types::SeatID)
{
	std::string filePath;
	REng::ResourcesFullPath("Food.png", filePath);
	mTexture = LoadTexture(filePath.c_str());
}

void Seat::Load()
{
}

void Seat::Unload()
{
}

void Seat::Update(float deltaTime)
{

}

void Seat::Render()
{
	if (mFood)
	{
		auto offsetX = mTexture.width / 2;
		auto offsetY = mTexture.height / 2;
		DrawTexture(mTexture, posX - offsetX, posY - offsetY, WHITE);
	}
}

void Seat::DebugRender()
{
	//DrawCircle(posX, posY, 16, YELLOW);
}
