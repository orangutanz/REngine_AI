#pragma once
#include <vector>
#include <REngine.h>


class Tilemap
{
public:
	void LoadTileMpa(const char* tileMap, int tileSize);
	void LoadFiles(const char mapPath);
	void Render();

private:
	std::vector<int> mTIleMap;
	std::vector<Texture2D> mTileMapTextures;
	int mRows;
	int mColums;
	int mHeight;
	int mWidth;
};
