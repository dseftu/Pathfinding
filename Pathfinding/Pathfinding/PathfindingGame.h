#pragma once
#include "Game.h"
#include <GridHelper.h>
#include "Tile.h"
#include <IPathFinder.h>
#include "Rectangle.h"
#include "..\Pathfinding.ConsoleApplication\IPathHelper.h"
#include "..\Pathfinding.ConsoleApplication\BreadthFirstSearch.h"
#include "..\Pathfinding.ConsoleApplication\AStar.h"
#include "..\Pathfinding.ConsoleApplication\DijkstrasAlgorithm.h"
#include "..\Pathfinding.ConsoleApplication\GreedyBestFirstSearch.h"
#include <ImGui\imgui_impl_dx11.h>

namespace Library
{
	class KeyboardComponent;
}

namespace Pathfinding
{
	enum class Algorithm
	{
		BreadthFirstSearch = 1,
		GreedyBestFirst = 2,
		Dijkstras = 3,
		AStar = 4,
	};

	class PathfindingGame : public Library::Game
	{
	public:
		PathfindingGame(std::function<void*()> getWindowCallback, std::function<void(SIZE&)> getRenderTargetSizeCallback);

		virtual void Initialize() override;
		void DrawGrid();
		void ClearOutOldTiles();
		void PerformSearch(std::shared_ptr<Library::IPathFinder> &search, std::shared_ptr<Library::Node> &startNode, std::shared_ptr<Library::Node> &endNode, std::set<std::shared_ptr<Library::Node>> &closedSet);
		void CreateSearchFunction(std::shared_ptr<Library::IPathFinder> &search);
		void ConstructTiles();
		virtual void Shutdown() override;
		virtual void Update(const Library::GameTime& gameTime) override;		
		virtual void Draw(const Library::GameTime& gameTime) override;	
		
	private:
		// ***** CHANGE THIS TO CHANGE THE GRID ***** //
		std::string mGridName = "Grid.grid";
		//std::string mGridName = "NoPathGrid.grid";
		//std::string mGridName = "SuperGrid.grid";
		Library::Point mStartPoint = Library::Point(0, 6);
		Library::Point mEndPoint = Library::Point(9, 2);

		void Exit();
		bool ValidNodePositions();
		static DirectX::XMVECTORF32 BackgroundColor;

		std::shared_ptr<Library::KeyboardComponent> mKeyboard;
		std::shared_ptr<Library::ImGuiComponent> mImGui;
		std::vector<std::shared_ptr<Pathfinding::Tile>> mTiles;

		Library::Graph mGraph;
		int32_t mGraphWidth;
		int32_t mGraphHeight;
		
		void ChangeAlgorithm();
		void ChangeAlgorithmHeuristic();
		int32_t mNumberVisited = 0;
		int64_t mTimeToComputeInMs = 0;
		HeuristicsType mHeuristicsType = HeuristicsType::ManhattanDistance;
		Algorithm mAlgorithm = Algorithm::BreadthFirstSearch;
		std::string mNumberVisitedText = "0";
		std::string mAlgorithmName = "Breadth-First Search";		
		std::string mAlgorithmHeuristicName = "Manhattan Distance";
		bool mPathFound = true;

		std::deque<std::shared_ptr<Library::Node>> thePath;		
	};
}