#pragma once
#include "Game.h"
#include <vector>
#include <GridHelper.h>
#include "Tile.h"

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
		
	};
}