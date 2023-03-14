#pragma once
#include <REngine.h>
#include <AI.h>

enum TileType
{
	Ground,
	Solid,
	Object
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
	bool GenerateMap(const int rows, const int colums, const int tileSize);
	void Render();
	void RenderPath(std::vector<REng::Math::Vector2> &path);
	void RenderGrid(Color color = GRAY);

	bool IsBlocked(int x, int y) const;
	std::vector<REng::Math::Vector2> FindPathBFS(float startX, float startY, float endX, float endY);
	std::vector<REng::Math::Vector2> FindPathDFS(float startX, float startY, float endX, float endY);

	void DrawSolidTile(int idx, float x, float y);
	void DrawObejctTile(int idx, float x, float y);
	float GetWidth() { return mColums * mTileSize; }
	float GetHeight() { return mRows * mTileSize; }

	REng::Math::Vector2 GetPixelPosition(int index_x, int index_y) const;
	std::vector<int> GetIndexPosition(float pixel_x, float pixel_y);


private:

	std::vector<int> mMap;
	std::vector<Tile> mGroundTiles;
	std::vector<Tile> mSolidTiles;
	std::vector<Tile> mObjectTiles;
	std::vector<Texture2D> mTileMapTextures;

	AI::GridBasedGraph mGridBasedGraph;
	AI::NodeList mClosedList;

	
	int mRows;
	int mColums;
	int mTileSize = 32;
};
