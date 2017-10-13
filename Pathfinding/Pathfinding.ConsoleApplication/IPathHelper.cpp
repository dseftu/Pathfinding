#include "pch.h"
#include <GridHelper.h>
#include "IPathHelper.h"
#include <cmath>

namespace Pathfinding
{
	IPathHelper::IPathHelper()
	{
		SetHeuristicsType(HeuristicsType::None);
	}

	const bool Pathfinding::IPathHelper::IsValidLocation(std::shared_ptr<Library::Node> node, std::set<std::shared_ptr<Library::Node>> closedSet)
	{
		// this determines if the node is normal and not in the closed set
		return !IsWall(node) && !Visited(node, closedSet);
	}
	const bool IPathHelper::IsWall(std::shared_ptr<Library::Node> node)
	{
		return (node->Type() == Library::NodeType::Wall);
	}
	const bool IPathHelper::Visited(std::shared_ptr<Library::Node> node, std::set<std::shared_ptr<Library::Node>> closedSet)
	{
		return (closedSet.find(node) != closedSet.end());
	}
	float IPathHelper::CalculateHeuristic(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end)
	{
		if (this->GetHeuristicsType() == HeuristicsType::ManhattanDistance)
		{
			return (CalculateManhattanDistance(start, end));
		}
		else if (this->GetHeuristicsType() == HeuristicsType::EuclidianDistance)
		{
			return (CalculateEuclidianDistance(start, end));
		}
		else
		{
			return 0.0;
		}

	}
	HeuristicsType IPathHelper::GetHeuristicsType()
	{
		return mHeuristicType;
	}
	void IPathHelper::SetHeuristicsType(HeuristicsType heuristicsType)
	{
		mHeuristicType = heuristicsType;
	}
	float IPathHelper::CalculateManhattanDistance(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end)
	{			
		return float(std::abs(start->Location().X - end->Location().X) + std::abs(start->Location().Y - end->Location().Y));
		
	}
	float IPathHelper::CalculateEuclidianDistance(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end)
	{
		float a = float(std::abs(start->Location().X - end->Location().X));
		float b = float(std::abs(start->Location().Y - end->Location().Y));
		return float(std::sqrt(std::pow(a, 2.0) + std::pow(b, 2.0)));
	}
}