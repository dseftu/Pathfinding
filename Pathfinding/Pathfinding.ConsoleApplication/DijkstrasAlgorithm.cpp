#include "pch.h"
#include "DijkstrasAlgorithm.h"


namespace Pathfinding
{
	std::deque<std::shared_ptr<Library::Node>> Pathfinding::DijkstrasAlgorithm::FindPath(
		std::shared_ptr<Library::Node> start,
		std::shared_ptr<Library::Node> end,
		std::set<std::shared_ptr<Library::Node>>& closedSet)
	{
		// the untamed frontier
		std::vector<std::shared_ptr<Library::Node>> frontier;
		std::make_heap(frontier.begin(), frontier.end());

		// adding the start node to the frontier
		start->SetParent(nullptr);
		start->SetHeuristic(CalculateHeuristic(start, end));
		start->SetPathCost(0.0f);
		frontier.push_back(start);
		std::push_heap(frontier.begin(), frontier.end(), valueComp);


		while (!frontier.empty())
		{
			// select the best node based off of their Heuristics
			std::pop_heap(frontier.begin(), frontier.end(), valueComp);
			auto currentNode = frontier.back();
			frontier.pop_back();
			
			// is this end?
			if (currentNode == end)
			{
				// add to visited set
				closedSet.insert(currentNode);
				break;
			}
			

			// que up the next neighbors
			for (const auto& weakNeighbor : currentNode->Neighbors())
			{
				auto neighbor = weakNeighbor.lock();
				if (!IsWall(neighbor))
				{
					// determine path cost					
					float newPathCost = currentNode->PathCost() + 1.0f;
					
					// if in visited and new cost is less or not in visited, do the things
					if (!Visited(neighbor, closedSet) || newPathCost < neighbor->PathCost()) 
					{
						neighbor->SetPathCost(newPathCost);
						neighbor->SetParent(currentNode);
						neighbor->SetHeuristic(CalculateHeuristic(neighbor, end));

						if (std::find(frontier.begin(), frontier.end(), neighbor) == frontier.end())
						{
							frontier.push_back(neighbor);
							std::push_heap(frontier.begin(), frontier.end(), valueComp);
						}
						else
						{
							std::make_heap(frontier.begin(), frontier.end(), valueComp);
						}

					}
					
				}
			}

			// add to visited set
			closedSet.insert(currentNode);
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
