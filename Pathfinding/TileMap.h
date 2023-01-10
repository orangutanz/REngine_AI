#pragma once
#include <REngine.h>
#include <AI.h>

enum TileType
{
	Ground,
	Solid
};

struct Tile
{
	std::string name = "name";
	int textureMapIdx;
	int PositionX;
	int PositionY;
	int height;
	int width;
	TileType type;
};


class TileMap
{
public:
	bool LoadMap(const std::string& filePath);
	bool LoadTileFiles(const std::string& filePath);
	bool GenerateMap(const int rows, const int colums);
	void Render();
	void DebugRender();

private:
	std::vector<int> mMap;
	std::vector<Tile> mGroundTiles;
	std::vector<Tile> mSolidTiles;
	std::vector<Texture2D> mTileMapTextures;

	int mRows;
	int mColums;
	int mTileSize;
};
