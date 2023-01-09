#include <fstream>
#include <iostream>
#include <string>
#include "TileMap.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

bool TileMap::LoadMap(const std::string& filePath)
{
	return false;
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

	//add tile infos to tileMap
	auto tileSize = data.value("TileSize", "Not Found!");

	for (auto tile : data["Tiles"])
	{
		cout << "tile: " << tile << endl;

	}
	
	for (auto tile : mTiles)
	{

	}
	

	f.close();
	return true;

}

void TileMap::Render()
{

}