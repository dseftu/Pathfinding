#pragma once
#include "Game.h"

namespace Library
{
	class KeyboardComponent;
}

namespace Pathfinding
{

	class PathfindingGame : public Library::Game
	{
	public:
		PathfindingGame(std::function<void*()> getWindowCallback, std::function<void(SIZE&)> getRenderTargetSizeCallback);

		virtual void Initialize() override;
		virtual void Shutdown() override;
		virtual void Update(const Library::GameTime& gameTime) override;		
		virtual void Draw(const Library::GameTime& gameTime) override;

	private:
		void Exit();
		
		static DirectX::XMVECTORF32 BackgroundColor;

		std::shared_ptr<Library::KeyboardComponent> mKeyboard;
		std::shared_ptr<Library::ImGuiComponent> mImGui;
		
	};
}