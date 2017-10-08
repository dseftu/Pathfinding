#include "pch.h"
#include <GridHelper.h>
#include "IPathHelper.h"
#include <cmath>

namespace Pathfinding
{
	IPathHelper::IPathHelper()
	{
		SetHeuristicsType(HeuristicsType::ManhattanDistance);
	}

	const bool Pathfinding::IPathHelper::IsValidLocation(std::shared_ptr<Library::Node> node, std::set<std::shared_ptr<Library::Node>> closedSet)
	{
		// this determines if the node is normal and not in the closed set
		return (node->Type() == Library::NodeType::Normal) && (closedSet.find(node) == closedSet.end());
	}
	double IPathHelper::CalculateHeuristic(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end)
	{
		if (this->GetHeuristicsType() == HeuristicsType::ManhattanDistance)
		{
			return (CalculateManhattanDistance(start, end));
		}
		else if (this->GetHeuristicsType() == HeuristicsType::ManhattanDistance)
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
		return this->heuristicType;
	}
	void IPathHelper::SetHeuristicsType(HeuristicsType heuristicsType)
	{
		this->heuristicType = heuristicsType;
	}
	double IPathHelper::CalculateManhattanDistance(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end)
	{			
		return std::abs(start->Location().X - end->Location().X) + std::abs(start->Location().Y - end->Location().Y);
		
	}
	double IPathHelper::CalculateEuclidianDistance(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end)
	{
		double a = std::abs(start->Location().X - end->Location().X);
		double b = std::abs(start->Location().Y - end->Location().Y);
		return std::sqrt(std::pow(a, 2.0) + std::pow(b, 2.0));
	}
}