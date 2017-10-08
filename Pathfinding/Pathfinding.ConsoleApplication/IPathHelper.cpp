#include "pch.h"
#include "IPathHelper.h"

namespace Pathfinding
{
	const bool Pathfinding::IPathHelper::IsValidLocation(std::shared_ptr<Library::Node> node, std::set<std::shared_ptr<Library::Node>> closedSet)
	{
		// this determines if the node is normal and not in the closed set
		return (node->Type() == Library::NodeType::Normal) && (closedSet.find(node) == closedSet.end());
	}
}