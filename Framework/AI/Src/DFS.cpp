#pragma once
#include "stdafx.h"
#include "Precompiled.h"
#include "DFS.h"

using namespace AI;


bool DFS::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY)
{
	//Reset everything
	graph.ResetSearchParameters();
	mOpenList.clear();
	mClosedList.clear();

	bool found = false;

	auto endNode = graph.GetNode(endX, endY);
	//add the start node to the opem list
	auto node = graph.GetNode(startX, startY);
	mOpenList.push_back(node);
	node->opened = true;

	while (!found && !mOpenList.empty())
	{
		node = mOpenList.front();
		node->closed = true;
		mClosedList.push_back(node);
		mOpenList.pop_front();

		for (auto i : node->neighbors)
		{
			if (i == nullptr)
			{
				continue;
			}
			//found node
			if (i == endNode)
			{
				i->parent = node;
				mClosedList.push_back(i);
				return true;
			}
			if (!i->closed && !i->opened)// new node
			{
				i->parent = node;
				i->opened = true;
				mOpenList.push_front(i);
			}
		}
	}
	return found;
}