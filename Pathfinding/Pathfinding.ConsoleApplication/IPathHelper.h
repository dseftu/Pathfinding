#pragma once
#include <Point.h>
#include <Node.h>
#include <set>

namespace Pathfinding
{
	class IPathHelper
	{
	public:
		const Library::Point dirs[4] = { Library::Point(0,1),
			Library::Point(0,-1),
			Library::Point(1,0),
			Library::Point(-1,0) };

		const bool IsValidLocation(std::shared_ptr<Library::Node> node, std::set<std::shared_ptr<Library::Node>> closedSet);

	};
}
