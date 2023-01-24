#include "stdafx.h"
#include "Precompiled.h"
#include "GridBasedGraph.h"

using namespace AI;

void GridBasedGraph::Initialize(int columns, int rows)
{
	//TODO
	//Resize mNodes to the matching dimension
	//for each node, set it's attributes (row / collumn)
	mRows = rows;
	mColumns = columns;
	mNodes.resize(mRows * mColumns);

	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mRows; ++x)
		{
			mNodes[GetIdx(x, y)].column = x;
			mNodes[GetIdx(x, y)].row = y;
		}
	}
}

void AI::GridBasedGraph::ResetSearchParameters()
{
	for (auto& node : mNodes)
	{
		node.parent = nullptr;
		node.opened = false;
		node.closed = false;
	}
}

GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y)
{
	if (x < 0 || x >= mColumns || y < 0 || y >= mRows)
	{
		return nullptr;
	}
	const int index = GetIdx(x, y);
	return &mNodes[index];
}

const GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y) const
{
	if (x < 0 || x >= mColumns || y < 0 || y >= mRows)
	{
		return nullptr;
	}
	const int index = GetIdx(x, y);
	return &mNodes[index];
}

int GridBasedGraph::GetIdx(int x, int y) const
{
	return x + (y * mColumns);
}
