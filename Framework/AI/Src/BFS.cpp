#pragma once
#include "stdafx.h"
#include "Precompiled.h"
#include "BFS.h"

using namespace AI;

bool BFS::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY)
{
	//Reset everything
	graph.ResetSearchParameters();
	mOpenList.clear();
	mClosedList.clear();

	bool found = false;

	auto endNode = graph.GetNode(endX, endX);
	//add the start node to the opem list
	auto node = graph.GetNode(startX, startY);
	mOpenList.push_back(node);
	node->opened = true;

	//TODO
	//		while end node not reached && open list isn't empty:
	//			select node N from open list ----> Depend on your startegy
	//			if node is end
	//				found = true
	//			else expand node N :
	//				if expanded node isn't in open list nor closed list
	//					add expanded node to open list, set parent
	//			Add node N to closed list

	while (!found && !mOpenList.empty())
	{
		node = mOpenList.front();
		node->closed = true;
		mClosedList.push_back(node);
		mOpenList.pop_front();

		for (auto i : node->neighbors)
		{
			if(i == nullptr)
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
			if(!i->closed && !i->opened)// new node
			{
				i->parent = node;
				i->opened = true;
				mOpenList.push_back(i);
			}
		}
	}
	return found;
}