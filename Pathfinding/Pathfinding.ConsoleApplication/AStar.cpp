#include "pch.h"
#include "AStar.h"


namespace Pathfinding
{

	HeuristicsType Pathfinding::AStar::GetHeuristicsType()
	{
		return HeuristicsType::EuclidianDistance;
	}
}