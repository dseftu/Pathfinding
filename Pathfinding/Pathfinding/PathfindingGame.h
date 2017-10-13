#pragma once
#include "Game.h"
#include <vector>
#include <GridHelper.h>
#include "Tile.h"
#include <set>

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
		virtual void Shutdown() override;
		virtual void Update(const Library::GameTime& gameTime) override;		
		virtual void Draw(const Library::GameTime& gameTime) override;
	protected:


	private:
		void Exit();
		
		static DirectX::XMVECTORF32 BackgroundColor;

		std::shared_ptr<Library::KeyboardComponent> mKeyboard;
		std::shared_ptr<Library::ImGuiComponent> mImGui;
		std::vector<std::shared_ptr<Pathfinding::Tile>> mTiles;

		Library::Graph mGraph;
		int32_t mGraphWidth;
		int32_t mGraphHeight;
		Library::Point mStartPoint = Library::Point(0,6);
		Library::Point mEndPoint = Library::Point(9, 2);
		Algorithm mAlgorithm = Algorithm::BreadthFirstSearch;
		void ChangeAlgorithm();
		void ChangeAlgorithmHeuristic();
		int32_t mNumberVisited = 0;
		int64_t mTimeToComputeInMs = 0;

		std::string mNumberVisitedText = "0";
		std::string mAlgorithmName = "Breadth-First Search";
		std::string mGridName = "Grid.grid";
		std::string mAlgorithmHeuristic = "Manhattan Distance";
		

		std::deque<std::shared_ptr<Library::Node>> thePath;
		
	};
}