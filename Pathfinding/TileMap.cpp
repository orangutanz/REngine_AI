#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include "TileMap.h"
#include "json.hpp"

using namespace std;
using namespace AI;
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


	//Implement this 
	//TODO
	mGridBasedGraph.Initialize(mColums, mRows);

	//for()
	//	for()
	//		//Connect the nodes to it's neighbors
	//		mGridBasedGraph.GetNode(4, 5)->neighbors[AI::GridBasedGraph::Directions::East] = mGridBasedGraph.GetNode(5, 5);

	auto GetNeighbor = [&](int x, int y) -> GridBasedGraph::Node*
	{
		auto node = mGridBasedGraph.GetNode(x, y);

		if (node == nullptr)
			return nullptr;

		if (IsBlocked(x, y))
			return nullptr;

		return node;
	};


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

	
}

void TileMap::RenderPath(std::vector<REng::Math::Vector2>& path)
{
	for (auto i : path)
	{
		DrawCircle(i.x, i.y, 16, GREEN);
	}

}

bool TileMap::IsBlocked(int x, int y) const
{

	return false;
}

std::vector<REng::Math::Vector2> TileMap::FindPathBFS(int startX, int startY, int endX, int endY)
{
	std::vector<REng::Math::Vector2> path;
	NodeList closedList;

	BFS bfs;
	if (bfs.Run(mGridBasedGraph, startX /32, startY /32, endX /32, endY /32))
	{
		closedList = bfs.GetClosedList();
		auto node = closedList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}
	else
	{
		mClosedList = bfs.GetClosedList();
	}

	return path;
}

void TileMap::DrawSolidTile(int idx, float x, float y)
{
	if (idx > -1 && idx < mSolidTiles.size())
	{
		Rectangle rec;
		Tile tile = mSolidTiles[idx];
		rec.x = tile.PositionX;
		rec.y = tile.PositionY;
		rec.width = tile.width;
		rec.height = tile.height;

		DrawTextureRec(mTileMapTextures[tile.textureMapIdx], rec, {x,y}, WHITE);
	}
}

REng::Math::Vector2 TileMap::GetPixelPosition(int x, int y) const
{
	return { x * 32.f,y * 32.f };
}
