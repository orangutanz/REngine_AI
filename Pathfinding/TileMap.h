#pragma once
#include <vector>
#include <REngine.h>

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
	void Render();

private:
	std::vector<int> mMap;
	std::vector<Tile> mTiles;
	std::vector<Texture2D> mTileMapTextures;
	int mRows;
	int mColums;
};
