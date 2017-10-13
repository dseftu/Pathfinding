#pragma once
#include <Point.h>
#include <Node.h>
#include <set>
#include <queue>

namespace Pathfinding
{
	enum class HeuristicsType
	{
		ManhattanDistance = 0,
		EuclidianDistance = 1,
		None = 2,
	};

	class IPathHelper
	{
	public:
		IPathHelper();
		virtual HeuristicsType GetHeuristicsType();
		virtual void SetHeuristicsType(HeuristicsType heuristicsType);
		const std::function<bool(std::shared_ptr<Library::Node>, std::shared_ptr<Library::Node>)> valueComp = [](const std::shared_ptr<Library::Node> lhs, const std::shared_ptr<Library::Node> rhs) { return lhs->TotalCost() > rhs->TotalCost(); };
	protected:
		const Library::Point dirs[4] = { Library::Point(0,1),
			Library::Point(0,-1),
			Library::Point(1,0),
			Library::Point(-1,0) };
		const bool IsValidLocation(std::shared_ptr<Library::Node> node, std::set<std::shared_ptr<Library::Node>> closedSet);
		const bool IsWall(std::shared_ptr<Library::Node> node);
		const bool Visited(std::shared_ptr<Library::Node> node, std::set<std::shared_ptr<Library::Node>> closedSet);
		virtual float CalculateHeuristic(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end);
		HeuristicsType mHeuristicType;

	private:
		float CalculateManhattanDistance(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end);
		float CalculateEuclidianDistance(std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end);
		
	};
}
