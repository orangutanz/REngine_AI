#pragma once
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
		for (int x = 0; x < mColumns; ++x)
		{
			int idx = GetIdx(x, y);
			mNodes[idx].column = x;
			mNodes[idx].row = y;

			mNodes[idx].neighbors[0] = GetNode(x, y - 1);//North
			mNodes[idx].neighbors[1] = GetNode(x, y + 1);//South
			mNodes[idx].neighbors[2] = GetNode(x + 1, y);//East
			mNodes[idx].neighbors[3] = GetNode(x - 1, y);//West
			mNodes[idx].neighbors[4] = GetNode(x + 1, y - 1);//NorthEast
			mNodes[idx].neighbors[5] = GetNode(x - 1, y - 1);//NorthWest
			mNodes[idx].neighbors[6] = GetNode(x + 1, y + 1);//SouthEast
			mNodes[idx].neighbors[7] = GetNode(x - 1, y + 1);//SouthWest
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
