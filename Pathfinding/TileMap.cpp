#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include "TileMap.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;


bool TileMap::LoadMap(const std::string& filePath)
{
	std::ifstream f("..\\Resources\\" + filePath);

	//try to open json file
	if (!f.is_open())
	{
		cout << "LoadMap - Failed! Json file does not open" << endl;
		return false;
	}

	//parse the json raw
	json data = json::parse(f);

	mRows = data.value("Colums", 0);
	mColums = data.value("Rows", 0); 
	for (auto i : data["TileIdx"])
	{
		mMap.push_back(i);
	}
	mMap.size();

	return true;
}

bool TileMap::LoadTileFiles(const std::string& filePath)
{
	std::ifstream f("..\\Resources\\"+ filePath);

	//try to open json file
	if (!f.is_open())
	{
		cout << "LoadTile - Failed! Json file does not open" << endl;
		return false;
	}

	//parse the json raw
	json data = json::parse(f);

	//tileMap does not have image name
	auto imageName = data.value("ImageName", "Not Found!");
	if (imageName == "Not Found!")
	{
		cout << "LoadTile - Failed! ImageName does not found in json file" << endl;
		return false;
	}

	//find image and load texture
	imageName = "..\\Resources\\"+ imageName.append(".png");
	auto imageTexture = LoadTexture(imageName.c_str());	
	mTileMapTextures.emplace_back(imageTexture);
	int textureIdx = mTileMapTextures.size() - 1;

	//add tile infos 
	mTileSize = data.value("TileSize", 0);
	for (auto tile : data["Tiles"])
	{
		Tile newTile;
		newTile.name = tile.value("Name", "TileName");
		std::string name = "name";
		newTile.textureMapIdx = textureIdx;
		newTile.PositionX = tile.value("PositionX", 0);
		newTile.PositionY = tile.value("PositionY", 0);
		newTile.height = tile.value("Height", 0);
		newTile.width = tile.value("Width", 0);
		auto tileType = tile.value("Type", "Not Found!");
		if (tileType == "Solid")
		{
			newTile.type = Solid;
			mSolidTiles.emplace_back(newTile);
		}
		else
		{
			mGroundTiles.emplace_back(newTile);
		}
	}

	f.close();
	return true;
}

bool TileMap::GenerateMap(const int rows, const int colums)
{	
	if (mGroundTiles.empty())
	{
		return false;
	}
	//uniformed randomizer
	std::uniform_int_distribution<std::mt19937::result_type> udist(0, mGroundTiles.size()-1);
	std::mt19937 rng;
	std::random_device rd;
	rng.seed(rd());

	mMap.clear();
	mRows = rows;
	mColums = colums;
	for (int i = 0; i < mRows; ++i)
	{
		for (int j = 0; j < mColums; ++j)
		{
			mMap.push_back(udist(rng));
		}
	}
	return true;
}

void TileMap::Render()
{
	Vector2 tilePos = { 0.0f , 0.0f };
	Rectangle rec;
	int mapIdx = 0;

	for (int i = 0; i < mRows; ++i)
	{
		for (int j = 0; j < mColums; ++j)
		{
			tilePos = { (float)j * mTileSize,(float)i * mTileSize };
			int tileIdx = mMap[mapIdx];
			Tile tile = mGroundTiles[tileIdx];
			rec.x = tile.PositionX;
			rec.y = tile.PositionY;
			rec.width = tile.width;
			rec.height = tile.height;

			DrawTextureRec(mTileMapTextures[tile.textureMapIdx], rec, tilePos, WHITE);
			mapIdx++;
		}
	}

	//DrawLine()
	
}

void TileMap::DebugRender()
{

}