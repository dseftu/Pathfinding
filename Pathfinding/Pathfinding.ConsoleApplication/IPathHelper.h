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
		None,
	};

	class IPathHelper
	{
	public:
		IPathHelper();
		virtual HeuristicsType GetHeuristicsType();
		virtual void SetHeuristicsType(HeuristicsType heuristicsType);

	protected:
		const Library::Point dirs[4] = { Library::Point(0,1),
			Library::Point(0,-1),
			Library::Point(1,0),
			Library::Point(-1,0) };
		const bool IsValidLocation(std::shared_ptr<Library::Node> node, std::set<std::shared_ptr<Library::Node>> closedSet);
		virtual float CalculateHeuristic(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end);
		HeuristicsType heuristicType;


	private:
		float CalculateManhattanDistance(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end);
		float CalculateEuclidianDistance(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end);
		

	};
}
