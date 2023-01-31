#include <iostream>
#include <REngine.h>
#include <String>

#include "Actor.h"
#include "TileMap.h"

REng::Math::Vector2 birdPosition;
Texture2D BirdTexture;
REng::Math::Vector2 goalPosition;
Tile goalTile;
TileMap myTileMap;
std::vector<REng::Math::Vector2> debugPath;


//initialized game infos
void GameInint()
{
	std::string fullPath;
	REng::ResourcesFullPath("bird32.png", fullPath);
	BirdTexture = LoadTexture(fullPath.c_str());

	myTileMap.LoadTileFiles("DesertTiles.json"); 
	//myTileMap.LoadMap("DesertMap.json"); 
	myTileMap.GenerateMap(20, 30);
}

//game loop
bool GameUpdate()
{
	//inputs

	myTileMap.Render();
	myTileMap.RenderPath(debugPath);
	
	DrawTexture(BirdTexture, birdPosition.x, birdPosition.y, WHITE);
	myTileMap.DrawSolidTile(2, goalPosition.x, goalPosition.y);

	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	
	return isStopped;
}

void GameCleanup()
{

}

void RenderDebugUI()
{
	ImGui::Begin("DEBUG");

	ImGui::SliderFloat("Start X", &birdPosition.x, 1.f, myTileMap.GetWidth()-32);
	ImGui::SliderFloat("Start Y", &birdPosition.y, 1.f, myTileMap.GetHeight()-32);

	ImGui::SliderFloat("End X", &goalPosition.x, 1.f, myTileMap.GetWidth()-32);
	ImGui::SliderFloat("End Y", &goalPosition.y, 1.f, myTileMap.GetHeight()-32);
	if (ImGui::Button("Reset Path"))
	{
		debugPath.clear();
	}
	if (ImGui::Button("Run BFS"))
	{
		
		int startX = birdPosition.x;
		int startY = birdPosition.y;
		int endX = goalPosition.x;
		int endY = goalPosition.y;
		debugPath = myTileMap.FindPathBFS(startX, startY, endX, endY);
	}

	ImGui::End();
}

int main()
{
	REng::Start("Pathfinding");
	GameInint();
	REng::Run(GameUpdate,RenderDebugUI);
	GameCleanup();
	REng::Stop();
	return 0;
}