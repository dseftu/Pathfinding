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
		UNREFERENCED_PARAMETER(closedSet);
		UNREFERENCED_PARAMETER(start);
		UNREFERENCED_PARAMETER(end);
		// the end result
		std::deque<std::shared_ptr<Library::Node>> thePath;

		return thePath;
	}

}