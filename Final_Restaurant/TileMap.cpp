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
		else if (tileType == "Object")
		{
			newTile.type = Object;
			mObjectTiles.emplace_back(newTile);

		}
		else
		{
			mGroundTiles.emplace_back(newTile);
		}
	}

	f.close();
	return true;
}

bool TileMap::GenerateMap(const int rows, const int colums, const int tileSize)
{
	//Initialize empty grid
	mGridBasedGraph.Initialize(colums, rows);
	mColums = colums;
	mRows = rows;
	mTileSize = tileSize;

	//for()
	//	for()
	//		//Connect the nodes to it's neighbors
	//		mGridBasedGraph.GetNode(4, 5)->neighbors[AI::GridBasedGraph::Directions::East] = mGridBasedGraph.GetNode(5, 5);

	//auto GetNeighbor = [&](int x, int y) -> GridBasedGraph::Node*
	//{
	//	auto node = mGridBasedGraph.GetNode(x, y);
	//
	//	if (node == nullptr)
	//		return nullptr;
	//
	//	if (IsBlocked(x, y))
	//		return nullptr;
	//
	//	return node;
	//};


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
	//for (auto node : mClosedList)
	//{
	//	if (node->parent)
	//	{
	//		REng::Math::Vector2 startPos = GetPixelPosition(node->parent->column, node->parent->row);
	//		REng::Math::Vector2 endPos = GetPixelPosition(node->column, node->row);
	//		DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, RED);
	//	}
	//}
	for (auto i : path)
	{
		DrawCircle(i.x , i.y, 16, GREEN);
	}

}

void TileMap::RenderGrid(Color color)
{
	for (int i = 0;i < mGridBasedGraph.GetColumns();++i)
	{
		for (int j = 0; j < mGridBasedGraph.GetRows(); ++j)
		{
			auto node = mGridBasedGraph.GetNode(j, i);
			if (node == nullptr)
			{
				continue;
			}
			for (auto n : node->neighbors)
			{
				if (n == nullptr)
				{
					continue;
				}
				REng::Math::Vector2 startPos = GetPixelPosition(node->column, node->row);
				REng::Math::Vector2 endPos = GetPixelPosition(n->column, n->row);
				DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, color);				
			}
		}
	}

}

bool TileMap::IsBlocked(int x, int y) const
{
	//Check index pos is blocked
	return false;
}

std::vector<REng::Math::Vector2> TileMap::FindPathBFS(float startX, float startY, float endX, float endY)
{
	std::vector<REng::Math::Vector2> path;
	auto startIdx = GetIndexPosition(startX, startY);
	auto endIdx = GetIndexPosition(endX, endY);

	BFS bfs;
	if (bfs.Run(mGridBasedGraph, startIdx[0] , startIdx[1], endIdx[0], endIdx[1]))
	{
		mClosedList = bfs.GetClosedList();
		auto node = mClosedList.back();
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

std::vector<REng::Math::Vector2> TileMap::FindPathDFS(float startX, float startY, float endX, float endY)
{
	std::vector<REng::Math::Vector2> path;
	auto startIdx = GetIndexPosition(startX, startY);
	auto endIdx = GetIndexPosition(endX, endY);

	DFS dfs;
	if (dfs.Run(mGridBasedGraph, startIdx[0], startIdx[1], endIdx[0], endIdx[1]))
	{
		mClosedList = dfs.GetClosedList();
		auto node = mClosedList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
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

void TileMap::DrawObejctTile(int idx, float x, float y)
{
	if (idx > -1 && idx < mObjectTiles.size())
	{
		Rectangle rec;
		Tile tile = mObjectTiles[idx];
		rec.x = tile.PositionX;
		rec.y = tile.PositionY;
		rec.width = tile.width;
		rec.height = tile.height;

		DrawTextureRec(mTileMapTextures[tile.textureMapIdx], rec, { x,y }, WHITE);
	}
}

REng::Math::Vector2 TileMap::GetPixelPosition(int index_X, int index_Y) const
{
	return { (index_X + 0.5f) * mTileSize ,(index_Y + 0.5f) * mTileSize };
}


std::vector<int> TileMap::GetIndexPosition(float pixel_x, float pixel_y) 
{
	float width = GetWidth();
	float height = GetHeight();
	int index_X = pixel_x / width * mColums;	
	int index_Y = pixel_y / height * mRows;
	return { index_X,index_Y };
}
