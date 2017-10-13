#pragma once
#include "DijkstrasAlgorithm.h"

namespace Pathfinding
{
	class AStar : public DijkstrasAlgorithm
	{

	public:
		AStar();
		AStar(HeuristicsType heuristicsType);
	private:
	};

}
