#include "pch.h"
#include "AStar.h"


namespace Pathfinding
{
	AStar::AStar()
	{
		SetHeuristicsType(HeuristicsType::EuclidianDistance);
	}
}