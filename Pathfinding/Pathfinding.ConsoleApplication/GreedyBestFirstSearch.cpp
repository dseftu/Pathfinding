#include "pch.h"
#include "GreedyBestFirstSearch.h"

namespace Pathfinding
{
	GreedyBestFirstSearch::GreedyBestFirstSearch()
	{
		SetHeuristicsType(HeuristicsType::ManhattanDistance);
	}
	GreedyBestFirstSearch::GreedyBestFirstSearch(HeuristicsType heuristicsType)
	{
		SetHeuristicsType(heuristicsType);
	}

	std::deque<std::shared_ptr<Library::Node>> Pathfinding::GreedyBestFirstSearch::FindPath(
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
		frontier.push_back(start);
		std::push_heap(frontier.begin(), frontier.end(), valueComp);

		while (!frontier.empty())
		{
			// select the best node based off of their Heuristics
			std::pop_heap(frontier.begin(), frontier.end(), valueComp);			
			auto currentNode = frontier.back();
			frontier.pop_back();	
			
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

					// check to see if we've already added this node to the frontier
					if (std::find(frontier.begin(), frontier.end(), neighbor) == frontier.end())
					{
						neighbor->SetHeuristic(CalculateHeuristic(neighbor, end));
						frontier.push_back(neighbor);
						std::push_heap(frontier.begin(), frontier.end(), valueComp);
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
			// we found it!  Let's follow the breadcrumbs and build the path.
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