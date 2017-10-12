#include "pch.h"
#include "GreedyBestFirstSearch.h"
#include <iostream>
#include <queue>


namespace Pathfinding
{

	std::deque<std::shared_ptr<Library::Node>> Pathfinding::GreedyBestFirstSearch::FindPath(
		std::shared_ptr<Library::Node> start,
		std::shared_ptr<Library::Node> end,
		std::set<std::shared_ptr<Library::Node>>& closedSet)
	{
		// the untamed frontier
		//std::priority_queue<std::shared_ptr<Library::Node>, std::vector<std::shared_ptr<Library::Node>>, std::greater<std::shared_ptr<Library::Node>>> frontier;
		std::deque<std::shared_ptr<Library::Node>> frontier;
		//std::set<std::shared_ptr<Library::Node>> frontierSet;
		
		// adding the start node to the frontier
		start->SetParent(nullptr);
		start->SetHeuristic(CalculateHeuristic(start, end));
		frontier.push_back(start);

		while (!frontier.empty())
		{
			// select the nest node based off of their Heuristics
			std::sort(frontier.begin(), frontier.end(), [](const std::shared_ptr<Library::Node> lhs, const std::shared_ptr<Library::Node> rhs) { return lhs->TotalCost() < rhs->TotalCost(); });
			std::shared_ptr<Library::Node> currentNode = frontier.front();
			frontier.pop_front();

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

					if (std::find(frontier.begin(), frontier.end(), neighbor) == frontier.end())
					{
						neighbor->SetHeuristic(CalculateHeuristic(neighbor, end));
						frontier.push_back(neighbor);
					}					
				} 
				else
				{
					std::cout << "Not putting (" << neighbor->Location().X << "," << neighbor->Location().Y << ") in frontier\n";

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