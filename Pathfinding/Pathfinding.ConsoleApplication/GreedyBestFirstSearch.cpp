#include "pch.h"
#include "GreedyBestFirstSearch.h"
#include <queue>


namespace Pathfinding
{

	std::deque<std::shared_ptr<Library::Node>> Pathfinding::GreedyBestFirstSearch::FindPath(
		std::shared_ptr<Library::Node> start,
		std::shared_ptr<Library::Node> end,
		std::set<std::shared_ptr<Library::Node>>& closedSet)
	{
		// the untamed frontier
		std::priority_queue<std::shared_ptr<Library::Node>> frontier;
		
		// adding the start node to the frontier
		start->SetParent(nullptr);
		start->SetHeuristic(0.0f);
		frontier.push(start);

		while (!frontier.empty())
		{
			// select the nest node based off of their Heuristics
			std::shared_ptr<Library::Node> currentNode = frontier.top();
			frontier.pop();

			// add to visited set
			closedSet.insert(currentNode);

			// is this end?
			if (currentNode == end) break;

			// que up the next neighbors
			for (const auto& weakNeighbor : currentNode->Neighbors())
			{
				auto neighbor = weakNeighbor.lock();
				if (IsValidLocation(neighbor, closedSet))
				{
					neighbor->SetParent(currentNode);
					neighbor->SetHeuristic(CalculateHeuristic(neighbor, end));
					frontier.push(neighbor);
				}
			}
		}

		// the end result
		std::deque<std::shared_ptr<Library::Node>> thePath;

		// see if we found the end node
		if (closedSet.find(end) != closedSet.end())
		{
			std::shared_ptr<Library::Node> currentNode = end;

			while (currentNode->Parent().lock() != nullptr)
			{
				thePath.push_front(currentNode);
				currentNode = currentNode->Parent().lock();
			}
		}

		return thePath;
	}


	

}