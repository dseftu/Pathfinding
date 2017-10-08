#pragma once
#include <Point.h>
#include <Node.h>
#include <set>

namespace Pathfinding
{
	enum class HeuristicsType
	{
		ManhattanDistance,
		EuclidianDistance,
	};

	class IPathHelper
	{
	public:
		IPathHelper();

	protected:
		const Library::Point dirs[4] = { Library::Point(0,1),
			Library::Point(0,-1),
			Library::Point(1,0),
			Library::Point(-1,0) };
		const bool IsValidLocation(std::shared_ptr<Library::Node> node, std::set<std::shared_ptr<Library::Node>> closedSet);
		virtual double CalculateHeuristic(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end);
		HeuristicsType GetHeuristicsType();
		void SetHeuristicsType(HeuristicsType heuristicsType);

	private:
		double CalculateManhattanDistance(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end);
		double CalculateEuclidianDistance(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end);
		HeuristicsType heuristicType;
		

	};
}
