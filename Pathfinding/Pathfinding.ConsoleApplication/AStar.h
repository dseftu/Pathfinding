#pragma once
#include "DijkstrasAlgorithm.h"

namespace Pathfinding
{
	class AStar : public DijkstrasAlgorithm
	{

	public:
		virtual HeuristicsType GetHeuristicsType();
	};

}
