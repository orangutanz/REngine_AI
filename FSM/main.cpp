#include <REngine.h>
#include <String>

#include "AI.h"

#include "Farmer.h"
#include "Crop.h"
#include "Well.h"

namespace
{
	std::unique_ptr<AI::AIWorld> world;
	std::unique_ptr<Farmer> farmer;
	std::unique_ptr<Well> well;
	std::unique_ptr<Crop> Crop1;
	std::unique_ptr<Crop> Crop2;
	std::unique_ptr<Crop> Crop3;
	std::vector<std::unique_ptr<Crop>> crops;

}

void GameInint()
{
	world = std::make_unique<AI::AIWorld>();
	farmer = std::make_unique<Farmer>(*world.get());
	farmer->Load();
	farmer.get()->posX = 100;
	farmer.get()->posY = 300;
	
	well = std::make_unique<Well>(*world.get());
	well->Load();
	well.get()->posX = 300;
	well.get()->posY = 300;

	Crop1 = std::make_unique<Crop>(*world.get());
	Crop1->Load();
	Crop1.get()->posX = 300;
	Crop1.get()->posY = 600;
	Crop1->SetWater(60);
	Crop2 = std::make_unique<Crop>(*world.get());
	Crop2->Load();
	Crop2.get()->posX = 500;
	Crop2.get()->posY = 600;
	Crop1->SetWater(80);
	Crop3 = std::make_unique<Crop>(*world.get());
	Crop3->Load();
	Crop3.get()->posX = 700;
	Crop3.get()->posY = 600;


}

bool GameUpdate()
{
	float deltaTime = GetFrameTime();
	farmer->Update(deltaTime);
	farmer->Render();
	well->Update(deltaTime);
	well->Render();

	Crop1->Update(deltaTime);
	Crop1->Render();
	Crop2->Update(deltaTime);
	Crop2->Render();
	Crop3->Update(deltaTime);
	Crop3->Render();

	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return isStopped;

}

void GameCleanup()
{

}

void RenderDebugUI()
{

}

int main()
{
	REng::Start("FSM");
	GameInint();
	REng::Run(GameUpdate, RenderDebugUI);
	GameCleanup();
	REng::Stop();
	return 0;
}
