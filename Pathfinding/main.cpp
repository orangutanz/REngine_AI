#include <iostream>
#include <REngine.h>
#include <String>

#include "Actor.h"
#include "TileMap.h"

REng::Math::Vector2 position;
Texture2D myTexture;
TileMap myTileMap;

//initialized game infos
void GameInint()
{
	std::string fullPath;
	REng::ResourcesFullPath("bird.png", fullPath);
	myTexture = LoadTexture(fullPath.c_str());

	myTileMap.LoadTileFiles("DesertTiles.json"); 
	myTileMap.LoadMap("DesertMap.txt"); 
}

//game loop
bool GameUpdate()
{
	//inputs
	if (IsKeyDown(KeyboardKey::KEY_RIGHT))
	{

	}
	if (IsKeyDown(KeyboardKey::KEY_LEFT))
	{

	}
	
	
	DrawTexture(myTexture, position.x, position.y, WHITE);
	
	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	
	return isStopped;
}

void GameCleanup()
{

}

void RenderDebugUI()
{
	ImGui::Begin("DEBUG");
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