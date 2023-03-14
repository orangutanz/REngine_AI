#include <REngine.h>
#include <String>
#include <fstream>
#include <iostream>
#include <random>

#include "AI.h"
#include "TileMap.h"

#include "Customer.h"
#include "Kitchen.h"
#include "Waiter.h"
#include "Seat.h"

namespace
{
	std::unique_ptr<AI::AIWorld> world;
	std::unique_ptr<Seat> seat1;
	std::unique_ptr<Seat> seat2;
	std::unique_ptr<Seat> seat3;
	std::unique_ptr<Seat> seat4;
	std::unique_ptr<Seat> seat5;
	std::unique_ptr<Seat> seat6;
	std::unique_ptr<Seat> seat7;
	std::unique_ptr<Seat> seat8;
	std::unique_ptr<Seat> seat9;
	std::unique_ptr<Kitchen> kitchen;
	std::unique_ptr<Waiter> waiter;
	std::vector<Customer*> customers;
	std::vector<Texture2D> customerTextures;

	Texture2D BGTexture;
	Texture2D FoodTexture;
	TileMap myTileMap;

	bool RenderGrid = false;

	//uniformed randomizer
	std::mt19937 rng;
	std::random_device rd;
}

// Game functions
void AddCustomer()
{
	for (auto c : customers)
	{
		if (!c->GetActive())
		{
			c->Reset();
			c->SetActive();

			return;
		}
	}
}


void GameInint()
{
	world = std::make_unique<AI::AIWorld>();

	//Seats&Kitchen
	{
		seat1 = std::make_unique<Seat>(*world.get());
		seat1.get()->posX = 232;
		seat1.get()->posY = 262;
		seat2 = std::make_unique<Seat>(*world.get());
		seat2.get()->posX = 554;
		seat2.get()->posY = 260;
		seat3 = std::make_unique<Seat>(*world.get());
		seat3.get()->posX = 744;
		seat3.get()->posY = 386;
		seat4 = std::make_unique<Seat>(*world.get());
		seat4.get()->posX = 300;
		seat4.get()->posY = 644;
		seat5 = std::make_unique<Seat>(*world.get());
		seat5.get()->posX = 874;
		seat5.get()->posY = 266;
		seat6 = std::make_unique<Seat>(*world.get());
		seat6.get()->posX = 360;
		seat6.get()->posY = 389;
		seat7 = std::make_unique<Seat>(*world.get());
		seat7.get()->posX = 104;
		seat7.get()->posY = 516;
		seat8 = std::make_unique<Seat>(*world.get());
		seat8.get()->posX = 1000;
		seat8.get()->posY = 516;
		seat9 = std::make_unique<Seat>(*world.get());
		seat9.get()->posX = 808;
		seat9.get()->posY = 644;
		kitchen = std::make_unique<Kitchen>(*world.get());

	}
	//Customers
	{
		//Assets
		std::string fullPath;
		REng::ResourcesFullPath("CafeBGAsset.png", fullPath);
		BGTexture = LoadTexture(fullPath.c_str());
		Texture2D CTexture;
		REng::ResourcesFullPath("1.png", fullPath);
		CTexture = LoadTexture(fullPath.c_str());
		customerTextures.emplace_back(CTexture);
		REng::ResourcesFullPath("2.png", fullPath);
		CTexture = LoadTexture(fullPath.c_str());
		customerTextures.emplace_back(CTexture);
		REng::ResourcesFullPath("3.png", fullPath);
		CTexture = LoadTexture(fullPath.c_str());
		customerTextures.emplace_back(CTexture);
		REng::ResourcesFullPath("4.png", fullPath);
		CTexture = LoadTexture(fullPath.c_str());
		customerTextures.emplace_back(CTexture);
		REng::ResourcesFullPath("5.png", fullPath);
		CTexture = LoadTexture(fullPath.c_str());
		customerTextures.emplace_back(CTexture);
		REng::ResourcesFullPath("6.png", fullPath);
		CTexture = LoadTexture(fullPath.c_str());
		customerTextures.emplace_back(CTexture);
		for (int i = 0; i < 20; ++i)
		{

			std::uniform_int_distribution<std::mt19937::result_type> randomPos(0, 20);
			rng.seed(rd());
			Customer* newCustomer = new Customer(*world.get());
			newCustomer->posX = 550.0f + randomPos(rng) - 10;
			newCustomer->posY = 762.0f + randomPos(rng) - 10;
			customers.push_back(newCustomer);
			
			//random customer sprite 
			std::uniform_int_distribution<std::mt19937::result_type> udist(0, customerTextures.size() - 1);
			customers.back()->Load(customerTextures.at(udist(rng)));
		}
	}
	//Waiter(s)
	waiter = std::make_unique<Waiter>(*world.get());
	waiter.get()->Load();

	myTileMap.LoadTileFiles("BarTiles.json");
	myTileMap.GenerateMap(16, 24, 64);	


}

bool GameUpdate()
{
	DrawTexture(BGTexture, 0, 0, WHITE);
	float deltaTime = GetFrameTime();
	kitchen.get()->Render();
	//render people
	for (auto c : customers)
	{
		c->Update(deltaTime);
		c->Render();
	}
	waiter.get()->Update(deltaTime);
	waiter.get()->Render();
	//redner ojbects
	{
		seat1.get()->Render();
		seat2.get()->Render();
		seat3.get()->Render();
		seat4.get()->Render();
		seat5.get()->Render();
		seat6.get()->Render();
		seat7.get()->Render();
		seat8.get()->Render();
		seat9.get()->Render();
	}

	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return isStopped;
}

void GameCleanup()
{
	for (auto c : customers)
	{
		delete c;
	}
}

void RenderDebugUI()
{
	if (RenderGrid)
	{
		//myTileMap.RenderGrid(YELLOW);
	}
	seat1.get()->DebugRender();
	seat2.get()->DebugRender();
	seat3.get()->DebugRender();
	seat4.get()->DebugRender();
	seat5.get()->DebugRender();
	seat6.get()->DebugRender();
	seat7.get()->DebugRender();
	seat8.get()->DebugRender();
	seat9.get()->DebugRender();

	ImGui::Begin("DEBUG");
	ImGui::Checkbox("Show Grid", &RenderGrid);
	if (ImGui::Button("Add Customer"))
	{
		AddCustomer();
	}

	ImGui::End();

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
