#include "pch.h"
#include "PathfindingGame.h"


using namespace std;
using namespace DirectX;
using namespace Library;
using namespace Microsoft::WRL;

IMGUI_API LRESULT ImGui_ImplDX11_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Pathfinding
{
	XMVECTORF32 PathfindingGame::BackgroundColor = Colors::DarkSlateGray;
	PathfindingGame::PathfindingGame(function<void*()> getWindowCallback, function<void(SIZE&)> getRenderTargetSizeCallback) :
		Game(getWindowCallback, getRenderTargetSizeCallback)
	{
	}

	void PathfindingGame::Initialize()
	{
		SpriteManager::Initialize(*this);				
		BlendStates::Initialize(mDirect3DDevice.Get());

		mKeyboard = make_shared<KeyboardComponent>(*this);
		mComponents.push_back(mKeyboard);
		mServices.AddService(KeyboardComponent::TypeIdClass(), mKeyboard.get());
		
		mImGui = make_shared<ImGuiComponent>(*this);
		mComponents.push_back(mImGui);
		mServices.AddService(ImGuiComponent::TypeIdClass(), mImGui.get());
		auto imGuiWndProcHandler = make_shared<UtilityWin32::WndProcHandler>(ImGui_ImplDX11_WndProcHandler);
		UtilityWin32::AddWndProcHandler(imGuiWndProcHandler);

		// we start with drawing a grid since the defaults are known to work.
		DrawGrid();
		
		// controls window
		auto sampleImGuiRenderBlock1 = make_shared<ImGuiComponent::RenderBlock>([this]()
		{
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::Begin("Input Controls");
			static float f = 0.0f;

			// display info about the currently displayed grid
			ImGui::Text(("Grid: " + mGridName).c_str());
			ImGui::Text(("Start: (" + std::to_string(mStartPoint.X) + "," + std::to_string(mStartPoint.Y) + ")").c_str());
			ImGui::SameLine();
			ImGui::Text(("End: (" + std::to_string(mEndPoint.X) + "," + std::to_string(mEndPoint.Y) + ")").c_str());
			ImGui::Text("Adjust Positions: ");
			ImGui::SameLine();
			ImGui::SliderInt4("", &mStartPoint.X, 0, mGraphWidth-1);

			if (!ValidNodePositions()) 
			{				
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Invalid node selections!");
				ImGui::Text("");
				ImGui::Text("");
			}
			else
			{
				// options for changing the algorithm
				if (ImGui::Button("Change Algorithm")) ChangeAlgorithm();
				if (ImGui::Button("Redraw Grid/Repeat Search") && ValidNodePositions()) DrawGrid();
				if (mAlgorithm == Algorithm::GreedyBestFirst || mAlgorithm == Algorithm::AStar)
				{
					if (ImGui::Button("Change Heuristic")) ChangeAlgorithmHeuristic();
					ImGui::SameLine();
					ImGui::Text(("Current: " + mAlgorithmHeuristicName).c_str());
				}
				ImGui::Text("");
			}
			if (!mPathFound)
			{
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "No path found!");
			}


			// Display algorithm name
			std::string algorithmText = "Current algorithm: ";
			algorithmText += mAlgorithmName;			
			ImGui::Text(("Current algorithm: " + mAlgorithmName).c_str());
			
			// runtime evaluations
			ImGui::Text(("Last run time (ms): " + std::to_string(mTimeToComputeInMs)).c_str());
			ImGui::Text(("Nodes visited: " + std::to_string(mNumberVisited)).c_str());
			
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
			
		});
		mImGui->AddRenderBlock(sampleImGuiRenderBlock1);
				
		Game::Initialize();
	}

	void PathfindingGame::DrawGrid()
	{
		ClearOutOldTiles();
		
		// setup to reconstruct the graph
		string filename = ".\\Content\\" + mGridName;
		mGraph = GridHelper::LoadGridFromFile(filename, mGraphWidth, mGraphHeight);
		std::set<std::shared_ptr<Library::Node>> closedSet;
		std::shared_ptr<Library::Node> startNode = mGraph.At(mStartPoint);
		std::shared_ptr<Library::Node> endNode = mGraph.At(mEndPoint);

		// base class for search algorithm
		std::shared_ptr<Library::IPathFinder> search;
		CreateSearchFunction(search);
		
		PerformSearch(search, startNode, endNode, closedSet);

		ConstructTiles();
	}

	void PathfindingGame::CreateSearchFunction(std::shared_ptr<Library::IPathFinder> &search)
	{
		switch (mAlgorithm)
		{
		case (Algorithm::BreadthFirstSearch):
		{
			search = make_shared<Pathfinding::BreadthFirstSearch>();
			break;
		}
		case (Algorithm::GreedyBestFirst):
		{
			search = make_shared<Pathfinding::GreedyBestFirstSearch>(mHeuristicsType);
			break;
		}
		case (Algorithm::Dijkstras):
		{
			search = make_shared<Pathfinding::DijkstrasAlgorithm>();
			break;
		}
		case (Algorithm::AStar):
		{
			search = make_shared<Pathfinding::AStar>(mHeuristicsType);
			break;
		}
		}
	}

	void PathfindingGame::PerformSearch(std::shared_ptr<Library::IPathFinder> &search, std::shared_ptr<Library::Node> &startNode, std::shared_ptr<Library::Node> &endNode, std::set<std::shared_ptr<Library::Node>> &closedSet)
	{
		// clear old path, perform new search and time it
		thePath.clear();
		auto startTime = std::chrono::high_resolution_clock::now();
		thePath = search->FindPath(startNode, endNode, closedSet);
		auto endTime = std::chrono::high_resolution_clock::now();
		auto totalTimeElapsed = endTime - startTime;

		// same evaluation results
		mTimeToComputeInMs = std::chrono::duration_cast<std::chrono::milliseconds>(totalTimeElapsed).count();
		mNumberVisited = closedSet.size();
		if (thePath.size() == 0) mPathFound = false;
		else mPathFound = true;
	}

	void PathfindingGame::ClearOutOldTiles()
	{
		// clear out the old tiles
		for (int32_t i = mComponents.size() - 1; i >= 0; i--)
		{
			if (mComponents.back()->ToString() == "Tile")
			{
				mComponents.back()->Shutdown();
				mComponents.back() = nullptr;
				mComponents.erase(mComponents.begin() + i);
			}
		}
	}

	void PathfindingGame::ConstructTiles()
	{
		// actually draw the thing
		for (int32_t x = 0; x < mGraphWidth; x++)
		{
			for (int32_t y = 0; y < mGraphHeight; y++)
			{
				std::shared_ptr<Tile> mTile;

				if (mStartPoint.X == x && mStartPoint.Y == y)
				{
					mTile = make_shared<Tile>(*this, TileType::Start);
				}
				else if (mEndPoint.X == x && mEndPoint.Y == y)
				{
					mTile = make_shared<Tile>(*this, TileType::End);
				}
				else if (std::find(thePath.begin(), thePath.end(), mGraph.At(x, y)) != thePath.end())
				{
					mTile = make_shared<Tile>(*this, TileType::Path);
				}
				else if (mGraph.At(x, y)->Type() == Library::NodeType::Wall)
				{
					mTile = make_shared<Tile>(*this, TileType::Wall);
				}
				else
				{
					mTile = make_shared<Tile>(*this, TileType::Ground);
				}

				mTile->SetBounds((mTile->Bounds().Width + 5)*x + 450, (mTile->Bounds().Height + 5)*y + 20);
				mComponents.push_back(mTile);
			}
		}
	}

	void PathfindingGame::Shutdown()
	{
		BlendStates::Shutdown();
		SpriteManager::Shutdown();
	}

	void PathfindingGame::Update(const GameTime &gameTime)
	{
		if (mKeyboard->WasKeyPressedThisFrame(Keys::Escape))
		{
			Exit();
		}
		
		Game::Update(gameTime);
	}

	void PathfindingGame::Draw(const GameTime &gameTime)
	{
		mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), reinterpret_cast<const float*>(&BackgroundColor));
		mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		Game::Draw(gameTime);

		HRESULT hr = mSwapChain->Present(1, 0);

		// If the device was removed either by a disconnection or a driver upgrade, we must recreate all device resources.
		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			HandleDeviceLost();
		}
		else
		{
			ThrowIfFailed(hr, "IDXGISwapChain::Present() failed.");
		}
	}

	void PathfindingGame::Exit()
	{
		PostQuitMessage(0);
	}

	bool PathfindingGame::ValidNodePositions()
	{
		if (mGraph.At(mStartPoint)->Type() == NodeType::Wall ||
			mGraph.At(mEndPoint)->Type() == NodeType::Wall ||
			(mStartPoint.X == mEndPoint.X && mStartPoint.Y == mEndPoint.Y))
		{
			return false;
		}		
		else return true;
	}

	void PathfindingGame::ChangeAlgorithm()
	{
		switch (mAlgorithm)
		{
			case (Algorithm::BreadthFirstSearch):
			{
				mAlgorithmName = "Greedy Best First";
				mAlgorithm = Algorithm::GreedyBestFirst;
				break;
			}
			case (Algorithm::GreedyBestFirst):
			{
				mAlgorithmName = "Dijkstras";
				mAlgorithm = Algorithm::Dijkstras;
				break;
			}
			case (Algorithm::Dijkstras):
			{
				mAlgorithmName = "A*";
				mAlgorithm = Algorithm::AStar;
				break;
			}
			case (Algorithm::AStar):
			{
				mAlgorithmName = "Breadth First Search";
				mAlgorithm = Algorithm::BreadthFirstSearch;
				break;
			}
		}
		DrawGrid();
	}

	void PathfindingGame::ChangeAlgorithmHeuristic()
	{
		if (mHeuristicsType == HeuristicsType::ManhattanDistance)
		{
			mAlgorithmHeuristicName = "Euclidian Distance";
			mHeuristicsType = HeuristicsType::EuclidianDistance;
		}
		else
		{
			mAlgorithmHeuristicName = "Manhattan Distance";
			mHeuristicsType = HeuristicsType::ManhattanDistance;
		}
		DrawGrid();
	}

}