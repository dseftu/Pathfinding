#include "pch.h"
#include "DijkstrasAlgorithm.h"
#include <queue>
#include <iostream>


namespace Pathfinding
{
	DijkstrasAlgorithm::DijkstrasAlgorithm()
	{
		SetHeuristicsType(HeuristicsType::None);
	}
	std::deque<std::shared_ptr<Library::Node>> Pathfinding::DijkstrasAlgorithm::FindPath(
		std::shared_ptr<Library::Node> start,
		std::shared_ptr<Library::Node> end,
		std::set<std::shared_ptr<Library::Node>>& closedSet)
	{
		// the untamed frontier
		std::deque<std::shared_ptr<Library::Node>> frontier;

		// adding the start node to the frontier
		start->SetParent(nullptr);
		start->SetHeuristic(CalculateHeuristic(start, end));
		start->SetPathCost(0.0f);
		frontier.push_back(start);

		while (!frontier.empty())
		{
			// select the nest node based off of their Heuristics
			std::sort(frontier.begin(), frontier.end(), [](const std::shared_ptr<Library::Node> lhs, const std::shared_ptr<Library::Node> rhs) { return lhs->TotalCost() < rhs->TotalCost(); });
			std::shared_ptr<Library::Node> currentNode = frontier.front();
			frontier.pop_front();

			
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
					bool addToFrontier = false;
					if (!Visited(neighbor, closedSet)) addToFrontier = true;
					else if (newPathCost < neighbor->PathCost())
					{
						std::cout << "Updated cost of " << neighbor->TotalCost() << " to " << newPathCost << "\n";
						addToFrontier = true;
					}

					if (addToFrontier)
					{
						neighbor->SetPathCost(newPathCost);
						neighbor->SetParent(currentNode);
						neighbor->SetHeuristic(CalculateHeuristic(neighbor, end));
						frontier.push_back(neighbor);
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
