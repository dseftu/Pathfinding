#pragma once
#include <IPathFinder.h>
#include "IPathHelper.h"

namespace Pathfinding
{
	class DijkstrasAlgorithm : public Library::IPathFinder, public Pathfinding::IPathHelper
	{

	public:
		DijkstrasAlgorithm();
		virtual std::deque<std::shared_ptr<Library::Node>> FindPath(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end, std::set<std::shared_ptr<Library::Node>>& closedSet) override;

	private:
	};

}
